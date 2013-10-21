#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <vector>
#include "state.h"
class StateManager {
    public:
        IState *getActiveState();
        enum State {
            SplashState = 0,
            MenuState,
            GameState,
            OptionsState,
            EndState,
        };
        void changeState(State _new);
    private:
        std::vector<IState*> states;
        enum State active;

};

#endif
