#include "util/ext.hxx"
#include "util/rand.hxx"
#include "scene/world.hxx"
#include "scene/map.hxx"
#include "constants.hxx"
#include "butler.hxx"
#include "assert.h"
#include "locator.hxx"

namespace scene {

const int view_xoff = (screen_width - world_width) / 2;
const int view_yoff = (screen_height - world_height) / 2;

World::World(sf::RenderWindow &_w) :
    w(_w),
    view(sf::FloatRect(0, 0, screen_width, screen_height))
{
    view.move(-view_xoff, -view_yoff);

    map = make_map();
    set_curr_floor(0);

    new_worker();
    stat_txt = create_txt("consola.ttf", 14);

    Locator::get_settings().register_bool("debug_tasks", false);
    Locator::get_settings().register_bool("debug_positions", false);
}

bool World::in_world(const WindowPos &p) const {
    const WorldPos wp(p.x  - view_xoff, p.y - view_yoff, curr_floor);
    return in_world(wp);
}
bool World::in_world(const WorldPos &p) const {
    return 0 <= p.pos.x && p.pos.x < world_width
        && 0 <= p.pos.y && p.pos.y < world_height;
}
WorldPos World::window2world(const WindowPos &p) const {
    const WorldPos res(p.x  - view_xoff, p.y - view_yoff, curr_floor);
    assert(in_world(res));
    return res;
}
MapPos World::window2map(const WindowPos &p) const {
    return world2map(window2world(p));
}
MapPos World::world2map(const WorldPos &p) const {
    assert(in_world(p));
    return MapPos(p.pos.x / tile_width, p.pos.y / tile_width, p.floor);
}
WindowPos World::map2window(const MapPos &p) const {
    return WindowPos(p.pos.x * tile_width + view_xoff, p.pos.y * tile_width + view_yoff);
}
WindowPos World::world2window(const WorldPos &p) const {
    return map2window(world2map(p));
}

/*
shared_ptr<Tile> World::get_tile(const WorldPos &p) const {
    assert(in_world(p));
    return map->tile(world2map(p));
}
*/
shared_ptr<Tile> World::get_tile(const MapPos &p) const {
    return map->tile(p);
}

bool World::in_world(sf::Vector2i wp) { return in_world(wp.x, wp.y); }
bool World::in_world(int x, int y) {
    return 0 <= x && x <= world_width && 0 <= y && y <= world_height;
}

// TODO move to floor
bool World::is_tile(int x, int y) {
    return 0 <= x && x < (int)map->floor(curr_floor)->grid[0].size()
        && 0 <= y && y < (int)map->floor(curr_floor)->grid.size();
}

int World::num_floors() const {
    return map->num_floors();
}
void World::set_curr_floor(int floor) {
    assert(0 <= floor && floor < num_floors());
    curr_floor = floor;
}
int World::get_curr_floor() const { return curr_floor; }

void World::handle_input(const sf::Event &e) { }
void World::update(const sf::Time &dt) {
    assign_tasks();

    map->update(dt);
    for (auto worker : workers) {
        worker->update(dt);
    }

    // Add in debug info
    if (Locator::get_settings().get_bool("debug_positions")) {
        WindowPos mp(get_mpos());
        if (in_world(mp)) {
            WorldPos wpos(window2world(mp));
            MapPos map_pos(world2map(wpos));
            // Treat as int position, prevent unnecessary decimals
            D_.set_key("world", IPoint(wpos.pos).to_string() + " (" + to_string(wpos.floor) + ")");
            D_.set_key("map", map_pos.to_string());
        }
        else {
            D_.set_key("world", "invalid");
            D_.set_key("map", "invalid");
        }
    }

    if (Locator::get_settings().get_bool("debug_tasks")) {
        D_.tmp("pending tasks: " + to_string(pending_tasks.size()));
        for (auto &t : pending_tasks) {
            D_.tmp(t->to_string());
        }
    }
}
void World::draw() {
    sf::View curr = w.getView();
    w.setView(view);

    map->draw(w, curr_floor);

    for (auto &worker : workers) {
        worker->draw(w);
    }

    w.setView(curr);
    draw_stats();
}

void World::push_cmd(unique_ptr<Command> cmd) {
    if (auto c = dynamic_cast<PlacePlanningCommand*>(cmd.get())) {
        //L_("%s\n", c->to_string());
        for (int x = c->area.start.pos.x; x <= c->area.end.pos.x; ++x) {
            for (int y = c->area.start.pos.y; y <= c->area.end.pos.y; ++y) {
                shared_ptr<Tile> tile(map->tile(MapPos(x, y, c->area.start.floor)));
                tile->set_preview(c->obj);
            }
        }
    }
    else if (auto c = dynamic_cast<RemovePlanningCommand*>(cmd.get())) {
        //L_("%s\n", c->to_string());
        for (int x = c->area.start.pos.x; x <= c->area.end.pos.x; ++x) {
            for (int y = c->area.start.pos.y; y <= c->area.end.pos.y; ++y) {
                shared_ptr<Tile> tile(map->tile(MapPos(x, y, c->area.start.floor)));
                tile->remove_preview();
            }
        }
    }
}

void World::push_task(unique_ptr<Task> task) {
    pending_tasks.push_back(move(task));
}

void World::new_worker() {
    // TODO
    // Some marker that we can't hire? Or something?
    if ((int)workers.size() >= resources.max_workers) return;

    auto worker = create_worker(0, 0, this);
    workers.push_back(worker);
    //free_workers.push_back(worker);
}

// TODO choose based on task and closeness.
WorkerPtr World::choose_free_worker() {
    for (auto w : workers) {
        if (w->is_free()) return w;
    }
    return WorkerPtr();
}

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// TODO floor??`
vector<sf::Vector2i> World::pathfind(sf::Vector2i s, sf::Vector2i t) {
    const int rows = map->floor(curr_floor)->grid.size(), cols = map->floor(curr_floor)->grid[0].size();

    //printf("Pathfinding %d,%d -> %d,%d\n", s.x, s.y, t.x, t.y);

    struct State {
        State(int d, int _x, int _y, int mh) : dist(d), x(_x), y(_y), h(mh) { }

        bool operator < (const State &s) const {
            return dist + h > s.dist + s.h ;
        }
        int dist, x, y;
        int h;
    };

    // cost / position
    vector<vector<int>> dist(rows, vector<int>(cols, numeric_limits<int>::max()));
    vector<vector<sf::Vector2i>> prev(rows, vector<sf::Vector2i>(cols, sf::Vector2i(-1, -1)));

    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { 1, 0, -1, 0 };

    priority_queue<State> pq;
    pq.push(State(0, s.x, s.y, manhattan(s.x, s.y, t.x, t.y)));
    dist[s.y][s.x] = 0;

    while (!pq.empty()) {
        State s = pq.top(); pq.pop();

        if (s.dist > dist[s.y][s.x]) continue;
        //printf("  cost %d at %d,%d (h %d) tot: %d\n", s.dist, s.x, s.y, s.h, s.dist + s.h);
        //printf("  %s\n", grid[s.y][s.x]->is_walkable() ? "ok" : "NO");

        // Goal check
        if (s.x == t.x && s.y == t.y) break;

        for (int d = 0; d < 4; ++d) {
            int nx = s.x + dx[d], ny = s.y + dy[d];
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) continue;
            bool is_goal = nx == t.x && ny == t.y;
            if (!map->floor(curr_floor)->grid.at(ny).at(nx)->is_walkable() && !is_goal) {
                //printf("skip %d %d\n", nx, ny);
                continue;
            }

            int next_cost = 1 + dist[s.y][s.x];
            if (next_cost < dist[ny][nx]) {
                dist[ny][nx] = next_cost;
                prev[ny][nx] = sf::Vector2i(s.x, s.y);
                pq.push(State(next_cost, nx, ny, manhattan(nx, ny, t.x, t.y)));
            }
        }
    }

    // Backtrack for path and transform to world coordinates.
    vector<sf::Vector2i> res;

    // Impossible!
    if (dist[t.y][t.x] == numeric_limits<int>::max())
        return res;

    sf::Vector2i p(t);
    while (p.x != -1) {
        res.push_back(p);
        p = prev[p.y][p.x];
    }
    res.pop_back(); // Temporary workaround, ignore start
    //printf("path:\n");
    //for (auto p : res) printf(" %d,%d\n", p.x, p.y);
    return res;
}

void World::task_done(Task task) {
    // TODO update grid here!
    if (task.type == Dig) {
        // Currently unused (?)
        shared_ptr<Tile> tile = get_tile(task.pos);
    }
    else if (task.type == BuildRoom) {
        shared_ptr<Tile> tile = get_tile(task.pos);

        /*
        // Check for ore mining
        RoomInfo *info = get_info(tile->get_type());
        if (info->is_ore) {
            int ores = rand_int(info->min_ores, info->max_ores);
            //printf("%d - %d => %d\n", info->min_ores, info->max_ores, ores);
            resources.money += ores * info->money_per_ore;
            switch (info->type) {
                case AluminiumOre:
                    resources.aluminium += ores;
                    break;
                case CoalOre:
                    resources.coal += ores;
                    break;
                case CopperOre:
                    resources.copper += ores;
                    break;
                case DiamondOre:
                    resources.diamond += ores;
                    break;
                case GoldOre:
                    resources.gold += ores;
                    break;
                case IronOre:
                    resources.iron += ores;
                    break;
                default: break;
            }
        }

        // Update tile
        tile->set_type(task.room_type);
        */
    }
    else if (task.type == PlaceObject) {
        /*
        shared_ptr<Tile> tile = get_tile(task.pos);
        tile->set_object(make_object(task.object_type));

        if (task.object_type == Bed) {
            resources.max_workers += bed_capacity;
        }
        */
    }
    else if (task.type == SellTask) {
        /*
        shared_ptr<Tile> tile = get_tile(task.pos);
        if (tile->get_object()->get_type() == Bed) {
            resources.max_workers -= bed_capacity;
        }
        tile->remove_object();
        */
    }
    else {
        printf("Unknown task %d is done!\n", task.type);
    }
}
void World::skip_task(Task task) {
    tasks.push_back(task);
}
void World::assign_tasks() {
    // TODO make something better...
    deque<Task> unfinished;
    for (Task t : tasks) {
        bool assigned = false;
        for (auto worker : workers) {
            if (!worker->is_free()) continue;
            if (worker->assign_task(t)) {
                assigned = true;
                break;
            }
        }
        if (!assigned) unfinished.push_back(t);
    }

    tasks.swap(unfinished);
}

shared_ptr<Tile> World::get_tile(int x, int y) {
    return map->tile(x, y, curr_floor);
}
shared_ptr<Tile> World::get_tile(sf::Vector2i pos) { return get_tile(pos.x, pos.y); }

// TODO move to gui
void World::draw_stats() {
    // Draw current state
    int xoff = 690;
    int yoff = 10;

    stringstream ss;

    ss.str("");
    stat_txt.setColor(sf::Color::White);
    stat_txt.setPosition(600, yoff);
    ss << "Workers: " << workers.size() << "/" << resources.max_workers;
    stat_txt.setString(ss.str());
    w.draw(stat_txt);


    ss.str("");
    ss << "$" << resources.money;
    stat_txt.setColor(make_color(0x2F9C3F));
    stat_txt.setPosition(740, yoff);
    stat_txt.setString(ss.str());
    w.draw(stat_txt);

    // Draw collected resources.
    int h = 16, curr_y = yoff + h + 5;
    draw_stats("Aluminium: ", resources.aluminium, make_color(0xF6926D), xoff, curr_y);
    curr_y += h;
    draw_stats("Coal: ", resources.coal, make_color(0xB6926D), xoff, curr_y);
    curr_y += h;
    draw_stats("Copper: ", resources.copper, make_color(0x924924), xoff, curr_y);
    curr_y += h;
    draw_stats("Diamond: ", resources.diamond, make_color(0x0092DB), xoff, curr_y);
    curr_y += h;
    draw_stats("Gold: ", resources.gold, make_color(0xFFB600), xoff, curr_y);
    curr_y += h;
    draw_stats("Iron: ", resources.iron, make_color(0xFFFFFF), xoff, curr_y);
    curr_y += h;
}

void World::draw_stats(string pre, int &val, sf::Color color, int x, int y) {
    stat_txt.setColor(sf::Color::White);
    stat_txt.setPosition(x, y);
    stat_txt.setString(pre);
    w.draw(stat_txt);
    int off = stat_txt.getGlobalBounds().width;

    stringstream ss;
    ss << val;
    stat_txt.setString(ss.str());
    stat_txt.setColor(color);
    stat_txt.setPosition(x + off, y);
    w.draw(stat_txt);
}

shared_ptr<Worker> World::select_closest_worker(const WorldPos &p) {
    shared_ptr<Worker> res{ nullptr };
    float closest = numeric_limits<float>::infinity();
    for (auto w : workers) {
        float d =  FPoint(w->get_pos()).dist(p.pos);
        if (d < closest) {
            closest = d;
            res = w;
        }
    }
    return res;
}

int World::calculate_build_cost(int x1, int y1, int x2, int y2, RoomType type) {
    int dx = abs(x1 - x2) + 1, dy = abs(y2 - y1) + 1;
    return dx * dy * get_info(type)->cost;
}
RoomType World::get_tile_type(int x, int y) {
    //shared_ptr<Tile> tile = get_tile(x, y);
    //return tile->get_type();
    return Rock;
}

sf::View &World::get_view() { return view; }

}; // Scene

