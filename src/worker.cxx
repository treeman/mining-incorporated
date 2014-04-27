#include "worker.hxx"
#include "butler.hxx"
#include "world.hxx"
#include "constants.hxx"

Worker::Worker(int x, int y, World *_world) : pos(x, y), world(_world){
    spr = create_sprite("worker.png");
    tile_pos = world->world2tile(x, y);
    current_task.is_done = true;
}

bool Worker::is_free() {
    return current_task.is_done;
}
void Worker::assign_task(Task task) {
    //printf("I have a task type: %d\n", task.type);

    current_task = task;
    path = world->pathfind(tile_pos, current_task.pos);
}

void Worker::update(const sf::Time &dt) {
    if (!path.empty())
        follow_path(dt);

    if (path.empty() && !is_free()) {
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
        auto pos = sf::Vector2f(next.x + tile_width / 2, next.y + tile_width / 2);
        lines.append(sf::Vertex(pos, make_color(0x42F207)));
    }
    w.draw(lines);
}

void Worker::follow_path(const sf::Time &dt) {
    // Check for finish
    sf::Vector2f a(pos), b(path.back());
    if (len(b - a) < 0.05) {
        path.pop_back();
        //printf("now path of length: %d\n", (int)path.size());
        //for (auto p : path) printf(" %d,%d\n", p.x, p.y);
    }
    if (path.empty()) return;

    // TODO this is jerky!
    sf::Vector2f from(pos), to(path.back());
    auto norm = normalize((to - from));
    auto diff = norm * dt.asSeconds() * 100.0f;
    pos = pos + diff;
    tile_pos = world->world2tile(sf::Vector2i(pos));
}

WorkerPtr create_worker(int x, int y, World *world) {
    return WorkerPtr(new Worker(x, y, world));
}

