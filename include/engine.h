#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

class Engine {
    private:
        Engine() {};
        Engine(const Engine &);
        Engine& operator=(const Engine&);
        ~Engine() {};

        sf::RenderWindow window;

    public:
        static Engine& getInstance(){
            static Engine instance;
            return instance;
        }

        void createGameWindow();
        void mainLoop();
};

#endif
