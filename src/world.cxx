#include "util.hxx"
#include "world.hxx"
#include "constants.hxx"
#include "butler.hxx"
#include "assert.h"

const int view_xoff = (screen_width - world_width) / 2;
const int view_yoff = (screen_height - world_height) / 2;

World::World(sf::RenderWindow &_w) :
    w(_w),
    view(sf::FloatRect(0, 0, screen_width, screen_height))
{
    view.move(-view_xoff, -view_yoff);

    grid.assign(num_tiles_high, vector<TilePtr>(num_tiles_wide));
    for (int i = 0; i < num_tiles_high; ++i) {
        for (int j = 0; j < num_tiles_wide; ++j) {
            grid[i][j] = create_tile(StoneTile, j * tile_width, i * tile_width);
        }
    }

    new_worker();

    mpos = create_txt("arial.ttf", 14, "0, 0");
    mpos.setPosition(100, 5);
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

void World::build(sf::Vector2i wp) {
    if (!in_world(wp)) return;

    auto tpos = world2tile(wp.x, wp.y);
    TilePtr tile = grid.at(tpos.y).at(tpos.x);
    // TODO better building...
    printf("click at %d %d\n", wp.x, wp.y);
    //TilePtr tile = get_tile(wp);
    tile->is_marked =  true;

    // Assign task to worker
    WorkerPtr worker = choose_free_worker();
    auto path = pathfind(worker->tile_pos, tpos);
    worker->set_path(path);
}

void World::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            build(window2world(e.mouseButton.x, e.mouseButton.y));
            break;
        default: break;
    }
}
void World::update(const sf::Time &dt) {
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
    mpos.setString(ss.str());
    w.draw(mpos);
}

void World::new_worker() {
    auto worker = create_worker(0, 0, this);
    workers.push_back(worker);
    free_workers.push_back(worker);
}

WorkerPtr World::choose_free_worker() {
    // TODO select worker with smallest task queue
    return workers.front();
}

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

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
        //printf("  cost %d at %d,%d (h %d) tot: %d\n", s.dist, s.x, s.y, s.h, s.dist + s.h);

        if (s.dist > dist[s.y][s.x]) continue;

        // Goal check
        if (s.x == t.x && s.y == t.y) break;

        for (int d = 0; d < 4; ++d) {
            int nx = s.x + dx[d], ny = s.y + dy[d];
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) continue;

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
    sf::Vector2i p(t);
    while (p.x != -1) {
        res.push_back(tile2world(p));
        p = prev[p.y][p.x];
    }
    //reverse(res.begin(), res.end());
    //printf("path:\n");
    //for (auto p : res) printf(" %d,%d\n", p.x, p.y);
    return res;
}

