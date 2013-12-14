#ifndef HOSTILE_NPC_H
#define HOSTILE_NPC_H

#include "npc.h"
#include "item.h"

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
        /*std::vector<Item> getLoot() {
            return loot;
        }*/
    private:
    protected:
        short experience;
        short type;
};

#endif // HOSTILE_NPC_H