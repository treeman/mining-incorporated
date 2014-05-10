#include "guiobject.hxx"

bool GuiObject::is_over(int x, int y) const {
    return bounds().contains(sf::Vector2f(x, y));
}

bool GuiObject::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseMoved:
            if (!is_over(e.mouseMove.x, e.mouseMove.y)) {
                handle_nonhover();
                return true;
            }
            else {
                handle_hover();
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (!is_over(e.mouseButton.x, e.mouseButton.y)) return true;
            handle_click(e.mouseButton.button);
            break;
        case sf::Event::MouseButtonReleased:
            if (!is_over(e.mouseButton.x, e.mouseButton.y)) return true;
            handle_release(e.mouseButton.button);
        default: break;
    }

    return false;
}

