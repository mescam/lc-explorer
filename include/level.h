#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>

enum FieldState {
    Empty = 0,
    Obstacle = 1,
    Character = 2,
    Enemy = 3,
    Item = 4
};

enum EntityType {
    Key = 0,
    Scroll,
    Herb,
    Armor,
    Weapon,
    Shield,
    Ring,
    Jewel,
    Chest,
    FriendlyNPC,
    Mob,
    Boss,
    Player
};

struct Field {
    FieldState state;
    int id;
};

class Level {
public:
    Level(std::string name);
    ~Level() {};
    void loadLevel(std::string name);
    bool isLoaded();
    void showGrid(bool visible);     // turn on/off grid on map
    void setMapSize(short width, short height);      // set map size (in tiles)
    short getMapWidth();
    short getMapHeight();
    void draw(sf::RenderWindow *w);
private:
    short width;
    short height;
    bool gridVisible = false;
    bool loaded = false;
    sf::Texture mapImage;
    sf::Sprite mapSprite;

    Field** map;
    std::map<int,Entity*> mapElements;
    
    Level();
protected:
};

#endif // LEVEL_H

