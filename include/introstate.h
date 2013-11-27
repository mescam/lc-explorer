#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"


class IntroState: public IState {
    public:
        IntroState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();

    private:
        std::vector<std::string> text;
        
        sf::Text currentLine;
        sf::Font font;
        sf::Texture backgroundImg;
        sf::Sprite background;

        int frameCount = 0; //animation frame counter
        short lineCount = 0;
};

#endif // INTROSTATE_H
