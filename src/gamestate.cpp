#include "engine.h"
#include "defaults.h"
#include "gamestate.h"
#include "endstate.h"
#include "dmg.h"
#include <iostream>
#include <cassert>


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
    
    assert(this->player != NULL);
    this->player->setSoundManager(engine->getSoundManager());

	if(this->lvl == NULL) {
        std::cerr << "Loading brand new level..." << std::endl;
        this->lvl = new Level("level1", player, true, engine->getSoundManager());
    }
    assert(this->lvl != NULL);

    this->updatePlayerStatsString();
	this->initialized = true;
}

void GameState::deinit() {
    delete this->player;
    delete this->lvl;
    this->lvl = NULL;
    this->player = NULL;
    this->initialized = false;
}

void GameState::handleEvents(sf::Event theEvent) {
    if(theEvent.type == sf::Event::KeyPressed) {
        switch(theEvent.key.code) {
            case sf::Keyboard::W: // going up
                player->motion.y = -1;
                player->lookingDirection = 1;
                break;
            case sf::Keyboard::S: //down
                player->motion.y = 1;
                player->lookingDirection = 3;
                break;
            case sf::Keyboard::A: //left
                player->motion.x = -1;
                player->lookingDirection = 4;
                break;
            case sf::Keyboard::D: //right
                player->motion.x = 1;
                player->lookingDirection = 2;
                break;
            case sf::Keyboard::Space: {
                DMG* dmg = player->attack(this->lvl->map);
                if(dmg != NULL) {
                    this->lvl->mapElements.push_back(dmg);
                }
                break;
            }
            case sf::Keyboard::F5:
                this->save();
                break;
            case sf::Keyboard::Escape:
                setNewState(EState::Menu);
                break;
            case sf::Keyboard::G:
                std::cerr << "My position is (" << player->getPosition().x/50 << ", " <<
                    player->getPosition().y/50 << ")" << std::endl;
                break;
            default:
                break;
        }
    } else if(theEvent.type == sf::Event::KeyReleased) {
        switch(theEvent.key.code) {
            case sf::Keyboard::W: 
                if(player->motion.y == -1) player->motion.y = 0;
                break;
            case sf::Keyboard::S: 
                if(player->motion.y == 1) player->motion.y = 0;
                break;
            case sf::Keyboard::A: 
                if(player->motion.x == -1) player->motion.x = 0;
                break;
            case sf::Keyboard::D: 
                if(player->motion.x == 1) player->motion.x = 0;
                break;
            default:
                break;
        }
    }
}

void GameState::draw() {
    // PLAYER MOTION LOGIC
    // next position of character player
    int nextX, nextY;
    sf::Vector2f curPos = player->getPosition();
    nextX = curPos.x + player->motion.x*CHAR_SPEED;
    nextY = curPos.y + player->motion.y*CHAR_SPEED;
    if(lvl->getMapField(nextX/50, nextY/50).state == Empty ||
        lvl->getMapField(nextX/50, nextY/50).state == Character) {
        player->setPosition(sf::Vector2f(nextX, nextY));
        lvl->getMapField(curPos.x/50, curPos.y/50).state = Empty;
        lvl->getMapField(nextX/50, nextY/50).state = Character;
    }

    // draw level elements and light mask
	this->lvl->draw(this->engine->getWindow());
	this->engine->getWindow()->draw(this->maskS);

    // draw some info about player, etc.
    this->updatePlayerStatsString();
    for (int i = 0; i < 10; i++) {
        this->engine->getWindow()->draw(guiText[i]);
    }

    //end game conditions
    if(lvl->isFinished()) {
        dynamic_cast<EndState*>(engine->getStateManager()->getStateObject(EState::End))->setWinner(true);
        setNewState(EState::End);
        std::cerr << "End conditions" << std::endl;
    } else if(player->getHealth() <= 0) {
        dynamic_cast<EndState*>(engine->getStateManager()->getStateObject(EState::End))->setWinner(false);
        setNewState(EState::End);
        std::cerr << "End conditions 2" << std::endl;
    }
}

bool GameState::save() {
    this->player->save();
    this->lvl->save();
    return 0;
}

void GameState::updatePlayerStatsString() {
    //level and class
    this->guiText[1].setString("Level " 
        + std::to_string(this->player->getExperience()/10 + 1)
        + " "
        + this->player->getProfessionName());

    //health
    this->guiText[2].setString("Health: "
        + std::to_string(this->player->getHealth())
        + "/"
        + std::to_string(this->player->getMaxHealth())
        );

    //exp
    this->guiText[3].setString("Exp: "
        + std::to_string(this->player->getExperience()));

    //strenght
    this->guiText[4].setString("Strenght: "
        + std::to_string(this->player->getAbilityScore(Strenght)));

    //dexterity
    this->guiText[5].setString("Dexterity: "
        + std::to_string(this->player->getAbilityScore(Dexterity)));

    //contitution
    this->guiText[6].setString("Constitution: "
        + std::to_string(this->player->getAbilityScore(Constitution)));

    //inteligence
    this->guiText[7].setString("Intelligence: "
        + std::to_string(this->player->getAbilityScore(Intelligence)));

    //wisdom
    this->guiText[8].setString("Wisdom: "
        + std::to_string(this->player->getAbilityScore(Wisdom)));

    //charisma
    this->guiText[9].setString("Charisma: "
        + std::to_string(this->player->getAbilityScore(Charisma)));
}
