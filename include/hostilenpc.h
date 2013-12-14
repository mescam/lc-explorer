#ifndef HOSTILE_NPC_H
#define HOSTILE_NPC_H

#include "npc.h"
#include "item.h"
#include "player.h"
#include "level.h"
#include <vector>

class HostileNPC : public NPC {
public:
    HostileNPC(std::string name, short exp, std::string image): NPC(name, image), experience(exp) {
        health = 10*(rand()%10 +1 );
        type = rand()%3;
    }
    short getExperience() {
        return experience;
    }

    void interact(Player *p, Field** map);
    void setPosition(sf::Vector2f p);
private:
protected:
    short experience;
    short type;
    int coolOff = 0;
    sf::Vector2f destination;
    bool destinationSet = false;
    sf::Vector2f motion;
};

#endif // HOSTILE_NPC_H