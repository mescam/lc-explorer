#include "aboutstate.h"
#include "engine.h"
#include "defaults.h"
#include <iostream>

AboutState::AboutState(Engine *_engine) {
	engine = _engine;
}

void AboutState::init() {
	engine->getLogFile()->writeToLog("Initialized AboutState");
	wall = new sf::Texture();
	wall->loadFromFile("images/wall-small.jpg");
	spriteWall = new sf::Sprite(*wall);
	initialized = true;
}

void AboutState::deinit() {
	initialized = false;
	delete wall;
}

void AboutState::handleEvents(sf::Event theEvent) {

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
}