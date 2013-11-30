#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <vector>
enum class EState {
    Splash = 0,
    Menu,
    Intro,
    Game,
    CreatePlayer,
    Load,
    Options,
    About,
    End,
    COUNT, //NOT A STATE!!!
};

class Engine;
class IState;

class StateManager {
    public:
        StateManager(Engine *_engine);
        ~StateManager();
        IState *getActiveState();
        IState *getStateObject(EState get);
        void changeState(EState _new, bool pause = false);
    private:
        std::vector<IState*> states;
        EState active;
        Engine *engine;

};

#endif
