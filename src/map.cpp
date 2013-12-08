
#include "map.h"

Map::Map() {

}

Map::Map(std::string filename) {
    this->load(filename);
}

void Map::load(std::string filename) {
    std::ifstream mapFile;
    mapFile.open(filename);
    if(mapFile.good()) {
        mapFile >> this->width >> this->height;

        // utworzenie dynamicznej tablicy
        this->map = new Field* [width];
        for (int i = 0; i < width; i++) {
            map[i] = new Field [height];
        }
        // wypełnienie jej pustymi polami
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                map[i][j].state = Empty;
                map[i][j].id = 0;
            }
        }
        // wczytanie grafiki mapy
        std::string temp;
        getline(mapFile,temp);
        if (!this->mapImage.loadFromFile(temp)) {
            // ERROR
        }
        this->mapSprite.setTexture(this->mapImage);
        // wczytanie zawartości mapy
        int x,y,state,id;
        while (!mapFile.eof()) {
            mapFile >> x >> y >> state >> id;
            map[x][y].state = (FieldState)state;
            map[x][y].id = id;
        }  

    } else {
        // BŁĄD
        return;
    }
    mapFile.close();
    this->loaded = true;
}

bool Map::isLoaded() {
    return this->loaded;
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

void Map::draw() {
    //sf::RenderWindow *w = engine->getWindow();
    //w->draw(this->mapSprite);
    if (this->gridVisible) {
        sf::Color c(255,255,255,128);
        
    }
}
