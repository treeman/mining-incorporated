#include "log.hxx"
#include "constants.hxx"
#include "butler.hxx"
#include "locator.hxx"
#include "util/ext.hxx"
#include "util/rand.hxx"
#include "scene/world.hxx"
#include "scene/map.hxx"
#include "scene/task.hxx"
#include "scene/material.hxx"
#include "scene/ore.hxx"

namespace scene {

const int view_xoff = (screen_width - world_width) / 2;
const int view_yoff = (screen_height - world_height) / 2;

World::World(sf::RenderWindow &_w) : task_debug({630, 145}), w(_w),
    view(sf::FloatRect(0, 0, screen_width, screen_height))
{
    view.move(-view_xoff, -view_yoff);
    map = Locator::get_object_factory().make_map();

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

WorldPos World::clamp(const WorldPos &p) const {
    WorldPos res(p);
    res.pos = p.pos.clamp(0, world_width, 0, world_height);
    return res;
}

shared_ptr<Tile> World::get_tile(const MapPos &p) const {
    return map->tile(p);
}
bool World::can_build(const MapPos &p, shared_ptr<Material>) const {
    // TODO move to lua
    const Ground *ground = get_tile(p)->get_ground();
    if (dynamic_cast<const Ore*>(ground))
        return false;
    return ground->key != "rock";
}
bool World::can_mine(const MapPos &p) const {
    const Ground *ground = get_tile(p)->get_ground();
    if (dynamic_cast<const Ore*>(ground))
        return true;
    // TODO don't hardcode?
    return ground->key == "rock";
}
bool World::can_build(const MapPos &p, shared_ptr<RoomType>) const {
    // TODO move to lua
    const Ground *ground = get_tile(p)->get_ground();
    if (dynamic_cast<const Ore*>(ground))
        return false;
    return ground->key != "rock";
}

int World::num_floors() const { return map->num_floors(); }

void World::handle_input(const sf::Event &e) { }
void World::update(const sf::Time &dt) {
    assign_tasks();

    map->update(dt);
    for (auto worker : workers) {
        worker->update(dt);
    }

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
        if (worker->get_pos().floor == floor)
            worker->draw(w);
    }

    for (auto &room : rooms) {
        //if (room->get_floor() == floor)
            room->draw(w);
    }

    draw_pending_tasks();

    w.setView(curr);
    task_debug.update();
}

void World::push_event(unique_ptr<Event> e) {
    assert(e != nullptr);
    e->handle(this);
}

void World::push_task(shared_ptr<Task> task) {
    //L_("new task: %s\n", task->to_string());
    pending_tasks.push_back(move(task));
}

Path World::pathfind(const MapPos &from, const MapPos &to) const {
    return map->pathfind(from, to);
}
void World::draw_pending_tasks() {
    // Draw unhandler
    for (auto &t : pending_tasks) {
        t->draw_preview(w, this);
    }

    // Draw currently handling
    for (auto &worker : workers) {
        if (worker->has_task())
            worker->get_task()->draw_preview(w, this);
    }
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

//void World::skip_task(shared_ptr<Task> task) {
    //L_("TODO world received a skipped task: %s\n", task->to_string());
    //tasks.push_back(task);
//}
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

// TODO smarter later?
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
shared_ptr<Worker> World::select_worker(const WorldPos &p) {
    for (auto w : workers) {
        if (w->is_on(p)) return w;
    }
    return nullptr;
}

int World::num_workers() const {
    return workers.size();
}

// TODO not always ok...
void World::mark_room(shared_ptr<RoomType> type, MapArea area) {
    //L_("room %s at %s\n", type->to_string(), area.to_string());

    shared_ptr<Room> room;
    bool create_new = true;
    for (auto r : rooms) {
        if (r->can_extend(type, area)) {
            //L_("extending...\n");
            r->extend(area);
            create_new = false;
            room = r;
        }
        else {
            r->remove(area);
        }
    }

    remove_empty_rooms();

    if (create_new) {
        //L_("New room\n");
        room.reset(new Room(type, area, this));
        rooms.push_back(room);
    }

    // Repoint tiles
    for (MapPos p : area) {
        get_tile(p)->set_room(room);
    }
}
void World::remove_room(MapArea area) {
    for (auto r : rooms)
        r->remove(area);

    for (MapPos p : area) {
        get_tile(p)->set_room(nullptr);
    }

    remove_empty_rooms();
}

shared_ptr<Room> World::get_room(const MapPos &p) const {
    return get_tile(p)->get_room();
}

void World::remove_empty_rooms() {
    // Find and remove empty rooms
    vector<shared_ptr<Room>> next_rooms;
    next_rooms.reserve(rooms.size());
    for (auto r : rooms) {
        if (!r->empty())
            next_rooms.push_back(r);
        //else
            //L_("Removing room!\n");
    }
    rooms.swap(next_rooms);
}

}; // Scene

