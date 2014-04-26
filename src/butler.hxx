#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <memory>

using namespace std;

typedef shared_ptr<sf::Font> FontPtr;
typedef shared_ptr<sf::Texture> TexPtr;

FontPtr get_font(string path);
TexPtr get_texture(string path);

sf::Text create_txt(string path, int size, string txt = "");
sf::Sprite create_sprite(string path);
