#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>

class IState {
    public:
        //called after init
        virtual void init() {};
        //clean up
        virtual void deinit() {};
        //paused state
        virtual void pause() {};
        //resumed state
        virtual void resume() {};
        //event from main loop
        virtual void handleEvents(sf::Event theEvent) = 0;
        //drawing entities
        virtual void draw() = 0;
};
#endif
