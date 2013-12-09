#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "level.h"

class GameState : public IState {
    public:
    	Level *lvl = NULL;
        GameState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();

        bool load();
        bool save();
};


#endif
