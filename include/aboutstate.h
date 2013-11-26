#ifndef ABOUTSTATE_H
#define ABOUTSTATE_H
#include <SFML/Graphics.hpp>
#include "state.h"
#include <vector>

class AboutState : public IState {
    public:
        AboutState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();

    private:
    	sf::Texture *wall;
    	sf::Sprite *spriteWall;
    	sf::Font *font;
    	std::vector<sf::Text> desc;

};

#endif