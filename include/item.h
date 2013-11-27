#ifndef ITEM_H
#define ITEM_H

#include "entity.h"

class Item : public Entity {
    public:
        Item(std::string name, std::string gameTexture, std::string inventoryTexture): Entity(name,gameTexture) {
            sf::Texture iTexture;
            iTexture.loadFromFile(inventoryTexture);
            inventorySprite.setTexture(iTexture);
        }  
        virtual void pickUp() {};
        virtual void drop() {};
        virtual void sell() {};
        virtual void buy() {};
        sf::Sprite getInventorySprite() {
            return inventorySprite;
        } 
    private:
    protected:
        sf::Sprite inventorySprite;
};

#endif // ITEM_H
