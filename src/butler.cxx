#include <memory>
using namespace std;

#include "butler.hxx"

map<string, shared_ptr<sf::Font>> fnts;

shared_ptr<sf::Font> get_font(string path) {
    auto it = fnts.find(path);
    if (it != fnts.end()) return it->second;

    shared_ptr<sf::Font> fnt(new sf::Font);
    string realpath = "fnt/" + path;
    if (!fnt->loadFromFile(realpath)) {
        printf("Error! Couldn't load font: %s\n", realpath.c_str());
        exit(-1);
    }
    fnts.insert(make_pair(path, fnt));
    return fnt;
}

sf::Text create_txt(string path, int size, string txt) {
    sf::Text res(txt, *get_font(path), size);
    return res;
}

