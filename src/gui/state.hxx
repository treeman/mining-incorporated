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
        State(Interface *gui, scene::World *world);
        virtual ~State() noexcept = default;

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
        MATERIAL,
        PLANNING,

        NUM_STATES,
    };

    string type2string(GuiState type);

    class InfoState : public State {
    public:
        InfoState(Interface *gui, scene::World *world);

        bool handle_input(const sf::Event &e) override;
        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    };

    class MaterialState : public State {
    public:
        MaterialState(Interface *gui, scene::World *world);

        void reset() override;

        void handle_event(const gui::Event &) override;
        bool handle_input(const sf::Event &e) override;

        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    private:
        shared_ptr<scene::Material> material;
        unique_ptr<Selection> selection;
        unique_ptr<sf::Sprite> preview_spr;
    };

    class PlanningState : public State {
    public:
        PlanningState(Interface *gui, scene::World *world);

        void reset() override;

        void handle_event(const gui::Event &) override;
        bool handle_input(const sf::Event &e) override;

        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    private:
        shared_ptr<scene::PlanningObject> obj;
        unique_ptr<Selection> selection;
    };

}

