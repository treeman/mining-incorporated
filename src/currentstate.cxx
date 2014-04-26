#include <stack>

#include "currentstate.hxx"
#include "help.hxx"
#include "game.hxx"

stack<shared_ptr<State>> s;

bool has_state() {
    return !s.empty();
}
shared_ptr<State> current_state() {
    return s.top();
}
void push_state(shared_ptr<State> next) {
    s.push(next);
}
void pop_state() {
    s.pop();
}
void push_next_state(string next, sf::RenderWindow &w) {
    //printf("creating state %s\n", next.c_str());
    if (next == "help") push_state(shared_ptr<State>(new HelpState(w)));
    else if (next == "game") push_state(shared_ptr<State>(new GameState(w)));
    else printf("state %s not found.\n", next.c_str());
}

