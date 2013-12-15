#include "player.h"
#include "hostilenpc.h"

Player::Player(std::string name, std::string image): Entity(name,image) {
    primarySprite.setTextureRect(sf::Rect<int>(0, 0, 40, 40));
    centerOrigin(primarySprite); //center origin again, as we changed texture size
}


void Player::setPosition(sf::Vector2f p) {
    position = p;
    primarySprite.setPosition(position);
    if(motion.x == 1) {
        primarySprite.setTextureRect(sf::IntRect(40*(int(p.x/30)%3), 40, 40, 40));
    }
    if(motion.x == -1) {
        primarySprite.setTextureRect(sf::IntRect(40*(int(p.x/30)%3), 120, 40, 40));
    }
    if(motion.y == 1) {
        primarySprite.setTextureRect(sf::IntRect(40*(int(p.y/30)%3), 0, 40, 40));
    }
    if(motion.y == -1) {
        primarySprite.setTextureRect(sf::IntRect(40*(int(p.y/30)%3), 80, 40, 40));
    }
}


std::string Player::getProfessionName() {
    switch(int(profession)) {
        case 0: return "Archer";
        case 1: return "Mage";
        case 2: return "Knight";
    }
    return "Unknown";
}

void Player::save() {
    std::ofstream s("saves/save_player.bin");
    s << int(profession) << std::endl;
    s << name << std::endl;
    s << maxHealth << std::endl;
    s << health << std::endl;
    s << experience << std::endl;
    s << energy << std::endl;
    s.close();
}

void Player::load() {
    std::ifstream s("saves/save_player.bin");
    int p;
    s >> p;
    profession = EProfessions(p);
    s >> name;
    s >> maxHealth;
    s >> health;
    s >> experience;
    s >> energy;
    s.close();
}

DMG* CArcher::attack(Field **map) {
    sm->play(Bow);
    DMG *o = NULL;
    int x = position.x/50;
    int y = position.y/50;
    switch(lookingDirection) {
        case 1:
        y--;
        while(map[x][y].state != Obstacle) {
            if(map[x][y].state == Enemy) break;
            y--;
        }
        break;
        case 2:
        x++;
        while(map[x][y].state != Obstacle) {
            if(map[x][y].state == Enemy) break;
            x++;
        }
        break;
        case 3:
        y++;
        while(map[x][y].state != Obstacle) {
            if(map[x][y].state == Enemy) break;
            y++;
        }
        break;
        case 4:
        x--;
        while(map[x][y].state != Obstacle) {
            if(map[x][y].state == Enemy) break;
            x--;
        }
        break;
    }
    if(map[x][y].state == Enemy) {
        HostileNPC *e = dynamic_cast<HostileNPC*>(map[x][y].entity);
        e->setHealth(e->getHealth() - 8);
        if(e->getHealth() <= 0)
            experience += 10;
        o = new DMG(8, true, e->getPosition());
    }
    return o;
}


DMG* CMage::attack(Field **map) {
    sm->play(Mage);
    int x = position.x/50;
    int y = position.y/50;
    DMG *o = NULL;
    switch(lookingDirection) {
        case 1:
        y--;
        while(map[x][y].state != Obstacle) {
            if(map[x][y].state == Enemy) break;
            y--;
        }
        break;
        case 2:
        x++;
        while(map[x][y].state != Obstacle) {
            if(map[x][y].state == Enemy) break;
            x++;
        }
        break;
        case 3:
        y++;
        while(map[x][y].state != Obstacle) {
            if(map[x][y].state == Enemy) break;
            y++;
        }
        break;
        case 4:
        x--;
        while(map[x][y].state != Obstacle) {
            if(map[x][y].state == Enemy) break;
            x--;
        }
        break;
    }
    if(map[x][y].state == Enemy) {
        HostileNPC *e = dynamic_cast<HostileNPC*>(map[x][y].entity);
        e->setHealth(e->getHealth() - 15);
        if(e->getHealth() <= 0)
            experience += 10;
        o = new DMG(15, true, e->getPosition());
    }
    return o;
}

DMG* CKnight::attack(Field **map) {
    sm->play(Knife);
    DMG* o = NULL;
    for(int i=-1; i <= 1; i++) {
        for(int j=-1; j <= 1; j++) {
            int x = int(position.x/50)+i;
            int y = int(position.y/50)+j;
            if(map[x][y].state == Enemy) {
                HostileNPC *e = dynamic_cast<HostileNPC*>(map[x][y].entity);
                e->setHealth(e->getHealth()-12);
                if(e->getHealth() <= 0) {
                    this->experience += 10;
                }
                o = new DMG(12, true, this->getPosition());
            }
        }
    }
    return o;
}