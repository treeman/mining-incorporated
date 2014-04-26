#include "worker.hxx"
#include "butler.hxx"

Worker::Worker(int x, int y) : pos(x, y){
    spr = create_sprite("worker.png");
}

void Worker::update(const sf::Time &dt) {
}
void Worker::draw(sf::RenderWindow &w) {
    spr.setPosition(pos.x, pos.y);
    w.draw(spr);
}

WorkerPtr create_worker(int x, int y) {
    return WorkerPtr(new Worker(x, y));
}

