#ifndef NPC_H
#define NPC_H

#include "entity.h"

class NPC: public Entity {
    public:
        NPC(std::string name, std::string image): Entity(name, image) {
            primarySprite.setTextureRect(sf::Rect<int>(0, 0, 40, 40));
            centerOrigin(primarySprite);
        }
        short getHealth() {
            return health;
        }
        void setHealth(short h) {
            health = h;
        }
    private:
    protected:
        short health;        
};

#endif // NPC_H