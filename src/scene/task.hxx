#pragma once

#include "pos.hxx"
#include "scene/ground.hxx"

// A task is something for workers to do,
// verified by the world so it works.
namespace scene {
    class World;
    class ObjectType;

    // TODO rework... Handling is ugly as hell. Code duplication etc. Yuk
    class Task {
    public:
        Task(MapPos pos, float work_time);
        virtual ~Task() { }

        virtual string to_string() const = 0;
        virtual void draw_preview(sf::RenderWindow &, World *) { }

        MapPos get_target_pos() const;
        float get_work_time() const;

        virtual void handle_completion(World *world) = 0;
    protected:
        MapPos pos;
        float work_time;
    };

    class MineTask : public Task {
    public:
        MineTask(MapPos pos);

        string to_string() const override;

        void draw_preview(sf::RenderWindow &w, World *world) override;
        void handle_completion(World *world) override;
    private:
        sf::Sprite spr;
    };

    class BuildGroundTask : public Task {
    public:
        BuildGroundTask(const Ground *o, MapPos pos);

        string to_string() const override;

        const Ground *ground;

        void draw_preview(sf::RenderWindow &w, World *world) override;
        void handle_completion(World *world) override;
    private:
        sf::Sprite spr;
    };

    class BuildObjectTask : public Task {
    public:
        BuildObjectTask(const ObjectType *type, MapPos pos);

        string to_string() const override;

        const ObjectType *type;

        void draw_preview(sf::RenderWindow &w, World *world) override;
        void handle_completion(World *world) override;
    private:
        sf::Sprite spr;
    };

} // Scene

