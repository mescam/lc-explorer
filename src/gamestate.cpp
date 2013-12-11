#include "engine.h"
#include "defaults.h"
#include "gamestate.h"

#include <iostream>

GameState::GameState(Engine *_engine) {
    engine = _engine;
}

void GameState::init() {
	this->maskT.loadFromFile("images/light.png");
	this->maskS.setTexture(this->maskT);

    this->guiFont = new sf::Font();
    this->guiFont->loadFromFile(DEFAULT_FONT);

    for (int i = 0; i < 10; i++) {
        this->guiText[i].setFont(*this->guiFont);
    }

    this->guiText[0].setString("Aomi");
    this->guiText[0].setColor(sf::Color(255,0,0,255));
    this->guiText[0].setCharacterSize(20);
    this->guiText[0].setPosition(10,10);

    this->guiText[1].setString("Level 1 Mage");
    this->guiText[1].setCharacterSize(20);
    this->guiText[1].setPosition(10,35);

    this->guiText[2].setString("Health: 8/12");
    this->guiText[2].setCharacterSize(18);
    this->guiText[2].setPosition(10,60);

    this->guiText[3].setString("Experience: 122/200");
    this->guiText[3].setCharacterSize(18);
    this->guiText[3].setPosition(10,80);

    this->guiText[4].setString("Strenght: 2");
    this->guiText[4].setCharacterSize(14);
    this->guiText[4].setPosition(10,110);

    this->guiText[5].setString("Dexterity: 5");
    this->guiText[5].setCharacterSize(14);
    this->guiText[5].setPosition(10,125);

    this->guiText[6].setString("Constitution: 4");
    this->guiText[6].setCharacterSize(14);
    this->guiText[6].setPosition(10,140);

    this->guiText[7].setString("Intelligence: 2");
    this->guiText[7].setCharacterSize(14);
    this->guiText[7].setPosition(10,155);

    this->guiText[8].setString("Wisdom: 1");
    this->guiText[8].setCharacterSize(14);
    this->guiText[8].setPosition(10,180);

    this->guiText[9].setString("Charisma: 4");
    this->guiText[9].setCharacterSize(14);
    this->guiText[9].setPosition(10,195);

	this->lvl = new Level("level1");

	this->initialized = true;
}

void GameState::deinit() {

}

void GameState::handleEvents(sf::Event theEvent) {
    if(theEvent.type != sf::Event::KeyPressed)
        return;

    switch(theEvent.key.code) {
        case sf::Keyboard::W:
            // ruch gracza do góry
            break;
        case sf::Keyboard::S:
            // ruch gracza w dół
            break;
        case sf::Keyboard::A:
            // ruch gracza w lewo
            break;
        case sf::Keyboard::D:
            // ruch gracza w prawo
            break;
        case sf::Keyboard::Space:
            // atak
            break;
        case sf::Keyboard::F5:
            this->save();
            break;
        case sf::Keyboard::F6:
            this->load();
            break;
        case sf::Keyboard::Escape:
            setNewState(EState::Menu);
            break;
        default:
            break;
    }
}

void GameState::draw() {
	this->lvl->draw(this->engine->getWindow());
	this->engine->getWindow()->draw(this->maskS);

    // draw some info about player, etc.
    for (int i = 0; i < 10; i++) {

        this->engine->getWindow()->draw(guiText[i]);
    }
}

bool GameState::load() {
    if(initialized) {
        return 0;
    }
    initialized = 1;
    paused = 1;
    //todo
    return 0;
}

bool GameState::save() {
    return 0;
}
