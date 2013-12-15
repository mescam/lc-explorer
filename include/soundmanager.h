#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <iostream>
#include <SFML/Audio.hpp>
enum Sounds {
    Knife,
    Bow,
    Mage,
    Dead,
};

class SoundManager {
    public:
        SoundManager() {
            if(!knife.loadFromFile("music/knife.wav") 
                || !bow.loadFromFile("music/bow.wav")
                || !mage.loadFromFile("music/spell.wav")
                || !dead.loadFromFile("music/pain.wav")) {
                std::cerr << "Error while loading music" << std::endl;
            }
        }

        void play(Sounds s){
            switch(s) {
                case Knife:
                    sound.setBuffer(knife);
                    break;
                case Bow:
                    sound.setBuffer(bow);
                    break;
                case Mage:
                    sound.setBuffer(mage);
                    break;
                case Dead:
                    sound.setBuffer(dead);
                    break;
            }
            sound.play();
        }

    private:
        sf::Sound sound;
        sf::SoundBuffer knife;
        sf::SoundBuffer bow;
        sf::SoundBuffer mage;
        sf::SoundBuffer dead;
};

#endif