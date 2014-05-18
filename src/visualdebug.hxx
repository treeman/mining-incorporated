#pragma once

#include <SFML/Graphics.hpp>
#include "debug.hxx"
#include "pos.hxx"

class VisualDebug : public Debug {
public:
    VisualDebug(IPoint pos);
private:
    void log() override;
    sf::Text txt;
    IPoint pos;
};

