#include "engine.h"
#include "statemanager.h"
#include "state.h"
#include <iostream>
void Engine::initializeManagers() {
    statemanager = new StateManager(this);
    statemanager->getActiveState()->init();
}

void Engine::createGameWindow() {
    window.create(sf::VideoMode(900,600), "Trouble in Lecture Center");
    window.setFramerateLimit(60);
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

sf::RenderWindow& Engine::getWindow() {
    return window;
}
