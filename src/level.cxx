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

vector<vector<TilePtr>> make_level(int level) {
    if (level == 1) return make_first_level();
    // TODO
    // Crate an empty level, but with ores!
    exit(-1);
}

