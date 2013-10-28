#include "menustate.h"
#include "engine.h"
#include "splash.h"
#include <SFML/Graphics.hpp>
void MenuState::init() {
    view.setCenter(900, 300);
    view.setSize(900, 600);
    wallbackground.loadFromFile("images/wall1.png");
    wall.setTexture(wallbackground);

    titleFont.loadFromFile("fonts/Minecraftia.ttf");
    title.setFont(titleFont);
    title.setString("Trouble in Lecture Center");
    title.setCharacterSize(40);
    centerOrigin(title);
    title.setPosition(450, 40);

    initialized = true;
}

void MenuState::deinit() {
    initialized = false;
}

void MenuState::handleEvents(sf::Event theEvent) {
    if(theEvent.type != sf::Event::KeyPressed)
        return;

    switch(theEvent.key.code) {
        case sf::Keyboard::Left:
            view.move(-10, 0);
            break;
        case sf::Keyboard::Right:
            view.move(10, 0);
            break;
        default:
            break;
    }
}

void MenuState::draw() {
    sf::RenderWindow &window = engine->getWindow();
    window.setView(view);
    window.draw(wall);

    window.setView(engine->getWindow().getDefaultView());
    window.draw(title);
}

MenuState::MenuState(Engine *_engine) {
    engine = _engine;
}
