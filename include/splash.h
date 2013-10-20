#ifndef SPLASH_H
#define SPLASH_H

#include <SFML/Graphics.hpp>
#include "engine.h"

template <class T>
class Splash {
    public:
        Splash(T &_object);
        void animate(int time);
        void centerObject();
    private:
        T &object;
};


template <class T>
Splash<T>::Splash(T& _object) : object(_object) {
    //nothing to do here
}

template <class T>
void Splash<T>::animate(int time)  {
    float alpha = 0.0f;
    for(int i = 0; i < time*60; ++i) {
        Engine::getInstance().getWindow().clear();
        sf::Color c(255, 255, 255, int(alpha));
        object.setColor(c);
        Engine::getInstance().getWindow().draw(object);
        Engine::getInstance().getWindow().display();
        if (i >= 60*(time/2))
            alpha -= 255.0f/180.0f;
        else
            alpha += 255.0f/180.0f;
    }
}

template <class T>
void Splash<T>::centerObject() {
    sf::FloatRect textRect = object.getLocalBounds();
    object.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    sf::Vector2u size = Engine::getInstance().getWindow().getSize();
    object.setPosition(sf::Vector2f((size.x)/2, (size.y/2)));
}
#endif
