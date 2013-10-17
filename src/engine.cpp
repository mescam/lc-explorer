#include "engine.h"

void Engine::createGameWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Trouble in Lecture Centre");
}

void Engine::mainLoop() {
    while(this->window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color::Black);

        window->display();
    }
}
