#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "statemanager.h"
class Engine;

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
        //getters
        bool isInitialized() {
            return initialized;
        }
        bool isPaused() {
            return paused;
        }
        bool shouldChangeState() {
            return changeState;
        }
        EState getNewState() {
            changeState = false;
            return newState;
        }

    protected:
        bool initialized = false;
        bool paused = false;
        bool changeState = false;
        Engine *engine = NULL;
        EState newState;
};
#endif
