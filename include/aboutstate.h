#ifndef ABOUTSTATE_H
#define ABOUTSTATE_H

#include <SFML/Graphics.hpp>

#include "state.h"
#include "defaults.h"

#include <vector>

class AboutState : public IState {
    public:
        AboutState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();

    private:
    	sf::Texture *wall; //texture of wall
    	sf::Sprite *spriteWall; //sprite for wall
    	sf::Font *font; //default font
    	std::vector<sf::Text> desc; //description of our game

};

#endif