#ifndef MENU_H
#define MENU_H
#include "state.h"
#include <SFML/Graphics.hpp>

class MenuState : public IState {
    public:
        MenuState(Engine *_engine);
        void init();
        void deinit();
        void handleEvents(sf::Event theEvent);
        void draw();

    private:
        unsigned short currentMenuItem;
        std::string menuItems[5] = {"New game","Load game","Settings","About...","Exit"};
        sf::View view;
        sf::Texture wallbackground;
        sf::Sprite wall;
        sf::Font titleFont;
        sf::Font menuFont;
        sf::Text title;
        sf::Text menuItem;
};

#endif
