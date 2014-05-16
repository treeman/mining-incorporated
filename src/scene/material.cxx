#include "util/fmt.hxx"
#include "scene/material.hxx"

namespace scene {

Material::Material(shared_ptr<const Ground> _ground, int _cost) : ground(_ground), cost(_cost) {

}

string Material::to_string() const {
    return fmt("ground material type %s costing %d", ground->key, cost);
}

} // scene

