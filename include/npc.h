#ifndef NPC_H
#define NPC_H

#include "entity.h"

class NPC: public Entity {
    public:
        NPC(std::string name): Entity(name,"img/NPC.png") {
        
        }
        short getHealth() {
            return health;
        }
    private:
    protected:
        short health;        
};

#endif // NPC_H