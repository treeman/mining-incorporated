#pragma once

#include "std.hxx"
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

