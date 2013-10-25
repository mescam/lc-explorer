#ifndef SPLASH_H
#define SPLASH_H
#include <SFML/Graphics.hpp>
#include <iostream>
template <class T> void centerObject(T &object, sf::Vector2u size) {
    sf::FloatRect textRect = object.getLocalBounds();
    object.setOrigin(textRect.left + textRect.width/2.0f,
            textRect.top + textRect.height/2.0f);
    object.setPosition(sf::Vector2f((size.x)/2, (size.y/2)));
}
#endif
