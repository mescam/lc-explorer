#include "level.h"

Level::Level() {
}

Level::~Level() {
    delete view;
    for(int i = 0; i < width; i++) {
        delete[] map[i];
    }
    delete[] map;
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
        
        std::cerr << "h: " << this->height << "    w: " << this->width << std::endl;

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
        std::cerr << "Dynamic mape is created" << std::endl;
        // wczytanie grafiki mapy
        std::string temp;
        //getline(mapFile,temp);
        mapFile >> temp;
                std::cerr << "graphics file: " << temp << std::endl;

        temp = "images/" + temp;
        std::cerr << "path: " << temp << std::endl;
        if (!this->mapImage.loadFromFile(temp)) {
            // ERROR
            
        }
        this->mapSprite.setTexture(this->mapImage);
        this->mapSprite.setPosition(-50, -50); //don't ask me why...
        // wczytanie zawartości mapy
        int x,y,state,id;
        while (!mapFile.eof()) {
            mapFile >> x >> y >> state >> id;
            // std::cerr << x << " " << y << " " << state << " " << std::endl;
            map[x][y].state = (FieldState)state;
            map[x][y].id = id;

            switch((FieldState)state) {
                case Character: {
                    player->setPosition(sf::Vector2f(x*50+20, y*50+20));
                    break;
                }
                case Enemy: {
                    std::cerr << "found enemy" << std::endl;

                    break;
                }
                default: {
                    break;
                }
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

Field& Level::getMapField(int x, int y) {
    return map[x][y];
}

void Level::draw(sf::RenderWindow *w) {
    //camera 2d
    w->setView(*view);
    view->setCenter(player->getPosition());
    this->player->getPrimarySprite().setPosition(player->getPosition());
    w->draw(this->mapSprite);
    this->player->draw(w);

    //grid
    // for(int x = 0; x < view->getSize().x; x+=50) {
    //     sf::VertexArray lines(sf::LinesStrip, 2);
    //     lines[0].position = sf::Vector2f(x, 0);
    //     lines[1].position = sf::Vector2f(x, view->getSize().y);
    //     w->draw(lines);
    // }
    // for(int y = 0; y < view->getSize().y; y+=50) {
    //     sf::VertexArray lines(sf::LinesStrip, 2);
    //     lines[0].position = sf::Vector2f(0, y);
    //     lines[1].position = sf::Vector2f(view->getSize().x, y);
    //     w->draw(lines);
    // }

    //reset to default view
    w->setView(w->getDefaultView());
}
