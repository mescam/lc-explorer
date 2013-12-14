#ifndef HOSTILE_NPC_H
#define HOSTILE_NPC_H

#include "npc.h"
#include "item.h"
#include "player.h"
#include "level.h"
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

    void interact(Player *p, Field** map) {
        int x = position.x/50, y = position.y/50;
        // std::cerr << "Thinking about beating someone" << std::endl;
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                if(map[x+i][y+j].state == Character) {
                    if(coolOff > 0) {
                        coolOff--;
                        return;
                    }
                    p->setHealth(p->getHealth()-rand()%p->getMaxHealth());
                    coolOff = 60;
                    return;
                }
            }
        }
        // std::cerr << "Thinking about joruney" << std::endl;
        if(!destinationSet) { //if there is no destination point for him
            // std::cerr << "I have to go somewhere" << std::endl;
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    if(map[x+i][y+j].state == Empty && rand()%100 < 10) { //maybe it could be good
                        destination = sf::Vector2f((x+i)*50+20, (y+j)*50+20); //set it!
                        // std::cerr << "I want to go there!" << std::endl;
                        destinationSet = true;
                    }
                }
            }
        } else { //if we have somewhere to go
            // std::cerr << "Going to my destination point" << std::endl;
            int d_x = destination.x - position.x,
            d_y = destination.y - position.y; //calculate distance
            d_x = (d_x > 0) ? d_x = 2 : (d_x < 0) ? -2 : 0;
            d_y = (d_y > 0) ? d_y = 2 : (d_y < 0) ? -2 : 0;
            sf::Vector2f newPosition(position.x + d_x, position.y + d_y);
            if(map[int(newPosition.x/50)][int(newPosition.y/50)].state != Empty &&
                map[int(newPosition.x/50)][int(newPosition.y/50)].entity != this) {
                // std::cerr << "My destination is blocked, sorry" << std::endl;
                destination = sf::Vector2f(0, 0);
            } else {
                if(d_y > 0) motion.y = 1;
                if(d_y < 0) motion.y = -1;
                if(d_x > 0) motion.x = 1;
                if(d_x < 0) motion.x = -1;
                this->setPosition(newPosition);
                map[x][y].state = Empty;
                map[x][y].entity = NULL;
                map[int(newPosition.x/50)][int(newPosition.y/50)].state = Enemy;
                map[int(newPosition.x/50)][int(newPosition.y/50)].entity = this;
                motion.x = motion.y = 0;
                // std::cerr << "Going there!" << std::endl;
            }
            if(d_x < 2 && d_x > -2 && d_y < 2 && d_y > -2) {
                destination = sf::Vector2f(0, 0);
                // std::cerr << "Already there, going somewhere else?" << std::endl;
                destinationSet = false;
            }
        }
    }

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