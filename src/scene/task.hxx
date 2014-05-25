#pragma once

#include "scene/ground.hxx"
#include "pos.hxx"

// A task is something for workers to do,
// verified by the world so it works.
namespace scene {
    class World;

    class Task {
    public:
        virtual ~Task() { }

        virtual string to_string() const = 0;
        virtual void draw_preview(sf::RenderWindow &, World *) { }
    };

    class MineTask : public Task {
    public:
        MineTask(MapPos pos);

        string to_string() const override;

        MapPos pos;

        void draw_preview(sf::RenderWindow &w, World *world) override;
    private:
        sf::Sprite spr;
    };

    class BuildGroundTask : public Task {
    public:
        BuildGroundTask(shared_ptr<const Ground> o, MapPos pos);

        string to_string() const override;

        shared_ptr<const Ground> ground;
        MapPos pos;

        void draw_preview(sf::RenderWindow &w, World *world) override;
    private:
        sf::Sprite spr;
    };

} // Scene

