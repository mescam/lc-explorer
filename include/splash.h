#ifndef SPLASH_H
#define SPLASH_H

#include <SFML/Graphics.hpp>
#include "engine.h"

class Splash {
    public:
        Splash(Engine& _engine);
        void animate();
    private:
        Engine& engine;
        sf::Font font; //font loaded from fonts
        sf::Text title; //title of our game, for splash screen

};

#endif
