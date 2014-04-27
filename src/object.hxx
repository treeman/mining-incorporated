#pragma once

#include "util.hxx"
#include "objecttype.hxx"

class Object {
public:
    Object(ObjectType type);

    void set_pos(int x, int y);
    void draw(sf::RenderWindow &w);
private:
    sf::Sprite spr;
};

typedef shared_ptr<Object> ObjectPtr;

ObjectPtr make_object(ObjectType type);
