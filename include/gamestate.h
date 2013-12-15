#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "level.h"
#include "player.h"

class GameState : public IState {
    public:
        sf::Font *guiFont;
        sf::Text guiText[10];
    	sf::Texture maskT;
    	sf::Sprite maskS;
    	Level *lvl = NULL;
        class Player *player = NULL;
        GameState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();
        bool save();

    protected:
        void updatePlayerStatsString();
};


#endif
