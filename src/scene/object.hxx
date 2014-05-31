#pragma once

#include "scene/world.hxx"
#include "scene/objecttype.hxx"

namespace scene {

    class Object {
    public:
        Object(shared_ptr<ObjectType> type, World *world);

        string to_string() const;
        shared_ptr<ObjectType> get_type() const;

        void set_pos(const WorldPos &p);

        void draw(sf::RenderWindow &w);
    private:
        World *world;
        shared_ptr<ObjectType> type;

        WorldPos pos;
        sf::Sprite spr;
    };
}

