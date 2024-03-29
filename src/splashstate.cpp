#include "splashstate.h"
#include "splash.h"
#include "engine.h"
#include <iostream>

void SplashState::init() {
    font.loadFromFile("fonts/Minecraftia.ttf");

    //gameTitle settings
    gameTitle.setFont(font);
    gameTitle.setString("Trouble in Lecture Center");
    gameTitle.setCharacterSize(50);
    centerObject(gameTitle, engine->getWindow()->getSize());

    sfmlImage.loadFromFile("images/sfml.png");
    sfmlLogo.setTexture(sfmlImage);
    centerObject(sfmlLogo, engine->getWindow()->getSize());

    initialized = true;
}

void SplashState::deinit() {
    initialized = false;
}

void SplashState::draw() {
    double x, y;
    int screen = frameCount / 120;
    x = frameCount % 120;
    y = (x < 60) ? (255.0/59.0)*x : -(255.0/59.0)*x + 510.0;
    if (y < 0)
        y = 0;
    sf::Color c(255, 255, 255, int(y));
    sf::RenderWindow *w = engine->getWindow();
    switch(screen) {
        case 0:
            gameTitle.setColor(c);
            w->draw(gameTitle);
            break;
        case 1:
            sfmlLogo.setColor(c);
            w->draw(sfmlLogo);
            break;
        default:
            this->changeState = true;
            this->newState = EState::Menu;
    }
    frameCount++;
}

void SplashState::handleEvents(sf::Event theEvent) {
    if(theEvent.type != sf::Event::KeyPressed)
        return;

    switch(theEvent.key.code) {
        case sf::Keyboard::Escape:
            this->changeState = true;
            this->newState = EState::Menu;
            break;
        default:
            break;
    }
}

SplashState::SplashState(Engine *_engine) {
    engine = _engine;
}
