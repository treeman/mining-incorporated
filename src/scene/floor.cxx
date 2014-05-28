#include "log.hxx"
#include "constants.hxx"
#include "util/rand.hxx"
#include "scene/ore.hxx"
#include "scene/floor.hxx"

namespace scene {

shared_ptr<Tile> Floor::tile(const TilePos &p) {
    assert(0 <= p.y && p.y < (int)grid.size());
    assert(0 <= p.x && p.x < (int)grid[0].size());
    return grid[p.y][p.x];
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

