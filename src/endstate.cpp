#include "endstate.h"
#include "splash.h"
#include "engine.h"


//nothing special here
//so nothing worth mentioning

EndState::EndState(Engine *_engine) {
    engine = _engine;
    backgroundImg.loadFromFile("images/wall_clean.png"); 
    background.setTexture(backgroundImg);

    font.loadFromFile("fonts/Minecraftia.ttf");
    line.setFont(font);
    line.setString("Trouble in Lecture Center");
    line.setCharacterSize(40);
}

void EndState::init() {
    initialized = true;
}

void EndState::deinit() {
    initialized = false;
}

void EndState::draw() {
    sf::RenderWindow *w = engine->getWindow();
    w->draw(background);
    if(winner) {
        line.setString("You've won!");
    } else {
        line.setString("GAME OVER");
    }
    centerOrigin(line);
    line.setPosition(450, 300);
    w->draw(line);
}

void EndState::handleEvents(sf::Event theEvent) {
    if(theEvent.type != sf::Event::KeyPressed)
        return;

    switch(theEvent.key.code) {
        case sf::Keyboard::Return:
            setNewState(EState::Menu);
            break;
        default:
            break;
    }
}

void EndState::setWinner(bool w) {
    winner = w;
}