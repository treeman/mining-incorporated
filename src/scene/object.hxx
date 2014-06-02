#pragma once

#include "scene/world.hxx"
#include "scene/objecttype.hxx"

namespace scene {

    class Object {
    public:
        Object(const ObjectType *type, World *world);

        string to_string() const;
        const ObjectType *get_type() const;

        void set_pos(const WorldPos &p);

        void draw(sf::RenderWindow &w);
    private:
        World *world;
        const ObjectType *type;

        WorldPos pos;
        sf::Sprite spr;
    };
}

