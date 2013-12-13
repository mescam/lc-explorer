#include "engine.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

#ifdef _MSC_VER
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-main.lib")
#pragma comment(lib,"sfml-network.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#endif

int main() {
    srand(time(NULL));
    Engine app;
    app.createGameWindow();
    app.initializeManagers();
    app.mainLoop();
    return 0;
}
