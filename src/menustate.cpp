#include "menustate.h"
#include "engine.h"
#include "splash.h"
#include "player.h"
#include "defaults.h"
#include "gamestate.h"
#include "level.h"

#include <SFML/Graphics.hpp>

#include <fstream>

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

void MenuState::loader() { //load
    //initial loading
    std::ifstream s("saves/save_player.bin");
    if(!s.is_open())
        return;

    int profession;
    std::string name;
    s >> profession;
    s >> name;
    s.close();
    //creating and loading player
    Player* player;
    switch(profession) {
        case 0: //archer
            player = new CArcher(name);
            break;
        case 1: //mage
            player = new CMage(name);
            break;
        case 2: //knight
            player = new CKnight(name);
            break;
        default:
            player = NULL;
            break;
    }
    player->load();
    dynamic_cast<GameState*>(engine->getStateManager()->getStateObject(EState::Game))->player = player;

    //loading map
    Level *l = new Level("saves/save_map.bin", player, false);
    dynamic_cast<GameState*>(engine->getStateManager()->getStateObject(EState::Game))->lvl = l;
    setNewState(EState::Game);
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
                case 1: 
                    this->loader();
                    break;
                case 2: //settings
                    break;
                case 3: //about
                    this->setNewState(EState::About);
                    break;
                case 4: //exit
                    if (WRITE_TO_LOG) engine->getLogFile()->writeToLog("Exitting application");
                    exit(0);
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
