#include <memory>
using namespace std;

#include "abort.hxx"
#include "butler.hxx"

map<string, shared_ptr<sf::Font>> fnts;
map<string, shared_ptr<sf::Texture>> texs;

shared_ptr<sf::Font> get_font(string path) {
    auto it = fnts.find(path);
    if (it != fnts.end()) return it->second;

    shared_ptr<sf::Font> fnt(new sf::Font);
    string realpath = "fnt/" + path;
    if (!fnt->loadFromFile(realpath)) {
        abort_game("Error! Couldn't load font: %s\n", realpath);
    }
    fnts.insert(make_pair(path, fnt));
    return fnt;
}

shared_ptr<sf::Texture> get_sprite(string path) {
    auto it = texs.find(path);
    if (it != texs.end()) return it->second;

    shared_ptr<sf::Texture> tex(new sf::Texture);
    string realpath = "gfx/" + path;
    if (!tex->loadFromFile(realpath)) {
        abort_game("Error! Couldn't load texture: %s\n", realpath);
    }
    texs.insert(make_pair(path, tex));
    return tex;
}

sf::Text create_txt(string path, int size, string txt) {
    sf::Text res(txt, *get_font(path), size);
    return res;
}

sf::Sprite create_sprite(string path) {
    auto tex = get_sprite(path);
    if (!tex) return sf::Sprite();
    return sf::Sprite(*tex);
}

