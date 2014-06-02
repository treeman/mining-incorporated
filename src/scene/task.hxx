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
        BuildGroundTask(const Ground *o, MapPos pos);

        string to_string() const override;

        const Ground *ground;
        MapPos pos;

        void draw_preview(sf::RenderWindow &w, World *world) override;
    private:
        sf::Sprite spr;
    };

    class BuildObjectTask : public Task {
    public:
        BuildObjectTask(const ObjectType *type, MapPos pos);

        string to_string() const override;

        const ObjectType *type;
        MapPos pos;

        void draw_preview(sf::RenderWindow &w, World *world) override;
    private:
        sf::Sprite spr;
    };

} // Scene

