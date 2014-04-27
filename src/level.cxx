#include "level.hxx"
#include "constants.hxx"

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

vector<vector<TilePtr>> make_first_level() {
    vector<vector<TilePtr>> grid(num_tiles_high, vector<TilePtr>(num_tiles_wide));
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
            grid[i][j] = create_tile(type, j * tile_width, i * tile_width);
        }
    }
    return grid;
}

RoomType randomize_ore_type(int) {
    //return DiamondOre;

    // AluminiumOre,
    // CoalOre,
    // CopperOre,
    // DiamondOre,
    // GoldOre,
    // IronOre,
    // In procent xD
    vector<int> ratio = {
        20,
        30,
        20,
        5,
        10,
        15,
    };
    int r = rand_int(0, 100);
    int sum = 0;
    for (int type = 0; type < (int)ratio.size(); ++type) {
        sum += ratio[type];
        if (r <= sum) {
            return static_cast<RoomType>(type + 7);
        }
    }
    return Rock; // fallback?
}

const int dr[4] = { 0, 1, 0, -1 };
const int dc[4] = { 1, 0, -1, 0 };

vector<vector<TilePtr>> make_random_level(int level) {
    vector<vector<TilePtr>> grid(num_tiles_high, vector<TilePtr>(num_tiles_wide));

    // TODO better randomization, with things more common at different levels
    // Randomize some ore strips
    int num_strips = rand_int(6, 10);
    //printf("doing %d strips\n", num_strips);

    for (int k = 0; k < num_strips; ++k) {
        RoomType type = randomize_ore_type(level);
        int num_ores = rand_int(3, 8);

        // Floodfill with randomization to place ores xD
        int r = rand_int(0, num_tiles_high - 1);
        int c = rand_int(0, num_tiles_wide - 1);
        //printf("floodfill from %d, %d\n", r, c);

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
            grid[r][c] = create_tile(type, c * tile_width, r * tile_width);

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (0 <= nr && nr < num_tiles_high && 0 <= nc && nc < num_tiles_wide) {
                    q.push_back(make_pair(nr, nc));
                }
            }
        }
    }

    for (int i = 0; i < num_tiles_high; ++i) {
        for (int j = 0; j < num_tiles_wide; ++j) {
            if (!grid[i][j])
                grid[i][j] = create_tile(Rock, j * tile_width, i * tile_width);
        }
    }
    return grid;
}

vector<vector<TilePtr>> make_level(int level) {
    //if (level == 1) return make_first_level();
    return make_random_level(level);
}

