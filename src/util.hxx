#pragma once

// T.T
#include <set>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stack>
#include <sstream>
#include <deque>
#include <queue>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Color make_color(int hex);

float len(sf::Vector2f v);
sf::Vector2f normalize(sf::Vector2f v);
