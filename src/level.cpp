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
    map = NULL;
    for(auto mob : mapElements) {
        delete mob;
    }
}

Level::Level(std::string name, Entity *p, bool cnew, SoundManager *snd) {
    player = p;
    view = new sf::View();
    view->reset(sf::FloatRect(0, 0, 900, 600));
    sm = snd;
    this->loadLevel(name, cnew);
}

void Level::loadLevel(std::string name, bool cnew) {
    std::string mapPath;
    if(cnew)
        mapPath = "levels/" + name + '/' + name + ".map"; 
    else
        mapPath = name;
    std::cerr << "Loading level" << std::endl;
    // read map
    std::ifstream mapFile;
    mapFile.open(mapPath);
    if(mapFile.is_open()) {
        mapFile >> this->width >> this->height;
        
        std::cerr << "h: " << this->height << "    w: " << this->width << std::endl;

        // create dynamic array
        this->map = new Field* [width];
        for (int i = 0; i < width; i++) {
            map[i] = new Field [height];
        }
        // fill it with empty fields
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                map[i][j].state = Empty;
                map[i][j].id = -1;
            }
        }
        std::cerr << "Dynamic map is created" << std::endl;
        // load map graphics
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
        //this->mapSprite.setPosition(-50, -50); //don't ask me why...
        // read map content
        int x,y,state,id;
        //class Player *playerptr = reinterpret_cast<class Player*>(player);
        while (!mapFile.eof()) {
            mapFile >> x >> y >> state >> id;
            //std::cerr << x << " " << y << " " << state << " " << std::endl;
            map[x][y].state = (FieldState)state;
            map[x][y].id = id;
            map[x][y].entity = NULL;

            switch((FieldState)state) {
                case Character: {
                    player->setPositionOnMap(x, y);
                    break;
                }
                case Enemy: {
                    //std::cerr << "found enemy" << std::endl;
                    HostileNPC *enemy = new HostileNPC(
                        "Professor",
                        20,
                        "prof" + std::to_string(rand()%7 + 1) + ".png");
                    enemy->setSoundManager(sm);
                    enemy->setPositionOnMap(x, y);
                    mapElements.push_back(enemy);
                    //std::cerr << mapElements.size() << std::endl;
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

void Level::save() {
    std::ofstream s("saves/save_map.bin");
    s << width << " " << height << std::endl;
    s << "level1.png" << std::endl;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if(map[i][j].state != Empty) {
                s << i << " " << j << " " << int(map[i][j].state) << " " << 0 << std::endl;
            }
        }
    }
    s.close();
}

bool Level::isLoaded() {
    return this->loaded;
}

bool Level::isFinished() {
    return mapElements.empty();
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
    //printf("rysuje\n");
    Player *p = dynamic_cast<Player*>(player);
    // draw other entities
    HostileNPC *npc;
    std::vector<Entity*> newElements;
    for(auto it = mapElements.begin(); it != mapElements.end(); it++) {
        npc = dynamic_cast<HostileNPC*>(*it);
        if(npc != NULL) {
            if(npc->getHealth() <= 0) { //if entity is dead
                int x = npc->getPosition().x/50, y = npc->getPosition().y/50;
                map[x][y].state = Empty;
                map[x][y].entity = NULL;
                if(!npc->dead) {
                    sm->play(Dead); //play some music
                    npc->dead = 1;
                }
                continue;
            } else {
                DMG* d = npc->interact(p, map); //make our mob alive
                if(d != NULL) {
                    mapElements.push_back(d);
                }
                newElements.push_back(*it);
            }
        }else{
            if((*it)->getHealth() <= 0)
                continue;
            newElements.push_back(*it);
        }
        (*it)->draw(w);

    }
    mapElements = newElements;
    //add more health every 60 frames
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
