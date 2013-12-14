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
        // virtual void draw() {};
        std::string getName() {
            return name;
        }
        sf::Sprite& getPrimarySprite() {
            return primarySprite;
        }
        virtual void setPositionOnMap(int x, int y) {
            position = sf::Vector2f(x*50+20, y*50+20);
            primarySprite.setPosition(position);
        }
        virtual void setPosition(sf::Vector2f p) {
            position = p;
            primarySprite.setPosition(position);
        }
        sf::Vector2f getPosition() {
            return position;
        }
        virtual void draw(sf::RenderWindow *w) {
            w->draw(primarySprite);
        }
        virtual void interact() {}
        // virtual void getHealth() {
        //     return 10;
        // }
    private:
    protected:
        sf::Sprite primarySprite;
        std::string name;
        sf::Texture eTexture;
        sf::Vector2f position;
};

#endif // ENTITY_H
