#include "engine.h"
#include "statemanager.h"
#include "state.h"
#include "defaults.h"

#include <iostream>

Engine::Engine() {
    if (WRITE_TO_LOG) {
        logFile = new Log();
    }
}

void Engine::initializeManagers() {
    statemanager = new StateManager(this);
    statemanager->getActiveState()->init();
}

void Engine::createGameWindow() {
    window.create(sf::VideoMode(DEFAULT_WINDOW_X,DEFAULT_WINDOW_Y), DEFAULT_WINDOW_TITLE, sf::Style::Close);
    window.setFramerateLimit(DEFAULT_FRAMERATE);
}

void Engine::mainLoop() {
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else
                statemanager->getActiveState()->handleEvents(event);
        }
        if(statemanager->getActiveState()->shouldChangeState()) {
            statemanager->changeState(statemanager->getActiveState()->getNewState());
        }
        window.clear();
        statemanager->getActiveState()->draw();
        window.display();
    }
}

sf::RenderWindow *Engine::getWindow() {
    return &window;
}

Log* Engine::getLogFile() {
    return logFile;
}

StateManager* Engine::getStateManager() {
    return statemanager;
}