#include "menustate.h"
#include "engine.h"
#include "splash.h"
#include "defaults.h"

#include <SFML/Graphics.hpp>

void MenuState::init() {
    currentMenuItem = 0;

    view.setCenter(450, 300);
    view.setSize(900, 600);
    wallbackground.loadFromFile("images/wall3.png");
    wall.setTexture(wallbackground);

    titleFont.loadFromFile("fonts/Minecraftia.ttf");
    title.setFont(titleFont);
    title.setString("Trouble in Lecture Center");
    title.setCharacterSize(40);
    centerOrigin(title);
    title.setPosition(450, 50);

    menuFont.loadFromFile(DEFAULT_FONT);
    menuItem.setFont(menuFont);
    menuItem.setCharacterSize(28);
    menuItem.setPosition(450, 550);

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
            if (currentMenuItem > 0) {
                view.move(-450, 0);
                currentMenuItem--;
            }
            break;
        case sf::Keyboard::Right:
            if (currentMenuItem < (sizeof(menuItems)/sizeof(menuItems[0]))-1) {
                view.move(450, 0);
                currentMenuItem++;
            }
            break;
        case sf::Keyboard::Return:
            switch(currentMenuItem) {
                case 0: //new game
                    this->changeState = true;
                    this->newState = EState::Intro;
                    break;
                case 1: //load
                    break;
                case 2: //settings
                    break;
                case 3: //about
                    setNewState(EState::About);
                    break;
                case 4: //exit
                    if (WRITE_TO_LOG) engine->getLogFile()->writeToLog("Exitting application");
                    exit(0);            // tymczasowo, później to zmienić !!!
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void MenuState::draw() {
    sf::RenderWindow *window = engine->getWindow();
    window->setView(view);
    window->draw(wall);

    window->setView(window->getDefaultView());
    window->draw(title);

    menuItem.setString(menuItems[currentMenuItem]);
    centerOrigin(menuItem);
    window->draw(menuItem);

}

MenuState::MenuState(Engine *_engine) {
    engine = _engine;
}
