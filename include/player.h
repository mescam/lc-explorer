#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

enum class EProfessions {
    Archer = 0,
    Mage,
    Wizard,
    COUNT //NOT A PROFESSION!
};

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
        Player(std::string name, std::string image): Entity(name,image) {
            
        }
        virtual void levelUp() {};
        void increaseAbilityScore(EAbilities a) {
            abilities[a]++;
        }
        short getMaxHealth() {
            return maxHealth;
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
        short getExperience() {
            return experience;
        }
    private:
    protected:
        short maxHealth;
        short health;
        short level = 1;
        short experience;
        short energy;
        short abilities[6];
};

class CArcher: public Player {
public: 
    CArcher(std::string name): Player(name,"archer.png") {
        this->abilities[Strenght] = 2;
        this->abilities[Dexterity] = 4;
        this->abilities[Constitution] = 3;
        this->abilities[Intelligence] = 2;
        this->abilities[Wisdom] = 2;
        this->abilities[Charisma] = 2;

        this->maxHealth = 8;
        this->health = this->maxHealth;
    }
};

class CMage: public Player {
public: 
    CMage(std::string name): Player(name,"mage.png") {
        this->abilities[Strenght] = 1;
        this->abilities[Dexterity] = 3;
        this->abilities[Constitution] = 1;
        this->abilities[Intelligence] = 3;
        this->abilities[Wisdom] = 5;
        this->abilities[Charisma] = 5;

        this->maxHealth = 6;
        this->health = this->maxHealth;
    }
};

class CKnight: public Player {
public: 
    CKnight(std::string name): Player(name,"knight.png") {
        this->abilities[Strenght] = 5;
        this->abilities[Dexterity] = 2;
        this->abilities[Constitution] = 5;
        this->abilities[Intelligence] = 1;
        this->abilities[Wisdom] = 2;
        this->abilities[Charisma] = 3;

        this->maxHealth = 10;
        this->health = this->maxHealth;
    }
};

#endif // PLAYER_H