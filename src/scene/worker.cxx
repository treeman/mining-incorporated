#include "butler.hxx"
#include "locator.hxx"
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
}

WorldPos Worker::get_pos() const {
    return world_pos;
}
int Worker::on_floor() const {
    return world_pos.floor;
}
bool Worker::is_free() const {
    return current_task == nullptr;
}

bool Worker::assign_task(shared_ptr<Task> task) {
    if (!is_free()) return false;

    if (auto t = dynamic_cast<BuildGroundTask*>(task.get())) {
        L_("Building ground at %s\n", t->pos.to_string());
        if (map_pos == t->pos) {
            current_task = task;
        }
        else {
            path = world->pathfind(map_pos, t->pos);
            p_ind = 0;
            path.print();

            if (path.empty()) return false;
            current_task = task;
        }
        //has_work_time = false;
        return true;
    }
    else {
        L_("unknown task %s in worker\n", task->to_string());
        return false;
    }
}

void Worker::update(const sf::Time &dt) {
    // TODO fix with new positions!
    if (!path.empty())
        follow_path(dt);

    // TODO this causes a jump.
    if (!path.empty() && map_pos == path.goal() && !is_free()) {
        // Align!
        //world_pos = world->map2world(map_pos);

        // Work on task, it's not instant.
        /*
        if (!has_work_time) {
            has_work_time = true;

            work_time = 0;

            if (current_task.type == BuildRoom) {
                // Need to remove current tile
                RoomType curr_type = world->get_tile_type(tile_pos.x, tile_pos.y);
                work_time += get_info(curr_type)->remove_time;
                // Time to build current tile
                work_time += get_info(current_task.room_type)->build_time;
            }
            else if (current_task.type == PlaceObject) {
                // TODO
            }

            work_clock.restart();
            progressbar.set_target_time(work_time);
            progressbar.reset();
        }
        */

        //float work_done = work_clock.getElapsedTime().asSeconds();
        //progressbar.set_completion(work_done);

        //if (work_done >= work_time) {
            //world->task_done(current_task);
            //current_task.is_done = true;
            //has_work_time = false;
        //}
        L_("Done!\n");
        current_task = nullptr;
    }

    //progressbar.set_position(pos.x, pos.y - 11);
}
void Worker::draw(sf::RenderWindow &w) {
    spr.setPosition(world_pos.pos.x, world_pos.pos.y);
    w.draw(spr);
    if (has_work_time && !is_free())
        progressbar.draw(w);

    // Debug things ^^
#if 1
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

// TODO This is stuttering like crazy!
void Worker::follow_path(const sf::Time &dt) {
    if (path.empty() || map_pos == path.goal()) return;
    if (p_ind >= path.size()) L_("!!!\n");

    FPoint from(world_pos.pos), to(world->map2world(path[p_ind]).pos);
    if (from.dist(to) < 0.001) {
        ++p_ind;
        to = world->map2world(path[p_ind]).pos;
    }

    auto norm = (to - from).normalize();
    auto diff = norm * dt.asSeconds() * 100.0f;
    world_pos.pos = world_pos.pos + diff;
    map_pos = world->world2map(world_pos);
}

} // Scene

