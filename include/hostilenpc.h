#ifndef HOSTILE_NPC_H
#define HOSTILE_NPC_H

#include "npc.h"
#include "player.h"
#include "level.h"
#include "dmg.h"
#include <vector>

class HostileNPC : public NPC {
public:
    HostileNPC(std::string name, short exp, std::string image): NPC(name, image), experience(exp) {
        health = 10*(rand()%10 +1 );
        type = rand()%3; //rand... :X
    }
    short getExperience() {
        return experience;
    }

    DMG* interact(Player *p, Field** map);
    void setPosition(sf::Vector2f p);
    int dead = 0; //if he is dead?
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