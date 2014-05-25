#include "butler.hxx"
#include "scene/task.hxx"
#include "scene/world.hxx"

namespace scene {

BuildGroundTask::BuildGroundTask(shared_ptr<const Ground> o, MapPos p) : ground(o), pos(p)
{
    spr = create_sprite(ground->spr);
    spr.setColor(sf::Color(255, 255, 255, 100));
}

string BuildGroundTask::to_string() const {
    return "build ground " + pos.to_string();
}

void BuildGroundTask::draw_preview(sf::RenderWindow &w, World *world) {
    WorldPos wpos = world->map2world(pos);
    spr.setPosition(wpos.pos);
    w.draw(spr);
}

} // Scene

