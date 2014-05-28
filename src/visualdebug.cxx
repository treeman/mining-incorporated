#include "visualdebug.hxx"
#include "locator.hxx"
#include "butler.hxx"

VisualDebug::VisualDebug(IPoint p) : pos(p) {
    txt = create_txt("consola.ttf", 12);
    txt.setColor(sf::Color::White);
}

void VisualDebug::log() {
    sf::RenderWindow &w = Locator::get_window();
    int x = pos.x, y = pos.y;
    const int h = 14;
    for (auto &p : persistent) {
        txt.setString(p.first + ": " + p.second);
        txt.setPosition(x, y);
        y += h;
        w.draw(txt);
    }

    for (auto &s : tmps) {
        txt.setString(s);
        txt.setPosition(x, y);
        y += h;
        w.draw(txt);
    }
}

