#ifndef FRIENDLY_NPC_H
#define FRIENDLY_NPC_H

#include "npc.h"

#include <ctime>

class FriendlyNPC: public NPC {
    public:
        FriendlyNPC(std::string name): NPC(name) {
            srand(time(NULL));
            attitude = rand()%20+1;
        }
        short getAttitude() {
            return attitude;
        }
        void increaseAttitude(short i = 1) {
            attitude+=i;
        }
        void decreaseAttitude(short i = 1) {
            attitude-=i;
        }
        void talk() {};
        void trade() {};
        
    private:
    protected:
        short attitude;
};

#endif // FRIENDLY_NPC_H