#pragma once

#include <SFML/Graphics.hpp>
#include "debug.hxx"

class VisualDebug : public Debug {
public:
    VisualDebug();
private:
    void log() override;
    sf::Text txt;
};

