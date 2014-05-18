#include "scene/path.hxx"

namespace scene {

void Path::draw(sf::RenderWindow &w, World *world) {

}

Path &Path::operator << (const MapPos &p) {
    path.push_back(p);
    return *this;
}

} // scene

