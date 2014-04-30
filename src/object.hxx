#pragma once

#include "basicincludes.hxx"
#include "objecttype.hxx"

class Object {
public:
    Object(ObjectType type);

    ObjectType get_type();
    void set_pos(int x, int y);
    void draw(sf::RenderWindow &w);
private:
    sf::Sprite spr;
    ObjectType type;
};

typedef shared_ptr<Object> ObjectPtr;

ObjectPtr make_object(ObjectType type);
