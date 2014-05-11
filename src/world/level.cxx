#include "level.hxx"
#include "constants.hxx"
#include "util/rand.hxx"
#include "ore.hxx"

/*
string first_level[num_tiles_high] = {
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

vector<vector<shared_ptr<Tile>>> make_first_level() {
    vector<vector<shared_ptr<Tile>>> grid(num_tiles_high, vector<shared_ptr<Tile>>(num_tiles_wide));
    for (int i = 0; i < num_tiles_high; ++i) {
        for (int j = 0; j < num_tiles_wide; ++j) {
            RoomType type;
            switch (first_level[i][j]) {
                case 's':
                    type = Mine; break;
                case 'a':
                    type = AluminiumOre; break;
                case 'k':
                    type = CoalOre; break;
                case 'c':
                    type = CopperOre; break;
                case 'd':
                    type = DiamondOre; break;
                case 'g':
                    type = GoldOre; break;
                case 'i':
                    type = IronOre; break;
                default:
                    type = Rock;
            }
            //grid[i][j] = create_tile(type, j * tile_width, i * tile_width);
        }
    }
    return grid;
}
*/

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

shared_ptr<Level> make_random_level(int lvl) {
    shared_ptr<Level> level(new Level());
    level->grid.assign(num_tiles_high, vector<shared_ptr<Tile>>(num_tiles_wide));

    // TODO better randomization, with things more common at different levels
    // Randomize some ore strips
    int num_strips = rand_int(6, 10);
    //printf("doing %d strips\n", num_strips);

    for (int k = 0; k < num_strips; ++k) {
        string type = randomize_ore_type(lvl);
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
            level->grid[r][c] = ore->create_tile(c * tile_width, r * tile_width);

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
            if (!level->grid[i][j]) {
                level->grid[i][j] = rock->create_tile(j * tile_width, i * tile_width);
            }
        }
    }
    return level;
}

shared_ptr<Level> make_level(int level) {
    //if (level == 1) return make_first_level();
    return make_random_level(level);
}

shared_ptr<Tile> Level::tile(int x, int y) {
    assert(0 <= y && y < (int)grid.size());
    assert(0 <= x && x < (int)grid[0].size());
    return grid[y][x];
}
shared_ptr<Tile> Level::tile(const TilePos &p) {
    return tile(p.x, p.y);
}

void Level::update(const sf::Time &dt) {
    for (int y = 0; y < (int)grid.size(); ++y) {
        for (int x = 0; x < (int)grid[y].size(); ++x) {
            // TODO
            //grid[y][x]->update(dt);
        }
    }
}

void Level::draw(sf::RenderWindow &w) {
    for (int y = 0; y < (int)grid.size(); ++y) {
        for (int x = 0; x < (int)grid[y].size(); ++x) {
            grid[y][x]->draw(w);
        }
    }
}

Level::Level() {

}

