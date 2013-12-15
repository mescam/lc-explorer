#include "introstate.h"
#include "splash.h"
#include "engine.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void IntroState::init() {
    std::ifstream file;
    char line[256];
    file.open("data/intro.txt");
    if (file.is_open()) {
        while (file.good()) {
            file.getline(line,256,'@');
            text.push_back(std::string(line));
        }
    }
    file.close();

    backgroundImg.loadFromFile("images/wall_clean.png"); 
    background.setTexture(backgroundImg);

    font.loadFromFile("fonts/Minecraftia.ttf");

    currentLine.setColor(sf::Color(255,255,255,255));
    currentLine.setFont(font);
    currentLine.setString(text[0]);
    currentLine.setCharacterSize(25);
    centerObject(currentLine, engine->getWindow()->getSize());

    initialized = true;
}

void IntroState::deinit() {
    initialized = false;
}

void IntroState::draw() {
    if (frameCount/60 > 5) {
        lineCount++;
        frameCount = 0;
    }
    engine->getWindow()->draw(background);

    if (lineCount < (int)text.size()) {
        currentLine.setString(text[lineCount]);
        centerObject(currentLine, engine->getWindow()->getSize());
        engine->getWindow()->draw(currentLine);
    } 
    else {
        setNewState(EState::CreatePlayer);
    }
    frameCount++;
}

void IntroState::handleEvents(sf::Event theEvent) {
    if(theEvent.type != sf::Event::KeyPressed)
        return;

    switch(theEvent.key.code) {
        case sf::Keyboard::Escape:
            setNewState(EState::CreatePlayer);
            break;
        default:
            break;
    }
}

IntroState::IntroState(Engine *_engine) {
    engine = _engine;
}
