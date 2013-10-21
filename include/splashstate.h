#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H
#include <SFML/Graphics.hpp>
#include "state.h"

class SplashState : public IState {
    public:
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();
};

#endif
