#include "worker.hxx"
#include "butler.hxx"
#include "world.hxx"
#include "constants.hxx"

Worker::Worker(int x, int y, World *_world) : pos(x, y), world(_world){
    spr = create_sprite("worker.png");
    tile_pos = world->world2tile(x, y);
    current_task.is_done = true;
    txt = create_txt("arial.ttf", 14);
}

bool Worker::is_free() {
    return current_task.is_done;
}
bool Worker::assign_task(Task task) {
    //printf("I have a task type: %d\n", task.type);

    if (tile_pos == task.pos) {
        current_task = task;
    }
    else {
        path = world->pathfind(tile_pos, task.pos);
        if (!path.size()) return false;
        current_task = task;
    }
    return true;
}

void Worker::update(const sf::Time &dt) {
    if (!path.empty())
        follow_path(dt);

    if (path.empty() && !is_free()) {
        // Align!
        tile_pos = current_task.pos;
        pos = sf::Vector2f(world->tile2world(tile_pos));

        // TODO
        // Work on task here. Not instant T.T
        world->task_done(current_task);
        current_task.is_done = true;
    }
}
void Worker::draw(sf::RenderWindow &w) {
    spr.setPosition(pos.x, pos.y);
    w.draw(spr);

    // Draw path
    sf::VertexArray lines(sf::LinesStrip);
    for (auto next : path) {
        // Draw at center
        auto p = world->tile2world(next);
        auto pos = sf::Vector2f(p.x + tile_width / 2, p.y + tile_width / 2);
        lines.append(sf::Vertex(pos, make_color(0x42F207)));
    }
    w.draw(lines);

    // Draw information
#if 0
    int x = pos.x + 25, y = pos.y - 10, dy = 16;
    stringstream ss;
    ss << "pos: " << pos;
    txt.setString(ss.str());
    txt.setPosition(x, y);
    w.draw(txt);

    y += dy;
    ss.str("");
    ss << "tile" << tile_pos;
    txt.setString(ss.str());
    txt.setPosition(x, y);
    w.draw(txt);
#endif
}

void Worker::follow_path(const sf::Time &dt) {
    // Check for finish
    sf::Vector2f a(pos), b(world->tile2world(path.back()));
    if (len(b - a) < 0.05) {
        path.pop_back();
        //printf("now path of length: %d\n", (int)path.size());
        //for (auto p : path) printf(" %d,%d\n", p.x, p.y);
    }
    if (path.empty()) return;

    sf::Vector2f from(pos), to(world->tile2world(path.back()));
    auto norm = normalize((to - from));
    auto diff = norm * dt.asSeconds() * 100.0f;
    pos = pos + diff;
    tile_pos = world->world2tile(sf::Vector2i(pos));
}

WorkerPtr create_worker(int x, int y, World *world) {
    return WorkerPtr(new Worker(x, y, world));
}

