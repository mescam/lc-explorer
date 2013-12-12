#include "engine.h"
#include "defaults.h"
#include "gamestate.h"
#include <iostream>
#include <cassert>

#include <boost/lexical_cast.hpp>

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

    this->guiText[0].setString(this->player->getName());
    this->guiText[0].setColor(sf::Color(255,0,0,255));
    this->guiText[0].setCharacterSize(20);
    this->guiText[0].setPosition(10,10);

    // level and class
    this->guiText[1].setCharacterSize(20);
    this->guiText[1].setPosition(10,35);

    //health
    this->guiText[2].setCharacterSize(18);
    this->guiText[2].setPosition(10,60);

    //experience
    this->guiText[3].setCharacterSize(18);
    this->guiText[3].setPosition(10,80);

    //strenght
    this->guiText[4].setCharacterSize(14);
    this->guiText[4].setPosition(10,110);

    //dexterity
    this->guiText[5].setCharacterSize(14);
    this->guiText[5].setPosition(10,125);

    //constitution
    this->guiText[6].setCharacterSize(14);
    this->guiText[6].setPosition(10,140);

    //intelligence
    this->guiText[7].setCharacterSize(14);
    this->guiText[7].setPosition(10,155);

    //wisdom
    this->guiText[8].setCharacterSize(14);
    this->guiText[8].setPosition(10,180);

    //charisma
    this->guiText[9].setCharacterSize(14);
    this->guiText[9].setPosition(10,195);

	if(this->lvl == NULL)
        this->lvl = new Level("level1");

    assert(this->player != NULL);
    this->updatePlayerStatsString();
	this->initialized = true;
}

void GameState::deinit() {
    delete this->player;
    delete this->lvl;
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

void GameState::updatePlayerStatsString() {
    //level and class
    this->guiText[1].setString("Level " 
        + boost::lexical_cast<std::string>(this->player->getLevel())
        + " "
        + this->player->getProfessionName());

    //health
    this->guiText[2].setString("Health: "
        + boost::lexical_cast<std::string>(this->player->getHealth())
        + "/"
        + boost::lexical_cast<std::string>(this->player->getMaxHealth())
        );

    //exp
    this->guiText[3].setString("Exp: "
        + boost::lexical_cast<std::string>(this->player->getExperience()));

    //strenght
    this->guiText[4].setString("Strenght: "
        + boost::lexical_cast<std::string>(this->player->getAbilityScore(Strenght)));

    //dexterity
    this->guiText[5].setString("Dexterity: "
        + boost::lexical_cast<std::string>(this->player->getAbilityScore(Dexterity)));

    //contitution
    this->guiText[6].setString("Constitution: "
        + boost::lexical_cast<std::string>(this->player->getAbilityScore(Constitution)));

    //inteligence
    this->guiText[7].setString("Intelligence: "
        + boost::lexical_cast<std::string>(this->player->getAbilityScore(Intelligence)));

    //wisdom
    this->guiText[8].setString("Wisdom: "
        + boost::lexical_cast<std::string>(this->player->getAbilityScore(Wisdom)));

    //charisma
    this->guiText[9].setString("Charisma: "
        + boost::lexical_cast<std::string>(this->player->getAbilityScore(Charisma)));
}
