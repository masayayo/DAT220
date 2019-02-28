//
// Created by Chrim14 on 05.10.2017.
//

#ifndef PROCY_STATES_H
#define PROCY_STATES_H

#include <stack>
#include "../Debugger/Logging.h"

/** List of all states **/
enum class List_State {
    Zero,
    Main_Menu,
        Option_Menu,
            EditorSetup,
            MapEditor,
            Settings,
            Language,
            Keybinding,
        Singleplayer_Menu,
            New_Game,
            Load_Game,
        Multiplayer_Menu,
            Host_Game,
            Join_Game,
        Game,
        Pause,
        Game_Done
};

class StateController {

public:

    StateController() = default;

    List_State getState();

    void NextState(List_State nextState);

    void StartStateStack();

    bool isEmpty();

private:

    void pushState(List_State nextState);

    void popState();

    std::stack<List_State> State;

};

#endif //PROCY_STATES_H
