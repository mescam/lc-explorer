#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics.hpp>

class StateManager;

class Engine {
    private:
        sf::RenderWindow window;
        StateManager *statemanager = NULL;

    public:
        void createGameWindow();
        void mainLoop();
        void initializeManagers();
        void welcomeAnimation();
        sf::RenderWindow& getWindow();
};

#endif
