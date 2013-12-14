#include "level.h"
#include "hostilenpc.h"
#include "player.h"

#include <vector>

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
    std::string mapPath = "levels/" + name + '/' + name + ".map"; 

    // read map
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
        std::cerr << "Dynamic map is created" << std::endl;
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
        class Player *playerptr = reinterpret_cast<class Player*>(player);
        while (!mapFile.eof()) {
            mapFile >> x >> y >> state >> id;
            // std::cerr << x << " " << y << " " << state << " " << std::endl;
            map[x][y].state = (FieldState)state;
            map[x][y].id = id;
            map[x][y].entity = NULL;

            switch((FieldState)state) {
                case Character: {
                    player->setPositionOnMap(x, y);
                    break;
                }
                case Enemy: {
                    std::cerr << "found enemy" << std::endl;
                    HostileNPC *enemy = new HostileNPC(
                        "Professor",
                        20,
                        "prof" + std::to_string(rand()%7 + 1) + ".png");
                    enemy->setPositionOnMap(x, y);
                    mapElements.push_back(enemy);
                    map[x][y].entity = enemy;
                    break;
                }
                default: {
                    break;
                }
            }
        }

    } else {
        // error?
        return;
    }
    mapFile.close();
    this->loaded = true;
}

bool Level::isLoaded() {
    return this->loaded;
}

bool Level::isFinished() {
    return mapElements.empty();
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
    // this->player->getPrimarySprite().setPosition(player->getPosition());
    w->draw(this->mapSprite);
    // draw player
    this->player->draw(w);
    Player *p = dynamic_cast<Player*>(player);
    // draw other entities
    HostileNPC *npc;
    std::vector<std::vector<Entity*>::iterator> toRemove; //oh god...
    for(auto it = mapElements.begin(); it != mapElements.end(); it++) {
        npc = dynamic_cast<HostileNPC*>(*it);
        if(npc != NULL) {
            if(npc->getHealth() <= 0) {
                int x = npc->getPosition().x/50, y = npc->getPosition().y/50;
                map[x][y].state = Empty;
                map[x][y].entity = NULL;
                toRemove.push_back(it);
            } else {
                // std::cerr << "NPC interacts" << std::endl;
                npc->interact(p, map);
            }
        } 
        (*it)->draw(w);
    }
    
    //remove dead entities
    for(auto it : toRemove) {
        mapElements.erase(it);
    }

    //add health every one second
    counter++;
    if(counter == 60) {
        if(p->getHealth() < p->getMaxHealth())
            p->setHealth(p->getHealth()+1);
        counter = 0;
    }

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
