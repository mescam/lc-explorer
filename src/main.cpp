#include <engine.h>
#include <iostream>
int main() {
    Engine::getInstance().createGameWindow();

    Engine::getInstance().mainLoop();
    return 0;
}
