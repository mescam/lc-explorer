#include "level.h"

Level::Level() {

}

Level::Level(std::string name) {
    this->loadLevel(name);
}

void Level::loadLevel(std::string name) {
    // generowanie ścieżek dla plików levelu
    std::string infoPath = "levels/" + name + '/' + name + ".nfo"; 
    std::string mapPath = "levels/" + name + '/' + name + ".map"; 
    std::string dataPath = "levels/" + name + '/' + name + ".dtb"; 
    // wczytać info o levelu

    std::ifstream infoFile;
    infoFile.open(infoPath);
    if(infoFile.is_open()) {
        
    } else {
        // BŁĄD
        return;
    }
    infoFile.close();

    // wczytać mapę
    std::ifstream mapFile;
    mapFile.open(mapPath);
    if(mapFile.is_open()) {
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
                map[i][j].id = -1;
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

    // wczytanie elementów levelu
    std::ifstream dataFile;
    dataFile.open(dataPath);
    if(dataFile.is_open()) {
        std::string line;
        while (!dataFile.eof()) {
            getline(dataFile,line);
            if (line.length() != 0 && line[0] != ';') {
                std::stringstream lineStream(line);
                int id, type;
                std::string name, texture;
                lineStream >> id >> type >> name >> texture;
                switch (type) {
                    case Key:

                            
                        break;
                    case Scroll:
                        break;
                    case Herb:
                        break;
                    case Armor:
                        break;
                    case Weapon:
                        break;
                    case Shield:
                        break;
                    case Ring:
                        break;
                    case Jewel:
                        break;
                    case Chest:
                        break;
                    case FriendlyNPC:
                        break;
                    case Mob:
                        break;
                    case Boss:
                        break;
                    case Player:
                        break;
                    default:
                        break;
                }
            } else {
                 continue;
            }
        }  
    } else {
        return;
        // BŁĄD
    }
    dataFile.close();   

    this->loaded = true;
}

bool Level::isLoaded() {
    return this->loaded;
}

void Level::showGrid(bool visible) {
    this->gridVisible = visible;
}

void Level::setMapSize(short width, short height) {
    this->width = width;
    this->height = height;
}

short Level::getMapWidth() {
    return this->width;
}

short Level::getMapHeight() {
    return this->height;
}

void Level::draw() {
    //sf::RenderWindow *w = engine->getWindow();
    //w->draw(this->mapSprite);
    if (this->gridVisible) {
        sf::Color c(255,255,255,128);
        
    }
}
