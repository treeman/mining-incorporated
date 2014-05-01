#include "inputbox.hxx"
#include "butler.hxx"

InputBox::InputBox(int x, int y) {
    txt = create_txt("arial.ttf", 10);
    txt.setPosition(x, y);
}

void InputBox::add_char(char c) { s.push_back(c); }
void InputBox::del_char() { if (!s.empty()) s.pop_back(); }
void InputBox::clear() { s.clear(); }
string InputBox::get_string() const { return s; }

void InputBox::update(const sf::Time &dt) {

}
void InputBox::draw(sf::RenderWindow &w) {
    txt.setString(s);
    w.draw(txt);
}

