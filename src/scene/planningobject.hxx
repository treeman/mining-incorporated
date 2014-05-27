#pragma once

#include "std.hxx"

namespace scene {

    enum class PlanningType : unsigned {
        ROOM,
        OBJECT,

        NUM_OBJECTS,
    };

    string type2string(PlanningType type);

    class PlanningObject {
    public:
        PlanningObject(string spr, PlanningType type, sf::Color color = sf::Color::White);

        PlanningType get_type() const;
        string to_string() const;

        void set_pos(int x, int y);
        void draw(sf::RenderWindow &w);
    private:
        sf::Sprite spr;
        PlanningType type;
    };

}

