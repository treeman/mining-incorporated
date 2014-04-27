#include "util.hxx"
#include "world.hxx"
#include "constants.hxx"
#include "butler.hxx"
#include "assert.h"
#include "level.hxx"

const int view_xoff = (screen_width - world_width) / 2;
const int view_yoff = (screen_height - world_height) / 2;

World::World(sf::RenderWindow &_w) :
    w(_w),
    view(sf::FloatRect(0, 0, screen_width, screen_height))
{
    view.move(-view_xoff, -view_yoff);

    // TODO multiple levels
    grid = make_level(1);

    new_worker();

    mpos = create_txt("arial.ttf", 14, "0, 0");
    mpos.setPosition(100, 5);
    txt = create_txt("arial.ttf", 14);
}

sf::Vector2i World::window2tile(int x, int y) {
    return world2tile(window2world(x, y));
}
sf::Vector2i World::window2world(int x, int y) {
    return sf::Vector2i(x - view_xoff, y - view_yoff);
}
sf::Vector2i World::world2tile(int x, int y) {
    return sf::Vector2i(x / tile_width, y / tile_width);
}
sf::Vector2i World::tile2world(int x, int y) {
    return sf::Vector2i(x * tile_width, y * tile_width);
}

bool World::in_world(sf::Vector2i wp) { return in_world(wp.x, wp.y); }
bool World::in_world(int x, int y) {
    return 0 <= x && x <= world_width && 0 <= y && y <= world_height;
}

bool World::is_tile(int x, int y) {
    return 0 <= x && x < (int)grid[0].size()
        && 0 <= y && y < (int)grid.size();
}

void World::build(sf::Vector2i wp, RoomType type) {
    if (!in_world(wp)) return;

    auto tpos = world2tile(wp.x, wp.y);
    build(tpos.x, tpos.y, type);
}
/*
void World::remove(sf::Vector2i wp) {
    if (!in_world(wp)) return;

    auto tpos = world2tile(wp.x, wp.y);
    remove(tpos.x, tpos.y);
}
*/

// Tile positions
void World::build(int x, int y, RoomType type) {
    if (!is_tile(x, y)) return;

    TilePtr tile = get_tile(x, y);
    if (tile->get_type() == type) return;

    tasks.push_back(create_room_task(x, y, type));
    tile->set_room_build_pending();
}
void World::build(int x, int y, ObjectType type) {
    if (!is_tile(x, y)) return;
    TilePtr tile = grid[y][x];

    if (tile->has_object() && type == SellObject) {
        tasks.push_back(create_sell_task(x, y));
    }
    else if (type != SellObject) {
        if (!tile->has_object()) {
            tile->set_object_build_pending();
            tasks.push_back(create_object_task(x, y, type));
        }
    }
}

void World::sell_object(int x, int y) {
    // TODO money management here
    if (!is_tile(x, y)) return;
    TilePtr tile = grid[y][x];

    tile->remove_object();
}

/*
void World::remove(int x, int y) {
    TilePtr tile = grid[y][x];
    tile->unmark();
}
*/

void World::build(int x1, int y1, int x2, int y2, RoomType type) {
    if (x2 < x1) swap(x1, x2);
    if (y2 < y1) swap(y1, y2);
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            if (is_tile(x, y)) {
                build(x, y, type);
            }
        }
    }
}
/*
void World::remove(int x1, int y1, int x2, int y2) {
    if (x2 < x1) swap(x1, x2);
    if (y2 < y1) swap(y1, y2);
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            if (is_tile(x, y)) {
                remove(x, y);
            }
        }
    }
}
*/

void World::preview_room_build(int x, int y) {
    if (is_tile(x, y)) {
        grid[y][x]->set_room_preview();
    }
}

void World::preview_room_build(int x1, int y1, int x2, int y2) {
    clear_preview();

    if (x2 < x1) swap(x1, x2);
    if (y2 < y1) swap(y1, y2);
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            if (is_tile(x, y)) {
                preview_room_build(x, y);
            }
        }
    }
}
void World::preview_object_build(int x, int y) {
    if (is_tile(x, y)) {
        grid[y][x]->set_object_preview();
    }
}
void World::clear_preview() {
    for (auto row : grid) {
        for (auto t : row) {
            t->clear_preview();
        }
    }
}

void World::handle_input(const sf::Event &e) { }
void World::update(const sf::Time &dt) {
    assign_tasks();

    for (auto worker : workers) {
        worker->update(dt);
    }
}
void World::draw() {
    sf::View curr = w.getView();
    w.setView(view);

    for (int i = 0; i < num_tiles_high; ++i) {
        for (int j = 0; j < num_tiles_wide; ++j) {
            grid[i][j]->draw(w);
        }
    }

    for (auto worker : workers) {
        worker->draw(w);
    }

    w.setView(curr);

    // Draw position in world.
    auto mp = sf::Mouse::getPosition(w);
    auto wp = window2world(mp.x, mp.y);
    stringstream ss; ss << wp.x << ", " << wp.y;
    auto tp = world2tile(wp.x, wp.y);
    ss << "   " << tp;
    mpos.setString(ss.str());
    w.draw(mpos);


    // Draw current task queue
    int x = 620, y = 250, dy = 16;
    for (auto t : tasks) {
        txt.setString(t.to_str());
        txt.setPosition(x, y);
        w.draw(txt);
        y += dy;
    }
}

void World::new_worker() {
    auto worker = create_worker(0, 0, this);
    workers.push_back(worker);
    free_workers.push_back(worker);
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

// TODO levels??`
vector<sf::Vector2i> World::pathfind(sf::Vector2i s, sf::Vector2i t) {
    const int rows = grid.size(), cols = grid[0].size();

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
            if (!grid.at(ny).at(nx)->is_walkable() && !is_goal) {
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

    //printf("Cost %d\n", dist[t.y][t.x]);

    // Impossible!
    if (dist[t.y][t.x] == numeric_limits<int>::max())
        return res;

    sf::Vector2i p(t);
    while (p.x != -1) {
        res.push_back(p);
        //res.push_back(tile2world(p));
        p = prev[p.y][p.x];
    }
    res.pop_back(); // Temporary workaround, ignore start
    //reverse(res.begin(), res.end());
    //printf("path:\n");
    //for (auto p : res) printf(" %d,%d\n", p.x, p.y);
    return res;
}

void World::task_done(Task task) {
    // TODO update grid here!
    if (task.type == Dig) {
        TilePtr tile = get_tile(task.pos);
    }
    else if (task.type == BuildRoom) {
        TilePtr tile = get_tile(task.pos);
        tile->set_type(task.room_type);
    }
    else if (task.type == PlaceObject) {
        TilePtr tile = get_tile(task.pos);
        tile->set_object(make_object(task.object_type));
    }
    else if (task.type == SellTask) {
        TilePtr tile = get_tile(task.pos);
        tile->remove_object();
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

TilePtr World::get_tile(int x, int y) {
    return grid.at(y).at(x);
}
TilePtr World::get_tile(sf::Vector2i pos) { return get_tile(pos.x, pos.y); }

