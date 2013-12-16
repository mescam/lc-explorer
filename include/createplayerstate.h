#ifndef CREATEPLAYERSTATE_H
#define CREATEPLAYERSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include <string>

class CreatePlayerState : public IState {
    public:
        CreatePlayerState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();

    private:
        sf::Sprite *wallBackground; //assets for background
        sf::Texture *tWallBackground;
        sf::Font *font;
        sf::Text *tName; //name of player
        sf::Text *hintName; //prompt?
        sf::Text *welcome; //welcome text
        std::string name; //storage for input
        std::vector<std::string> professions; //available professions
        unsigned int selectedProfession; //selected profession

        void drawProfessions(); //draw professions on screen
};

#endif
