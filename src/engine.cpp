#include "engine.h"
#include "statemanager.h"
#include "soundmanager.h"
#include "state.h"
#include "defaults.h"

#include <iostream>

Engine::Engine() {
    if (WRITE_TO_LOG) {
        logFile = new Log();
    }
}

void Engine::initializeManagers() { //initializes all managers
    statemanager = new StateManager(this);
    soundmanager = new SoundManager();
    statemanager->getActiveState()->init();
}

void Engine::createGameWindow() {
    window.create(sf::VideoMode(DEFAULT_WINDOW_X,DEFAULT_WINDOW_Y), DEFAULT_WINDOW_TITLE, sf::Style::Close);
    window.setFramerateLimit(DEFAULT_FRAMERATE);
}

void Engine::mainLoop() {
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) { //get event from event queue
            if (event.type == sf::Event::Closed)
                window.close();
            else
                statemanager->getActiveState()->handleEvents(event); //handle it in correct state
        }
        if(statemanager->getActiveState()->shouldChangeState()) { //check need of state change
            statemanager->changeState(statemanager->getActiveState()->getNewState()); //change it
        }
        window.clear(); //paint it black
        statemanager->getActiveState()->draw(); //draw everything from active state
        window.display(); //display from buffer
    }
}


//simple getters below
sf::RenderWindow *Engine::getWindow() {
    return &window;
}

Log* Engine::getLogFile() {
    return logFile;
}

StateManager* Engine::getStateManager() {
    return statemanager;
}

SoundManager* Engine::getSoundManager() {
    return soundmanager;
}

Engine::~Engine() {
    delete statemanager;
    delete soundmanager;
}