#include "lua.hxx"
#include "log.hxx"
#include "constants.hxx"
#include "util/rand.hxx"
#include "scene/objectfactory.hxx"
#include "scene/ore.hxx"

namespace scene {

ObjectFactory::ObjectFactory() {
    init_planning_objects();
    load_ground_definitions("ground.lua");
    load_ore_definitions("ore.lua");
}

shared_ptr<PlanningObject> ObjectFactory::create_planning_object(PlanningType o) const {
    unsigned x = static_cast<unsigned>(o);
    assert(x < planning_objects.size());
    assert(planning_objects[x] != nullptr);
    shared_ptr<PlanningObject> res(new PlanningObject(*planning_objects[x].get()));
    return move(res);
}
const Ground *ObjectFactory::get_ground(string key) const {
    auto it = grounds.find(key);
    if (it == grounds.end()) {
        throw lua_parse_error(fmt("Could not find ground definition for '%s'", key));
    }
    return it->second.get();
}

void ObjectFactory::init_planning_objects() {
    // TODO load from lua
    // Maybe cleanup?
    auto col = sf::Color(255, 255, 255, 100);
    planning_objects.resize(static_cast<unsigned>(PlanningType::NUM_OBJECTS));
    planning_objects[static_cast<unsigned>(PlanningType::ROOM)].reset(
        new PlanningObject("room_preview.png", PlanningType::ROOM, col));
    planning_objects[static_cast<unsigned>(PlanningType::OBJECT)].reset(
        new PlanningObject("object_preview.png", PlanningType::OBJECT, col));
}

void ObjectFactory::load_ground_definitions(string path) {
    LuaState L;
    L.dofile(path);

    vector<shared_ptr<Ground>> found;

    // Find definitions inside 'ground' table.
    lua_getglobal(L, "ground");
    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        shared_ptr<Ground> ground(new Ground());

        string key = lua_tostring(L, -2);
        //L_ << key << '\n';
        //L.dump_stack();
        if (!lua_istable(L, -1))
            throw lua_parse_error(path, fmt("ground %s not a table.", key));
        ground->key = key;

        // TODO create functions for these?
        // or just use these raw?
        lua_pushstring(L, "sprite");
        lua_gettable(L, -2);
        if (!lua_isstring(L, -1)) {
            throw lua_parse_error(path, fmt("%s missing sprite.", key));
        }
        ground->spr = lua_tostring(L, -1);
        //L_ << "  sprite: " << ground->spr << '\n';
        lua_pop(L, 1);

        lua_pushstring(L, "remove_time");
        lua_gettable(L, -2);
        if (lua_isnumber(L, -1)) {
            ground->remove_time = (float)lua_tonumber(L, -1);
            //L_("  remove_time: %f\n", ground->remove_time);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "build_time");
        lua_gettable(L, -2);
        if (lua_isnumber(L, -1)) {
            ground->build_time = (float)lua_tonumber(L, -1);
            //L_("  build_time: %f\n", ground->build_time);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "walkable");
        lua_gettable(L, -2);
        if (lua_isboolean(L, -1)) {
            ground->is_walkable = lua_toboolean(L, -1);
            //L_("  walkable: %s\n", to_string(ground->is_walkable));
        }
        lua_pop(L, 1);

        grounds.insert({key, ground});
        found.push_back(ground);
    }
    lua_pop(L, 1);

    assert(L.stack_size() == 0);

    L_("found %d grounds\n", found.size());
    for (auto x : found) {
        L_("  %s\n", x->key);
    }
}

void ObjectFactory::load_ore_definitions(string path) {
    LuaState L;
    L.dofile(path);

    vector<shared_ptr<Ore>> found;

    // Find definitions inside 'ground' table.
    lua_getglobal(L, "ore");
    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        shared_ptr<Ore> ore(new Ore());

        string key = lua_tostring(L, -2);
        //L_ << key << '\n';
        //L.dump_stack();
        if (!lua_istable(L, -1))
            throw lua_parse_error(path, fmt("ore %s not a table.", key));
        ore->key = key;

        // TODO create functions for these?
        // or just use these raw?
        lua_pushstring(L, "sprite");
        lua_gettable(L, -2);
        if (!lua_isstring(L, -1)) {
            throw lua_parse_error(path, fmt("%s missing sprite.", key));
        }
        ore->spr = lua_tostring(L, -1);
        //L_ << "  sprite: " << ore->spr << '\n';
        lua_pop(L, 1);

        lua_pushstring(L, "remove_time");
        lua_gettable(L, -2);
        if (lua_isnumber(L, -1)) {
            ore->remove_time = (float)lua_tonumber(L, -1);
            //L_("  remove_time: %f\n", ore->remove_time);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "build_time");
        lua_gettable(L, -2);
        if (lua_isnumber(L, -1)) {
            ore->build_time = (float)lua_tonumber(L, -1);
            //L_("  build_time: %f\n", ore->build_time);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "walkable");
        lua_gettable(L, -2);
        if (lua_isboolean(L, -1)) {
            ore->is_walkable = lua_toboolean(L, -1);
            //L_("  walkable: %s\n", to_string(ore->is_walkable));
        }
        lua_pop(L, 1);

        grounds.insert({key, ore});
        found.push_back(ore);
        //ores.insert({key, shared_ptr<Ground>(move(ore))});
    }
    lua_pop(L, 1);

    assert(L.stack_size() == 0);

    L_("found %d ores\n", found.size());
    for (auto x : found) {
        L_("  %s\n", x->key);
    }
}

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
    auto f = Locator::get_object_factory();
    for (int i = 0; i < num_tiles_high; ++i) {
        for (int j = 0; j < num_tiles_wide; ++j) {
            const Ground *ground{ nullptr };
            switch (first_floor[i][j]) {
                case 's': ground = f.get_ground("stone"); break;
                case 'a': ground = f.get_ground("aluminium"); break;
                case 'k': ground = f.get_ground("coal"); break;
                case 'c': ground = f.get_ground("copper"); break;
                case 'd': ground = f.get_ground("diamond"); break;
                case 'g': ground = f.get_ground("gold"); break;
                case 'i': ground = f.get_ground("iron"); break;
                case '.': ground = f.get_ground("rock"); break;
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
    auto f = Locator::get_object_factory();

    // TODO better randomization, with things more common at different floors
    // Randomize some ore strips
    int num_strips = rand_int(6, 10);
    //printf("doing %d strips\n", num_strips);

    for (int k = 0; k < num_strips; ++k) {
        string type = randomize_ore_type(num);
        auto ore = f.get_ground(type);
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

    auto rock = f.get_ground("rock");
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

shared_ptr<Map> ObjectFactory::make_map() const {
    shared_ptr<Map> res(new Map());
    for (int i = 0; i < 10; ++i) {
        res->floors.push_back(make_floor(i));
    }
    return res;
}

};

