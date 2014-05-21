#include "constants.hxx"
#include "butler.hxx"
#include "locator.hxx"
#include "util/ext.hxx"
#include "util/rand.hxx"
#include "scene/world.hxx"
#include "scene/map.hxx"
#include "scene/task.hxx"
#include "scene/material.hxx"

namespace scene {

const int view_xoff = (screen_width - world_width) / 2;
const int view_yoff = (screen_height - world_height) / 2;

World::World(sf::RenderWindow &_w) : task_debug({630, 145}), w(_w),
    view(sf::FloatRect(0, 0, screen_width, screen_height))
{
    view.move(-view_xoff, -view_yoff);
    map = make_map();

    new_worker();

    Locator::get_settings().register_bool("debug_tasks", false);
    Locator::get_settings().register_bool("debug_positions", false);
}

bool World::in_world(const WindowPos &p, int floor) const {
    const WorldPos wp(p.x  - view_xoff, p.y - view_yoff, floor);
    return in_world(wp);
}
bool World::in_world(const WorldPos &p) const {
    return 0 <= p.pos.x && p.pos.x < world_width
        && 0 <= p.pos.y && p.pos.y < world_height
        && 0 <= p.floor && p.floor < map->num_floors();
}
WorldPos World::map2world(const MapPos &p) const {
    return WorldPos(p.pos.x * tile_width, p.pos.y * tile_width, p.floor);
}
WorldPos World::window2world(const WindowPos &p, int floor) const {
    const WorldPos res(p.x  - view_xoff, p.y - view_yoff, floor);
    assert(in_world(res));
    return res;
}
MapPos World::window2map(const WindowPos &p, int floor) const {
    return world2map(window2world(p, floor));
}
MapPos World::world2map(const WorldPos &p) const {
    assert(in_world(p));
    return MapPos(p.pos.x / tile_width, p.pos.y / tile_width, p.floor);
}
WindowPos World::map2window(const MapPos &p) const {
    return WindowPos(p.pos.x * tile_width + view_xoff, p.pos.y * tile_width + view_yoff);
}
WindowPos World::world2window(const WorldPos &p) const {
    return map2window(world2map(p));
}

shared_ptr<Tile> World::get_tile(const MapPos &p) const {
    return map->tile(p);
}

int World::num_floors() const { return map->num_floors(); }

void World::handle_input(const sf::Event &e) { }
void World::update(const sf::Time &dt) {
    assign_tasks();

    map->update(dt);
    for (auto worker : workers) {
        worker->update(dt);
    }

    /*
    // Add in debug info
    if (Locator::get_settings().get_bool("debug_positions")) {
        WindowPos mp(get_mpos());
        if (in_world(mp)) {
            WorldPos wpos(window2world(mp));
            MapPos map_pos(world2map(wpos));
            // Treat as int position, prevent unnecessary decimals
            D_.set_key("world", IPoint(wpos.pos).to_string() + " (" + to_string(wpos.floor) + ")");
            D_.set_key("map", map_pos.to_string());
        }
        else {
            D_.set_key("world", "invalid");
            D_.set_key("map", "invalid");
        }
    }
    */

    if (Locator::get_settings().get_bool("debug_tasks")) {
        task_debug.tmp("pending tasks: " + to_string(pending_tasks.size()));
        for (auto &t : pending_tasks) {
            task_debug.tmp(t->to_string());
        }
    }
}
void World::draw(int floor) {
    sf::View curr = w.getView();
    w.setView(view);

    map->draw(w, floor);

    for (auto &worker : workers) {
        worker->draw(w);
    }

    w.setView(curr);
    task_debug.update();
}

void World::push_task(shared_ptr<Task> task) {
    //L_("new task: %s\n", task->to_string());
    pending_tasks.push_back(move(task));
}

Path World::pathfind(const MapPos &from, const MapPos &to) const {
    return map->pathfind(from, to);
}

void World::new_worker() {
    // TODO
    // Some marker that we can't hire? Or something?
    if ((int)workers.size() >= resources.max_workers) return;

    workers.push_back(shared_ptr<Worker>(new Worker(WorldPos(0, 0, 0), this)));
}

// TODO choose based on task and closeness.
shared_ptr<Worker> World::choose_free_worker() {
    for (auto w : workers) {
        if (w->is_free()) return w;
    }
    return nullptr;
}

void World::skip_task(shared_ptr<Task> task) {
    L_("TODO world received a skipped task: %s\n", task->to_string());
    //tasks.push_back(task);
}
void World::assign_tasks() {
    // TODO make something better...
    // 1. Take into account time for workers doing tasks, might be able to do tasks close.
    deque<shared_ptr<Task>> unfinished;
    for (shared_ptr<Task> t : pending_tasks) {
        bool assigned = false;
        for (auto worker : workers) {
            if (!worker->is_free()) continue;
            if (worker->assign_task(t)) {
                assigned = true;
                break;
            }
        }
        if (!assigned) unfinished.push_back(t);
    }

    pending_tasks.swap(unfinished);
}

const Resources &World::get_resources() const {
    return resources;
}

shared_ptr<Worker> World::select_closest_worker(const WorldPos &p) {
    shared_ptr<Worker> res{ nullptr };
    float closest = numeric_limits<float>::infinity();
    for (auto w : workers) {
        float d =  w->get_pos().pos.dist(p.pos);
        if (d < closest) {
            closest = d;
            res = w;
        }
    }
    return res;
}

int World::num_workers() const {
    return workers.size();
}

}; // Scene

