#include "gui/selection.hxx"

SelectionArea::SelectionArea() : start(-1), end(-1) {

}

Selection::Selection() : active(false) {

}

void Selection::begin(const WorldPos &start) {
    active = true;
    area.start = start;
    area.end = start;
}
void Selection::extend(const WorldPos &end) {
    area.end = end;
}
void Selection::clear() {
    active = false;
}
bool Selection::is_active() const {
    return active;
}
bool Selection::is_point() const {
    return is_active() && area.start == area.end;
}

