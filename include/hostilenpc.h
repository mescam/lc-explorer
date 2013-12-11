#ifndef HOSTILE_NPC_H
#define HOSTILE_NPC_H

#include "NPC.h"
#include "item.h"

#include <vector>

class HostileNPC {
    public:
        HostileNPC(std::string name, short exp): NPC(name), experience(exp) {
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
        short experience;   // to może być niepotrzebne
        std::vector<Item> loot;
};

#endif // HOSTILE_NPC_H