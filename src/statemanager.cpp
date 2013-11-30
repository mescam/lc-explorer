#include "statemanager.h"
#include <SFML/Graphics.hpp>
#include "engine.h"
#include "state.h"

#include "splashstate.h"
#include "menustate.h"
#include "gamestate.h"
#include "aboutstate.h"
#include "introstate.h"
#include "createplayerstate.h"


StateManager::StateManager(Engine *_engine) {
    engine = _engine;
    active = EState::Splash;
    states.resize(int(EState::COUNT));

    //loading states objects
    states[int(EState::Splash)] = new SplashState(engine);
    states[int(EState::Menu)] = new MenuState(engine);
    states[int(EState::Game)] = new GameState(engine);
    states[int(EState::About)] = new AboutState(engine);
    states[int(EState::Intro)] = new IntroState(engine);
    states[int(EState::CreatePlayer)] = new CreatePlayerState(engine); 
    //there is no memory leak above us.
}

StateManager::~StateManager() {
    for(auto it = states.begin(); it != states.end(); ++it) {
        delete *it;
    }
    states.clear();
}

IState *StateManager::getActiveState() {
    return states[int(active)];
}

IState *StateManager::getStateObject(EState get) {
    return states[int(get)];
}

void StateManager::changeState(EState _new, bool pause) {
    /*
     * init state if not initialized
     * resume if paused
     * pause or deinit old state
     */
    if(_new == active)
        return;

    if(pause)
        getActiveState()->pause();
    else
        getActiveState()->deinit();

    active = _new; //changed state

    if(!getActiveState()->isInitialized())
        getActiveState()->init();
    else if (!getActiveState()->isPaused())
        getActiveState()->resume();
}
