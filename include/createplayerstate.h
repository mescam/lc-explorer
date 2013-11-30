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
        sf::Sprite *wallBackground;
        sf::Texture *tWallBackground;
        sf::Font *font;
        sf::Text *tName;
        sf::Text *hintName;
        sf::Text *welcome;
        std::string name;
        std::vector<std::string> professions;
        unsigned int selectedProfession;

        void drawProfessions();
};

#endif
