#include "butler.hxx"
#include "locator.hxx"
#include "scene/task.hxx"
#include "scene/objecttype.hxx"
#include "scene/object.hxx"
#include "scene/world.hxx"

namespace scene {

Task::Task(MapPos _pos, float _work_time) : spr(nullptr), pos(_pos), work_time(_work_time)
{

}

void Task::set_preview(shared_ptr<sf::Sprite> _spr) {
    spr = _spr;
}
void Task::draw_preview(sf::RenderWindow &w, World *world) {
    if (spr != nullptr) {
        WorldPos wpos = world->map2world(pos);
        spr->setPosition(wpos.pos);
        w.draw(*spr);
    }
}

MapPos Task::get_target_pos() const {
    return pos;
}
float Task::get_work_time() const {
    return work_time;
}

MineTask::MineTask(MapPos p) : Task(p, 3)
{
    shared_ptr<sf::Sprite> spr(new sf::Sprite(create_sprite("mine_preview.png")));
    spr->setColor(sf::Color(255, 255, 255, 100));
    set_preview(spr);
}

string MineTask::to_string() const {
    return "mine " + pos.to_string();
}

void MineTask::handle_completion(World *world) {
    auto tile = world->get_tile(get_target_pos());
    tile->set_ground(Locator::get_object_factory().get_ground("stone"));
}

BuildGroundTask::BuildGroundTask(const Ground *o, MapPos p) : Task(p, o->build_time), ground(o)
{
    shared_ptr<sf::Sprite> spr(new sf::Sprite(create_sprite(ground->spr)));
    spr->setColor(sf::Color(255, 255, 255, 100));
    set_preview(spr);
}

string BuildGroundTask::to_string() const {
    return "build ground " + pos.to_string();
}

void BuildGroundTask::handle_completion(World *world) {
    auto tile = world->get_tile(get_target_pos());
    tile->set_ground(ground);
}

BuildObjectTask::BuildObjectTask(const ObjectType *t, MapPos p) : Task(p, 2), type(t)
{
    shared_ptr<sf::Sprite> spr(new sf::Sprite(create_sprite(type->spr)));
    spr->setColor(sf::Color(255, 255, 255, 100));
    set_preview(spr);
}

string BuildObjectTask::to_string() const {
    return "build " + type->to_string() + " at " + pos.to_string();
}

void BuildObjectTask::handle_completion(World *world) {
    auto tile = world->get_tile(get_target_pos());
    shared_ptr<Object> obj(new Object(type, world));
    tile->set_object(obj);
}

} // Scene

