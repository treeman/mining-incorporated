#include "inputqueue.hxx"

void InputQueue::add_handler(InputHandler *h) {
    q.push_back(h);
}

bool InputQueue::handle_input(const sf::Event &e) {
    for (InputHandler *h : q) {
        if (!h->handle_input(e))
            return false;
    }
    return true;
}

