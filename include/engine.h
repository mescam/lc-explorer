#ifndef ENGINE_H
#define ENGINE_H

#include "log.h"


#include <SFML/Graphics.hpp>


class StateManager;
class SoundManager;

class Engine {
    private:
        sf::RenderWindow window;
        StateManager *statemanager = NULL;
        SoundManager *soundmanager = NULL;
        Log *logFile = NULL;        

    public:
        Engine();
        ~Engine();
        void createGameWindow();
        void mainLoop();
        void initializeManagers();
        void welcomeAnimation();
        sf::RenderWindow *getWindow();
        Log* getLogFile();
        StateManager *getStateManager();
        SoundManager *getSoundManager();
};

#endif
