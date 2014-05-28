#include "butler.hxx"
#include "scene/task.hxx"
#include "scene/world.hxx"

namespace scene {

BuildGroundTask::BuildGroundTask(const Ground *o, MapPos p) : ground(o), pos(p)
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

MineTask::MineTask(MapPos p) : pos(p)
{
    spr = create_sprite("mine_preview.png");
    spr.setColor(sf::Color(255, 255, 255, 100));
}

string MineTask::to_string() const {
    return "mine " + pos.to_string();
}

void MineTask::draw_preview(sf::RenderWindow &w, World *world) {
    WorldPos wpos = world->map2world(pos);
    spr.setPosition(wpos.pos);
    w.draw(spr);
}

} // Scene

