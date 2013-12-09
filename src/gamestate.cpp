#include "engine.h"
#include "gamestate.h"
#include <iostream>

GameState::GameState(Engine *_engine) {
    engine = _engine;
}

void GameState::init() {
	this->lvl = new Level("level1");
	this->initialized = true;
}

void GameState::deinit() {

}

void GameState::handleEvents(sf::Event theEvent) {

}

void GameState::draw() {
	this->lvl->draw(this->engine->getWindow());
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
