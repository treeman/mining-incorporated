#pragma once

#include "std.hxx"
#include "pos.hxx"

// Some extensions to sfml.
sf::Color make_color(int a, int r, int g, int alpha = 0xff);
sf::Color make_color(int hex);
sf::Color make_color(int hex, int alpha);
sf::Color make_alpha_color(int hex);
sf::ConvexShape make_rect(const sf::FloatRect &rect);

WindowPos get_mpos();
