#include "createplayerstate.h"
#include "engine.h"
#include "defaults.h"
#include "splash.h"
#include "player.h"


CreatePlayerState::CreatePlayerState(Engine *_engine) {
    engine = _engine;
    professions.push_back("Archer");
    professions.push_back("Mage");
    professions.push_back("Wizard");
}

void CreatePlayerState::init() {
    tWallBackground = new sf::Texture();
    tWallBackground->loadFromFile("images/wall_clean.png");
    wallBackground = new sf::Sprite(*tWallBackground);
    font = new sf::Font();
    font->loadFromFile(DEFAULT_FONT);
    
    //hint: Your name, so user knows that he has to input it
    hintName = new sf::Text("Your name:", *font);
    hintName->setCharacterSize(22);
    centerOrigin(*hintName);
    hintName->setPosition(DEFAULT_WINDOW_X/2, 450);
    //container for presenting input name
    tName = new sf::Text("", *font);
    tName->setCharacterSize(28);
    centerOrigin(*tName);

    //reset some things
    selectedProfession = 1;

    //welcome title
    welcome = new sf::Text("Choose your destiny!", *font);
    welcome->setCharacterSize(36);
    centerOrigin(*welcome);
    welcome->setPosition(DEFAULT_WINDOW_X/2, 40);
}

void CreatePlayerState::deinit() {
    delete tWallBackground;
    delete wallBackground;
    delete font;
    delete hintName;
    delete tName;
    delete welcome;
    name.clear();
}

void CreatePlayerState::draw() {
    sf::RenderWindow *window = engine->getWindow();
    window->draw(*wallBackground);

    tName->setString(name.c_str());
    centerOrigin(*tName);
    tName->setPosition(DEFAULT_WINDOW_X/2, 520);

    window->draw(*tName);
    window->draw(*hintName);
    window->draw(*welcome);

    drawProfessions();
}

void CreatePlayerState::handleEvents(sf::Event theEvent) {
    if(theEvent.type == sf::Event::KeyPressed) {
        switch(theEvent.key.code) {
            case sf::Keyboard::Return: {
                //sth;
                if(name.empty())
                    return;
                
                //do sth about creating player
                setNewState(EState::Game);
                break;
            }
            case sf::Keyboard::Escape: {
                setNewState(EState::Menu);
                break;
            }
            case sf::Keyboard::BackSpace: {
                if(name.size()>0)
                    name.pop_back();
                break;
            }
            case sf::Keyboard::Left: {
                if(selectedProfession > 0)
                    selectedProfession--;
                break;
            }
            case sf::Keyboard::Right: {
                if(selectedProfession < professions.size()-1)
                    selectedProfession++;
                break;
            }
            default: {
                break;
            }
        }
    }

    if(theEvent.type == sf::Event::TextEntered) {
        int num = int(theEvent.text.unicode);
        if(!((num > 47 && num < 58) || (num > 64 && num < 91) || (num > 96 && num < 123) || num == 95 || num == 32))
            return; //have a nice day debugging this.
        char x = static_cast<char>(theEvent.text.unicode);
        // printf("got %c\n", x);
        name += x; //wtf?
    }
}

void CreatePlayerState::drawProfessions() { //draws professions on the screen
    //it seems like I have to explain some magic 
    sf::RenderWindow *window = engine->getWindow();
    sf::Text profession("", *font);
    profession.setCharacterSize(32);

    //position of end of area designed for one profession
    int xPosIter = DEFAULT_WINDOW_X/professions.size();
    //pixels to left shift so we have center of this area
    int pixelShift = xPosIter/2;

    //and iterate!
    for(unsigned int i = 0; i < professions.size(); ++i) {
        std::string p = professions[i];
        profession.setString(p.c_str());
        centerOrigin(profession);
        profession.setPosition(xPosIter*(i+1)-pixelShift, DEFAULT_WINDOW_Y/2);
        profession.setColor((i == selectedProfession) ? sf::Color(255, 0, 0) : sf::Color(255, 255, 255));
        window->draw(profession);        
    }
}