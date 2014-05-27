#include "log.hxx"
#include "constants.hxx"
#include "util/rand.hxx"
#include "scene/ore.hxx"
#include "scene/floor.hxx"

namespace scene {

// TODO
// load from lua!
string first_floor[num_tiles_high] = {
    "sssss.............aa",
    "sssss............aa.",
    "..............aaaa..",
    ".dd.................",
    "..d.................",
    "..........c.cc......",
    "..........ccc.......",
    "....................",
    "............kk......",
    "...ggg......kkk.....",
    "....gg..............",
    "....................",
    ".....i..............",
    ".....i....i.........",
    "...iii....ii........",
    ".....i..............",
};

shared_ptr<Floor> make_first_floor() {
    shared_ptr<Floor> res(new Floor(0));
    res->grid.assign(num_tiles_high, vector<shared_ptr<Tile>>(num_tiles_wide));
    for (int i = 0; i < num_tiles_high; ++i) {
        for (int j = 0; j < num_tiles_wide; ++j) {
            shared_ptr<const Ground> ground;
            switch (first_floor[i][j]) {
                case 's': ground = get_ground("stone"); break;
                case 'a': ground = get_ore("aluminium"); break;
                case 'k': ground = get_ore("coal"); break;
                case 'c': ground = get_ore("copper"); break;
                case 'd': ground = get_ore("diamond"); break;
                case 'g': ground = get_ore("gold"); break;
                case 'i': ground = get_ore("iron"); break;
                case '.': ground = get_ground("rock"); break;
                default: L_("missing ground def for %c\n", first_floor[i][j]);
            }

            assert(ground != nullptr);
            res->grid[i][j] = ground->create_tile(j * tile_width, i * tile_width);
        }
    }

    return res;
}

string randomize_ore_type(int) {
    // TODO take from lua
    // TODO specify vein size as well
    // TODO make something more clever...
    map<string,  int> ratio = {
        { "aluminium", 20 },
        { "coal", 30 },
        { "copper", 20 },
        { "diamond", 5 },
        { "gold", 10 },
        { "iron", 15 },
    };
    int r = rand_int(0, 100);
    int sum = 0;
    for (auto &x : ratio) {
        sum += x.second;
        if (r <= sum) {
            return x.first;
        }
    }
    return "rock"; // fallback?
}

const int dr[4] = { 0, 1, 0, -1 };
const int dc[4] = { 1, 0, -1, 0 };

shared_ptr<Floor> make_random_floor(int num) {
    shared_ptr<Floor> floor(new Floor(num));
    floor->grid.assign(num_tiles_high, vector<shared_ptr<Tile>>(num_tiles_wide));

    // TODO better randomization, with things more common at different floors
    // Randomize some ore strips
    int num_strips = rand_int(6, 10);
    //printf("doing %d strips\n", num_strips);

    for (int k = 0; k < num_strips; ++k) {
        string type = randomize_ore_type(num);
        auto ore = get_ore(type);
        int num_ores = rand_int(3, 8);

        // Floodfill with randomization to place ores xD
        int r = rand_int(0, num_tiles_high - 1);
        int c = rand_int(0, num_tiles_wide - 1);

        vector<vector<int>> seen(num_tiles_high, vector<int>(num_tiles_wide, 0));
        vector<pair<int, int>> q;
        q.push_back(make_pair(r, c));

        int placed = 0;
        while (!q.empty() && placed < num_ores) {
            int choice = rand_int(0, q.size() - 1);
            auto pos = q[choice];
            q.erase(q.begin() + choice);

            int r = pos.first, c = pos.second;

            if (seen[r][c]) continue;

            ++placed;
            seen[r][c] = 1;
            // Place ore here!
            // TODO
            //grid[r][c] = create_tile(type, c * tile_width, r * tile_width);
            floor->grid[r][c] = ore->create_tile(c * tile_width, r * tile_width);

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (0 <= nr && nr < num_tiles_high && 0 <= nc && nc < num_tiles_wide) {
                    q.push_back(make_pair(nr, nc));
                }
            }
        }
    }

    auto rock = get_ground("rock");
    for (int i = 0; i < num_tiles_high; ++i) {
        for (int j = 0; j < num_tiles_wide; ++j) {
            if (!floor->grid[i][j]) {
                floor->grid[i][j] = rock->create_tile(j * tile_width, i * tile_width);
            }
        }
    }
    return floor;
}

shared_ptr<Floor> make_floor(int floor) {
    if (floor == 0) return make_first_floor();
    return make_random_floor(floor);
}

shared_ptr<Tile> Floor::tile(int x, int y) {
    assert(0 <= y && y < (int)grid.size());
    assert(0 <= x && x < (int)grid[0].size());
    return grid[y][x];
}
shared_ptr<Tile> Floor::tile(const TilePos &p) {
    return tile(p.x, p.y);
}
bool Floor::in_floor(const TilePos &p) const {
    return 0 <= p.y && p.y < (int)grid.size()
        && 0 <= p.x && p.x < (int)grid[p.y].size();
}

void Floor::update(const sf::Time &dt) {
    // TODO?
    //for (int y = 0; y < (int)grid.size(); ++y) {
        //for (int x = 0; x < (int)grid[y].size(); ++x) {
            //grid[y][x]->update(dt);
        //}
    //}
}

void Floor::draw(sf::RenderWindow &w) {
    for (int y = 0; y < (int)grid.size(); ++y) {
        for (int x = 0; x < (int)grid[y].size(); ++x) {
            grid[y][x]->draw(w);
        }
    }
}

Floor::Floor(int num) : floor_num(num) {

}

Path Floor::pathfind(const TilePos &from, const TilePos &to) const {
    assert(in_floor(from) && in_floor(to)); // TODO change?
    const int rows = grid.size();
    const int cols = grid[0].size();

    struct State {
        State(TilePos _p, int _dist, int _h) : p(_p), dist(_dist), h(_h) { }

        bool operator < (const State &s) const {
            return dist + h > s.dist + s.h ;
        }
        TilePos p;
        int dist, h;
    };

    // manhattan heuristic for A*
    auto h = [to](const TilePos &p) {
        return abs(p.x - to.x) + abs(p.y - to.y);
    };

    const int INF = numeric_limits<int>::max();

    // cost / position
    vector<vector<int>> dist(rows, vector<int>(cols, INF));
    const TilePos invalid(-1, -1);
    vector<vector<TilePos>> prev(rows, vector<TilePos>(cols, invalid));

    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { 1, 0, -1, 0 };

    // Run A*
    priority_queue<State> pq;
    pq.push(State(from, 0, h(from)));
    dist[from.y][from.x] = 0;

    while (!pq.empty()) {
        State s = pq.top(); pq.pop();

        if (s.dist > dist[s.p.y][s.p.x]) continue;
        if (s.p == to) break;

        for (int d = 0; d < 4; ++d) {
            TilePos next_pos(s.p.x + dx[d], s.p.y + dy[d]);

            if (next_pos.x < 0 || next_pos.x >= cols ||
                next_pos.y < 0 || next_pos.y >= rows) continue;

            if (grid[next_pos.y][next_pos.x]->is_walkable() || next_pos == to) {
                int next_cost = 1 + dist[s.p.y][s.p.x];
                if (next_cost < dist[next_pos.y][next_pos.x]) {
                    dist[next_pos.y][next_pos.x] = next_cost;
                    prev[next_pos.y][next_pos.x] = s.p;
                    pq.push(State(next_pos, next_cost, h(next_pos)));
                }
            }
        }
    }

    // Backtrack for path
    Path res;

    if (dist[to.y][to.x] == INF)
        return res;

    // Incorporate floor number inside path, to later allow for cross-floor pathfinding.
    TilePos p(to);
    while (p != invalid) {
        res.v.push_back(MapPos(p, floor_num));
        p = prev[p.y][p.x];
    }
    reverse(res.v.begin(), res.v.end());

    return res;
}

} // scene

