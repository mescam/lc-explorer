#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>

class Entity {
    public:
        Entity(std::string name, std::string textureFilename): name(name) {
            sf::Texture eTexture;
            std::string texturePath = "images/" + textureFilename;
            eTexture.loadFromFile(texturePath);
            primarySprite.setTexture(eTexture);            
        }
        virtual void draw() {};
        std::string getName() {
            return name;
        }
        sf::Sprite getPrimarySprite() {
            return primarySprite;
        }
    private:
    protected:
        sf::Sprite primarySprite;
        std::string name;
};

#endif // ENTITY_H
