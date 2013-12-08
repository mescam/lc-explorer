#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>

enum FieldState {
    Empty = 0,
    Obstacle = 1,
    Player = 2,
    Enemy = 3,
    Item = 4
};

struct Field {
    FieldState state;
    int id;
};

class Map {
public:
    Map(std::string filename);
    ~Map();
    void load(std::string filename);
    bool isLoaded();
    void showGrid(bool visible);     // turn on/off grid on map
    void setMapSize(short width, short height);      // set map size (in tiles)
    short getMapWidth();
    short getMapHeight();
    void draw();
private:
    short width;
    short height;
    bool gridVisible = false;
    bool loaded = false;
    sf::Texture mapImage;
    sf::Sprite mapSprite;

    Field** map;

    Map();
protected:
};

#endif // MAP_H

