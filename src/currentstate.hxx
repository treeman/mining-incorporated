#pragma once

#include <memory>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
#include "state.hxx"

bool has_state();
shared_ptr<State> current_state();
void push_state(shared_ptr<State> next);
void pop_state();
void push_next_state(string next, sf::RenderWindow &w);
void clean_states();
