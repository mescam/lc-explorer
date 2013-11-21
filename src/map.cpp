
#include "map.h"

Map::Map() {

}

Map::Map(short width, short height, std::string image) {
    this->setMapSize(width,height);
    this->gridVisible = false;

    if (!this->image.loadFromFile(image)) {
        // ERROR
    }    
}

void Map::showGrid(bool visible) {
    this->gridVisible = visible;
}

void Map::setMapSize(short width, short height) {
    this->width = width;
    this->height = height;
}

short Map::getMapWidth() {
    return this->width;
}

short Map::getMapHeight() {
    return this->height;
}

