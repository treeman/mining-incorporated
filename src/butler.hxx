#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <memory>

using namespace std;

shared_ptr<sf::Font> get_font(string path);
sf::Text create_txt(string path, int size, string txt = "");

