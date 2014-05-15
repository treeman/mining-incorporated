#pragma once

#include <SFML/Graphics.hpp>

#include "gui/event.hxx"
#include "gui/selection.hxx"

namespace scene {
    class World;
};

namespace gui {

    class Interface;

    class State {
    public:
        State();
        virtual ~State() noexcept = default;

        void init(Interface *gui, scene::World *world);
        virtual void reset() { };

        virtual void handle_event(const gui::Event &) { }
        virtual bool handle_input(const sf::Event &e) = 0;
        virtual void update(const sf::Time &dt) = 0;
        virtual void draw(sf::RenderWindow &w) = 0;
    protected:
        Interface *gui;
        scene::World *world;
    };


    // States:
    // Info
    // Build room
    // (Demolish)
    // Build object -or- room selection!
    // (Sell object)
    // Mine (?)
    enum class GuiState : unsigned {
        INFO,
        PLANNING,

        NUM_STATES,
    };

    string type2string(GuiState type);

    class InfoState : public State {
    public:
        bool handle_input(const sf::Event &e) override;
        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    };

    class PlanningState : public State {
    public:
        PlanningState();

        void reset() override;

        void handle_event(const gui::Event &) override;
        bool handle_input(const sf::Event &e) override;
    private:
        void move(const WindowPos &p);
        void left_click(const WindowPos &p);
        void right_click(const WindowPos &p);
        void left_release(const WindowPos &p);
        void right_release(const WindowPos &p);

    public:
        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    private:
        Selection selection;
        shared_ptr<scene::PlanningObject> obj;
        bool erase;
    };

}

