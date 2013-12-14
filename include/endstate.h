#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "state.h"
#include <SFML/Graphics.hpp>

class EndState: public IState {
    public:
        EndState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();
        void setWinner(bool w);
    private: 
        sf::Text line;
        sf::Font font;
        sf::Texture backgroundImg;
        sf::Sprite background;
        bool winner = false;
};


#endif