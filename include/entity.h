#ifndef ENTITY_H
#define ENTITY_H

#include "splash.h"

#include <string>
#include <SFML/Graphics.hpp>

class Entity {
    public:
        Entity(std::string name, std::string textureFilename): name(name) {
            std::string texturePath = "images/" + textureFilename;
            eTexture.loadFromFile(texturePath);
            primarySprite.setTexture(eTexture);         
            centerOrigin(primarySprite);   
        }
        virtual void draw() {};
        std::string getName() {
            return name;
        }
        sf::Sprite& getPrimarySprite() {
            return primarySprite;
        }
        void setPosition(sf::Vector2f p) {
            position = p;
        }
        sf::Vector2f getPosition() {
            return position;
        }
    private:
    protected:
        sf::Sprite primarySprite;
        std::string name;
        sf::Texture eTexture;
        sf::Vector2f position;
};

#endif // ENTITY_H
