#include "aboutstate.h"
#include "engine.h"
#include "defaults.h"
#include "splash.h"
#include <iostream>

AboutState::AboutState(Engine *_engine) {
	engine = _engine;
}

void AboutState::init() {
	engine->getLogFile()->writeToLog("Initialized AboutState");
	wall = new sf::Texture();
	wall->loadFromFile("images/wall-small.jpg");
	spriteWall = new sf::Sprite(*wall);
	font = new sf::Font();
	font->loadFromFile("fonts/Minecraftia.ttf");
	//description
	desc.push_back(sf::Text("Trouble in Lecture Center", *font));
	desc.push_back(sf::Text("Dominik Galewski", *font));
	desc.push_back(sf::Text("Jakub Wozniak", *font));
	desc.push_back(sf::Text("Poznan University of Technology 2013", *font));

	desc[0].setCharacterSize(40); //it's ugly, I know.
	desc[1].setCharacterSize(28);
	desc[2].setCharacterSize(28);
	desc[3].setCharacterSize(23);

	for(auto it = desc.begin(); it != desc.end(); ++it) //I love auto keyword
		centerOrigin(*it);
	desc[0].setPosition(450, 50);
	desc[1].setPosition(450, 280);
	desc[2].setPosition(450, 320);
	desc[3].setPosition(450, 450);

	initialized = true;
}

void AboutState::deinit() {
	initialized = false;
	delete wall;
	delete font;
	delete spriteWall;
	desc.clear();
}

void AboutState::handleEvents(sf::Event theEvent) {
    if(theEvent.type != sf::Event::KeyPressed)
        return;

    switch(theEvent.key.code) {
        case sf::Keyboard::Return:
            this->changeState = true;
            this->newState = EState::Menu;
            break;
        default:
            break;
    }
}

void AboutState::draw() {
	//painting the wall
	sf::RenderWindow *window = engine->getWindow();
	//spriteWall->setPosition(0, 0); //reset position
	for(int x = 0; x < DEFAULT_WINDOW_X; x += 140) { //loop over background
 		for(int y = 0; y < DEFAULT_WINDOW_Y; y += 140) {
			spriteWall->setPosition(x, y);
			window->draw(*spriteWall);
		}
	}
	//draw description
	for(auto it = desc.begin(); it != desc.end(); ++it)
		window->draw(*it);
}