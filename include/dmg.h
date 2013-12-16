#ifndef DMG_H
#define DMG_H

#include <SFML/Graphics.hpp>

class DMG : public Entity {
    public:
        // generates simple text with dealed damage
        DMG(short val, bool attack, sf::Vector2f position) : Entity("dmg", "dummy.png") {
            font.loadFromFile("fonts/Minecraftia.ttf");
            this->val = val;
            this->position = position;
            if(attack) {
                c = sf::Color::Green;
            }else{
                c = sf::Color::Red;
            }
            text.setFont(font);
            text.setColor(c);
            text.setCharacterSize(16);
            text.setString(std::to_string(val));
        }

        short getHealth() {
            return life;
        }

        void draw(sf::RenderWindow *w) {
            life--;
            text.setPosition(position);
            w->draw(text);
            position.y = position.y - 3;
        }

    private:
        short life = 60; //yeah, it has life :D
        short val;
        sf::Color c;
        sf::Font font;
        sf::Text text;
        sf::Vector2f position;
};

#endif