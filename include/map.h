#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map {
public:
    Map(short width, short height, std::string image);
    ~Map();
    void showGrid(bool visible);     // turn on/off grid on map
    void setMapSize(short width, short height);      // set map size (in tiles)
    short getMapWidth();
    short getMapHeight();
private:
    short width;
    short height;
    bool gridVisible;
    sf::Texture image;

    Map();
protected:
};

#endif // MAP_H

