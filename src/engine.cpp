#include "engine.h"

void Engine::createGameWindow() {
    window.create(sf::VideoMode(900,600), "Trouble in Lecture Centre");
}

void Engine::mainLoop() {
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.display();
    }
}
