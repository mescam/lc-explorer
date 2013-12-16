#include "hostilenpc.h"

DMG* HostileNPC::interact(Player *p, Field** map) {
        DMG* o = NULL;
        if(coolOff > 0) { // not ready to do anything
            coolOff--;
            return 0;
        }
        int x = position.x/50, y = position.y/50;
        for(int i = -1; i <= 1; i++) { //for each of neighbour fields
            for(int j = -1; j <= 1; j++) {
                if(map[x+i][y+j].state == Character) { //if there is a character nearby
                    // kill him!
                    int dmg = rand()%(p->getMaxHealth()/2);
                    p->setHealth(p->getHealth()-dmg);
                    coolOff = 60; // and rest
                    o = new DMG(dmg, false, p->getPosition());
                    return o;
                }
            }
        }
        // going somewhere
        if(!destinationSet) { //if there is no destination point for him
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    if(map[x+i][y+j].state == Empty && rand()%100 < 5) { //maybe it could be good
                        destination = sf::Vector2f((x+i)*50+20, (y+j)*50+20); //set it!
                        destinationSet = true;
                    }
                }
            }
        } else { //if we have somewhere to go
            int d_x = destination.x - position.x,
                d_y = destination.y - position.y; //calculate distance
            d_x = (d_x > 0) ? 2 : ((d_x < 0) ? -2 : 0); // set delta limits
            d_y = (d_y > 0) ? 2 : ((d_y < 0) ? -2 : 0);
            sf::Vector2f newPosition(position.x + d_x, position.y + d_y); // get new position
            if(map[int(newPosition.x/50)][int(newPosition.y/50)].state != Empty && //check if it's legal
                map[int(newPosition.x/50)][int(newPosition.y/50)].entity != this) {
                destination = sf::Vector2f(0, 0); //if not - reset vector
            destinationSet = false;
            coolOff = 120;
            } else { //if it's legal
                if(d_y > 0) motion.y = 1; //check motion animation frame
                if(d_y < 0) motion.y = -1;
                if(d_x > 0) motion.x = 1;
                if(d_x < 0) motion.x = -1;
                this->setPosition(newPosition); //set position on map
                map[x][y].state = Empty; //reset old field state
                map[x][y].entity = NULL; //and below set new one
                map[int(newPosition.x/50)][int(newPosition.y/50)].state = Enemy;
                map[int(newPosition.x/50)][int(newPosition.y/50)].entity = this;
                motion.x = motion.y = 0; //reset motion
            }
            if(d_x < 2 && d_x > -2 && d_y < 2 && d_y > -2) { //if we've reached our destination point
                destination = sf::Vector2f(0, 0); //reset vector
            destinationSet = false;
            coolOff = 120;
        }
    }
    return o;
}

void HostileNPC::setPosition(sf::Vector2f p) {
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