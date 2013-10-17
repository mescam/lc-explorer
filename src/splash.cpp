#include "splash.h"

Splash::Splash(Engine& _engine) : engine(_engine) {
    //engine = Engine::getInstance();
    font.loadFromFile("fonts/Grundschrift.ttf");
    title.setFont(font);
    title.setString("Trouble in Lecture Centre");
    title.setCharacterSize(50);
    //checking window resolution for centering text
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    sf::Vector2u size = engine.getWindow().getSize();
    title.setPosition(sf::Vector2f((size.x)/2, (size.y/2)));
}

void Splash::animate()  {
    float alpha = 0.0f;
    for(int i = 0; i < 2*3*60; ++i) {
        engine.getWindow().clear();
        sf::Color c(255, 255, 255, int(alpha));
        title.setColor(c);
        engine.getWindow().draw(title);
        engine.getWindow().display();
        if (i>=3*60)
            alpha -= 255.0f/180.0f;
        else
            alpha += 255.0f/180.0f;
    }
}

