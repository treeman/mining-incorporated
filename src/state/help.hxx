#include "std.hxx"
#include "state/state.hxx"

namespace state {

    class HelpState : public State {
    public:
        HelpState(sf::RenderWindow &w);

        string id() const override { return "help"; }

        void handle_input(const sf::Event &e) override;
        void update(const sf::Time &dt) override;
        void draw() override;
    private:
        sf::Text txt;
        sf::Sprite pic;
    };

}

