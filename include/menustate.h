#ifndef MENU_H
#define MENU_H
#include "state.h"
#include <SFML/Graphics.hpp>

class MenuState : public IState {
    void init();
    void deinit();
    void handleEvents(sf::Event theEvent);
    void draw();
};

#endif
