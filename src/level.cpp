#include "level.h"

Level::Level() {
}

Level::~Level() {
    delete view;
}

Level::Level(std::string name, Entity *p) {
    player = p;
    view = new sf::View();
    this->loadLevel(name);
    view->setSize(900, 600);
}

void Level::loadLevel(std::string name) {
    // generowanie ścieżek dla plików levelu
    std::string infoPath = "levels/" + name + '/' + name + ".nfo"; 
    std::string mapPath = "levels/" + name + '/' + name + ".map"; 
    std::string dataPath = "levels/" + name + '/' + name + ".dtb"; 
    // wczytać info o levelu
    /*
    std::ifstream infoFile;
    infoFile.open(infoPath);
    if(infoFile.is_open()) {
        
    } else {
        // BŁĄD
        return;
    }
    infoFile.close();
    */
    // wczytać mapę
    std::ifstream mapFile;
    mapFile.open(mapPath);
    if(mapFile.is_open()) {
        mapFile >> this->width >> this->height;
        
        std::cerr << "wys: " << this->height << "    szer: " << this->width << std::endl;

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
        std::cerr << "Utworzyłem mapę dynamiczną" << std::endl;
        // wczytanie grafiki mapy
        std::string temp;
        //getline(mapFile,temp);
        mapFile >> temp;
                std::cerr << "nazwa pliku z grafika: " << temp << std::endl;

        temp = "images/" + temp;
        std::cerr << "ścieżka: " << temp << std::endl;
        if (!this->mapImage.loadFromFile(temp)) {
            // ERROR
            
        }
        this->mapSprite.setTexture(this->mapImage);
        // wczytanie zawartości mapy
        int x,y,state,id;
        while (!mapFile.eof()) {
            mapFile >> x >> y >> state >> id;
            //std::cerr << x << " " << y << " " << state << " " << std::endl;
            map[x][y].state = (FieldState)state;
            map[x][y].id = id;
            if(state == 2) {
                std::cerr << "Found player on x=" << x << " y=" << y << std::endl;
                player->setPosition(sf::Vector2f(x*50+20, y*50+20));
            }
        }

    } else {
        // BŁĄD
        return;
    }
    mapFile.close();
    /*
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
    */
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

void Level::draw(sf::RenderWindow *w) {

    //camera 2d
    w->setView(*view);
    view->setCenter(player->getPosition());
    this->player->getPrimarySprite().setPosition(player->getPosition());
    w->draw(this->mapSprite);
    w->draw(this->player->getPrimarySprite());

    //reset to default view
    w->setView(w->getDefaultView());
}
