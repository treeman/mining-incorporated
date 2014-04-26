#include "util.hxx"
#include "world.hxx"
#include "constants.hxx"
#include "butler.hxx"

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

    workers.push_back(create_worker(0, 0));

    mpos = create_txt("arial.ttf", 14, "0, 0");
    mpos.setPosition(100, 5);
}

sf::Vector2i World::window2world(int x, int y) {
    return sf::Vector2i(x - view_xoff, y - view_yoff);
}
bool World::in_world(sf::Vector2i wp) { return in_world(wp.x, wp.y); }
bool World::in_world(int x, int y) {
    return 0 <= x && x <= world_width && 0 <= y && y <= world_height;
}

void World::build(sf::Vector2i wp) {
    if (!in_world(wp)) return;

    printf("click at %d %d\n", wp.x, wp.y);
}

void World::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            build(window2world(e.mouseButton.x, e.mouseButton.y));
            //printf("click at %d %d ", e.mouseButton.x, e.mouseButton.y);
            //auto wp = window2world(e.mouseButton.x, e.mouseButton.y);
            //printf(" -> %d %d\n", wp.x, wp.y);
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

