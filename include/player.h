#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

enum EAbilities {
    Strenght = 0,
    Dexterity,
    Constitution,
    Intelligence,
    Wisdom,
    Charisma
};

class Player: public Entity {
    public:
        Player(std::string name): Entity(name,"img/player.png") {
            
        }
        virtual void levelUp() {};
        void increaseAbilityScore(EAbilities a) {
            abilities[a]++;
        }
        short getHealth() {
            return health;
        }
        short getLevel() {
            return level;
        }
        short getEnergy() {
            return energy;
        }
        short getAbilityScore(EAbilities a) {
            return abilities[a];
        }
    private:
    protected:
        short health;
        short level = 1;
        short energy;
        short abilities[6];
};

#endif // PLAYER_H