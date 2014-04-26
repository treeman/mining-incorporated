#include "worker.hxx"
#include "butler.hxx"
#include "world.hxx"
#include "constants.hxx"

Worker::Worker(int x, int y, World *_world) : pos(x, y), world(_world){
    spr = create_sprite("worker.png");
    tile_pos = world->world2tile(x, y);
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
    sf::Vector2f from(pos), to(path.back());
    auto norm = normalize((to - from));
    //printf("%f,%f -> %f,%f: %f,%f\n", from.x, from.y, to.x, to.y, norm.x, norm.y);
    auto diff = norm * dt.asSeconds() * 100.0f;
    pos = pos + diff;
    tile_pos = world->world2tile(sf::Vector2i(pos));
}
void Worker::set_path(vector<sf::Vector2i> p) {
    path = p;
    //printf("has path of length: %d\n", (int)path.size());
    //for (auto p : path) printf(" %d,%d\n", p.x, p.y);
}

void Worker::update(const sf::Time &dt) {
    if (!path.empty())
        follow_path(dt);
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
    //auto pos = sf::Vector2f(tile_pos.x + tile_width / 2, tile_pos.y + tile_width / 2);
    //lines.append(sf::Vertex(pos, make_color(0x42F207)));
    w.draw(lines);
}

WorkerPtr create_worker(int x, int y, World *world) {
    return WorkerPtr(new Worker(x, y, world));
}

