#include "butler.hxx"
#include "log.hxx"
#include "constants.hxx"
#include "scene/worker.hxx"
#include "scene/world.hxx"

namespace scene {

Worker::Worker(const WorldPos &p, World *_world) : world(_world), p_ind(0),
    world_pos(p), map_pos(world->world2map(world_pos)), current_task(nullptr)
{
    spr = create_sprite("worker.png");
    txt = create_txt("arial.ttf", 14);
    has_work_time = false;
    work_time = 0;

    fatigue = 1.0;
}

WorldPos Worker::get_pos() const {
    return world_pos;
}
int Worker::on_floor() const {
    return world_pos.floor;
}
bool Worker::is_on(const WorldPos &p) const {
    if (p.floor != world_pos.floor) return false;

    auto rect = spr.getLocalBounds();
    rect.left = world_pos.pos.x;
    rect.top = world_pos.pos.y;

    return rect.contains(p.pos);
}
bool Worker::is_free() const {
    return current_task == nullptr;
}

bool Worker::assign_task(shared_ptr<Task> task) {
    if (!is_free()) return false;

    MapPos target = task->get_target_pos();
    if (map_pos == target) {
        path.clear();
        p_ind = 0;
    }
    else {
        path = world->pathfind(map_pos, target);
        p_ind = 0;

        if (path.empty()) return false;
    }
    current_task = task;
    has_work_time = false;
    return true;
}
bool Worker::has_task() const {
    return get_task() != nullptr;
}
shared_ptr<Task> Worker::get_task() const {
    return current_task;
}

void Worker::update(const sf::Time &dt) {
    if (!path.empty())
        follow_path(dt);

    if (p_ind == path.size() && !is_free()) {
        // Align!
        if (!path.empty()) {
            map_pos = path.goal();
            world_pos = world->map2world(map_pos);
        }

        // Work on task, it's not instant.
        if (!has_work_time) {
            has_work_time = true;

            work_time = current_task->get_work_time();

            // TODO this may crash if setting is missing.
            if (Locator::get_settings().get_bool("build_fast")) {
                work_time /= 20;
            }

            work_clock.restart();
            progressbar.set_target_time(work_time);
            progressbar.reset();
        }

        float work_done = work_clock.getElapsedTime().asSeconds();
        progressbar.set_completion(work_done);

        if (work_done >= work_time) {
            world->push_event(move(unique_ptr<Event>(new HandleEvent(
                [this](World *world) {
                    world->task_done(current_task);
                },
                "Task done: " + current_task->to_string()
            ))));
            has_work_time = false;

            //L_("Done!\n");
            current_task = nullptr;
            path.clear();
        }
    }

    // Update status effects
    // TODO do some more intelligent choices here.
    // TODO specify fatigue level
    fatigue = max(0.0, fatigue - 0.1 * dt.asSeconds());
}
void Worker::draw(sf::RenderWindow &w) {
    spr.setPosition(world_pos.pos.x, world_pos.pos.y);
    w.draw(spr);
    if (has_work_time && !is_free()) {
        progressbar.set_position(world_pos.pos.x, world_pos.pos.y - 11);
        progressbar.draw(w);
    }

    // Debug things ^^
#if 0
    if (current_task != nullptr)
        path.draw(w, world);

    // Draw information
    int x = world_pos.pos.x + 25, y = world_pos.pos.y - 10, dy = 16;
    txt.setString("pos: " + world_pos.to_string());
    txt.setPosition(x + 25, y - 10);
    w.draw(txt);

    y += dy;
    txt.setString("map: " + map_pos.to_string());
    txt.setPosition(x, y);
    w.draw(txt);
#endif
}

void Worker::follow_path(const sf::Time &dt) {
    if (path.empty()) return;
    if (p_ind == path.size()) return;

    FPoint from(world_pos.pos), to(world->map2world(path[p_ind]).pos);
    if (from.dist(to) < 0.05) {
        ++p_ind;
        if (p_ind == path.size()) return;
        to = world->map2world(path[p_ind]).pos;
    }

    FPoint norm = (to - from).normalize();
    FPoint diff = norm * dt.asSeconds() * 100.0f;
    world_pos.pos = world_pos.pos + diff;
    world_pos = world->clamp(world_pos);
    map_pos = world->world2map(world_pos);
}

void Worker::debug() {
    D_.tmp("Worker");
    D_.tmp("pos " + world_pos.to_string());
    D_.tmp(fmt("fatigue: %f", fatigue));
}

} // Scene

