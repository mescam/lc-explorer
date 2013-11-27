#ifndef HOSTILE_NPC_H
#define HOSTILE_NPC_H

#include "NPC.h"
#include "item.h"

#include <vector>

class HostileNPC {
    public:
        HostileNPC(std::string name): NPC(name) {
            // tutaj wczytać dane przeciwnika z jakiegoś pliku czy coś?
        }
        short getExperience() {
            return experience;
        }
        std::vector<Item> getLoot() {
            return loot;
        }
    private:
    protected:
        short EL;
        short experience;   // to może być nie potrzebne
        std::vector<Item> loot;
};

#endif // HOSTILE_NPC_H