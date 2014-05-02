#pragma once

#include "basicincludes.hxx"
#include "inputhandler.hxx"

class InputQueue : public InputHandler {
public:
    void add_handler(InputHandler *h);

    bool handle_input(const sf::Event &e);
private:
    // TODO priority queue later so we can sort?
    deque<InputHandler*> q;
};

