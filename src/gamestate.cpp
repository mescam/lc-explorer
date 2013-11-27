#include "engine.h"
#include "gamestate.h"


GameState::GameState(Engine *_engine) {
    engine = _engine;
}

void GameState::init() {

}

void GameState::deinit() {

}

void GameState::handleEvents(sf::Event theEvent) {

}

void GameState::draw() {

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
