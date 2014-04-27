#include "level.hxx"
#include "constants.hxx"

string first_level[num_tiles_high] = {
    "..xxxxxxxxxxxxxxxxxx",
    "..xxxxxxxxxxxxxxxxxx",
    "..xxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
    "xxxxxxxxxxxxxxxxxxxx",
};

vector<vector<TilePtr>> make_first_level() {
    vector<vector<TilePtr>> grid(num_tiles_high, vector<TilePtr>(num_tiles_wide));
    for (int i = 0; i < num_tiles_high; ++i) {
        for (int j = 0; j < num_tiles_wide; ++j) {
            if (first_level[i][j] == '.') {
                grid[i][j] = create_tile(Mine, j * tile_width, i * tile_width);
            }
            else {
                grid[i][j] = create_tile(Rock, j * tile_width, i * tile_width);
            }
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

