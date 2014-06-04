#pragma once

#include "pos.hxx"
#include "scene/ground.hxx"

// A task is something for workers to do,
// verified by the world so it works.
namespace scene {
    class World;
    class ObjectType;

    // TODO rework. Maybe avoid subtyping?
    // At the very least refactor out sprite preview.
    class Task {
    public:
        Task(MapPos pos, float work_time);
        virtual ~Task() { }

        virtual string to_string() const = 0;

        void set_preview(shared_ptr<sf::Sprite> spr);
        // TODO remove world from here.
        // Need to set MapPos and WorldPos at the same time then.
        void draw_preview(sf::RenderWindow &w, World *world);

        MapPos get_target_pos() const;
        float get_work_time() const;

        virtual void handle_completion(World *world) = 0;
    protected:
        shared_ptr<sf::Sprite> spr;
        MapPos pos;
        float work_time;
    };

    class MineTask : public Task {
    public:
        MineTask(MapPos pos);

        string to_string() const override;

        void handle_completion(World *world) override;
    private:
        sf::Sprite spr;
    };

    class BuildGroundTask : public Task {
    public:
        BuildGroundTask(const Ground *o, MapPos pos);

        string to_string() const override;

        const Ground *ground;

        void handle_completion(World *world) override;
    private:
        sf::Sprite spr;
    };

    class BuildObjectTask : public Task {
    public:
        BuildObjectTask(const ObjectType *type, MapPos pos);

        string to_string() const override;

        const ObjectType *type;

        void handle_completion(World *world) override;
    private:
        sf::Sprite spr;
    };

} // Scene

