#include "engine.h"
#include "splash.h"

void Engine::createGameWindow() {
    window.create(sf::VideoMode(900,600), "Trouble in Lecture Centre");
    window.setFramerateLimit(60);
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

void Engine::welcomeAnimation() {
    sf::Font font;
    sf::Text title;

    font.loadFromFile("fonts/Grundschrift.ttf");
    title.setFont(font);
    title.setString("Trouble in Lecture Centre");
    title.setCharacterSize(50);
    Splash<sf::Text> textAnimation(title);
    textAnimation.centerObject();
    textAnimation.animate(6); //animate it for 6 seconds;

    //second phase, proof of concept
    sf::Texture texture; sf::Sprite sprite;
    texture.loadFromFile("images/sfml.png");
    sprite.setTexture(texture);
    Splash<sf::Sprite> spriteAnimation(sprite);
    spriteAnimation.centerObject();
    spriteAnimation.animate(4);
}

sf::RenderWindow& Engine::getWindow() {
    return window;
}
