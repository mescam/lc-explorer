#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H
#include <SFML/Graphics.hpp>
#include "state.h"


class SplashState : public IState {
    public:
        SplashState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();

    private:
        sf::Text gameTitle;
        sf::Sprite sfmlLogo;
        sf::Font font;
        sf::Texture sfmlImage;

        int frameCount = 0; //animation frame counter
};

#endif
