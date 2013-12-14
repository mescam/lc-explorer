#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <string>
#include "level.h"


enum class EProfessions {
    Archer = 0,
    Mage,
    Knight,
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
        Player(std::string name, std::string image);
        virtual ~Player() {};
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
        void setHealth(int x) {
            health = x;
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
        std::string getProfessionName();

        void setPosition(sf::Vector2f p) {
            position = p;
            primarySprite.setPosition(position);
            if(motion.x == 1) {
                primarySprite.setTextureRect(sf::IntRect(40*(int(p.x/30)%3), 40, 40, 40));
            }
            if(motion.x == -1) {
                primarySprite.setTextureRect(sf::IntRect(40*(int(p.x/30)%3), 120, 40, 40));
            }
            if(motion.y == 1) {
                primarySprite.setTextureRect(sf::IntRect(40*(int(p.y/30)%3), 0, 40, 40));
            }
            if(motion.y == -1) {
                primarySprite.setTextureRect(sf::IntRect(40*(int(p.y/30)%3), 80, 40, 40));
            }
        }
        virtual void attack(Field **map) {}
        sf::Vector2f motion;
        short lookingDirection = 3;
    private:
    protected:
        short maxHealth;
        short health;
        short level = 1;
        short experience = 0;
        short energy;
        short abilities[6];
        EProfessions profession;        
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
        this->profession = EProfessions::Archer;
    }

    void attack(Field **map);
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
        this->profession = EProfessions::Mage;
    }

    void attack(Field **map);
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
        this->profession = EProfessions::Knight;
    }

    void attack(Field **map);
};

#endif // PLAYER_H