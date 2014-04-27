#include <memory>
using namespace std;

#include "butler.hxx"

map<string, FontPtr> fnts;
map<string, TexPtr> texs;

FontPtr get_font(string path) {
    auto it = fnts.find(path);
    if (it != fnts.end()) return it->second;

    FontPtr fnt(new sf::Font);
    string realpath = "fnt/" + path;
    if (!fnt->loadFromFile(realpath)) {
        printf("Error! Couldn't load font: %s\n", realpath.c_str());
        exit(-1);
    }
    fnts.insert(make_pair(path, fnt));
    return fnt;
}

TexPtr get_sprite(string path) {
    auto it = texs.find(path);
    if (it != texs.end()) return it->second;

    TexPtr tex(new sf::Texture);
    string realpath = "gfx/" + path;
    if (!tex->loadFromFile(realpath)) {
        printf("Error! Couldn't load texture: %s\n", realpath.c_str());
        return TexPtr();
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

