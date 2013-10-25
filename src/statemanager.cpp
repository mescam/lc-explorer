#include "statemanager.h"
#include <SFML/Graphics.hpp>
#include "engine.h"
#include "state.h"

#include "splashstate.h"
#include "menustate.h"


StateManager::StateManager(Engine *_engine) {
    engine = _engine;
    active = EState::Splash;
    states.resize(int(EState::COUNT));
    states[0] = new SplashState(engine);
    states[1] = new MenuState(engine);
}

IState *StateManager::getActiveState() {
    return states[int(active)];
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
