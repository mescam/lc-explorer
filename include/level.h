#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

enum FieldState {
    Empty = 0,
    Obstacle = 1,
    Character = 2,
    Enemy = 3,
    Item = 4
};


struct Field {
    FieldState state;
    int id;
    Entity *entity;
};

class Level {
public:
    Level(std::string name, Entity *p);
    ~Level();
    void loadLevel(std::string name);
    bool isLoaded();
    void showGrid(bool visible);     // turn on/off grid on map
    void setMapSize(short width, short height);      // set map size (in tiles)
    short getMapWidth();
    short getMapHeight();
    Field& getMapField(int x, int y);
    void draw(sf::RenderWindow *w);
    Entity *player = NULL;
    Field** map;
private:
    short width;
    short height;
    bool gridVisible = false;
    bool loaded = false;
    sf::Texture mapImage;
    sf::Sprite mapSprite;
    std::vector<Entity*> mapElements;
    sf::View *view;
    int counter = 0;
    Level();
protected:
};

#endif // LEVEL_H

