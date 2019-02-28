//
// Created by Chrim14 on 05.10.2017.
//

#include "StateController.h"

void StateController::pushState(List_State nextState) {

    lDebug("Pushing state");
    State.push(nextState);
}

void StateController::popState() {

    if (!State.empty()) {
        lDebug("Popping state");
        State.pop();
        return;
    }
    lError("Tried to pop state, stack empty");
}

bool StateController::isEmpty() {
    return State.empty();
}

List_State StateController::getState() {


    if(!State.empty()) return State.top();

    lError("Top state not found");

    return List_State::Zero;
}

void StateController::NextState(List_State nextState) {

    switch (StateController::getState()){

        case List_State::Zero:
            lDebug("Moving from state: Zero");
            if(nextState == List_State::Main_Menu){
                StateController::pushState(nextState);
            }
            else lError("States do not match, from Zero");
            break;

        case List_State::Main_Menu:
            lDebug("Moving from state: Main Menu");
            if(nextState == List_State::Zero){
                StateController::popState();
                StateController::popState();

            }
            else if(nextState == List_State::Option_Menu ||
                    nextState == List_State::Singleplayer_Menu ||
                    nextState == List_State::Multiplayer_Menu){
                StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::Option_Menu:
            lDebug("Moving from state: Option Menu");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else if(nextState == List_State::Settings ||
                    nextState == List_State::EditorSetup){
                StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::EditorSetup:
            lDebug("Moving from state: EditorSetup");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else if(nextState == List_State::MapEditor){
                   StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::MapEditor:
            lDebug("Moving from state: MapEditor");
            if(nextState == List_State::Zero){
                StateController::popState();
                StateController::popState();
                StateController::popState();

            } lError("States do not match");
            break;

        case List_State::Settings:
            lDebug("Moving from state: Settings");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else if(nextState == List_State::Language ||
                    nextState == List_State::Keybinding){
                StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::Singleplayer_Menu:
            lDebug("Moving from state: Singelplayer menu");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else if(nextState == List_State::New_Game  ||
                    nextState == List_State::Load_Game){
                StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::New_Game:
            lDebug("Moving from state: New Game");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else if(nextState == List_State::Game){
                StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::Load_Game:
            lDebug("Moving from state: Load_Game");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else if(nextState == List_State::Game){
                StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::Multiplayer_Menu:
            lDebug("Moving from state: Multiplayer Menu");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else if(nextState == List_State::Host_Game ||
                    nextState == List_State::Join_Game){
                //StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::Host_Game:break;
        case List_State::Join_Game:break;

        case List_State::Game:
            lDebug("Moving from state: Game");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else if(nextState == List_State::Pause){
                StateController::pushState(nextState);
            }
            else lError("States do not match");
            break;

        case List_State::Pause:
            lDebug("Moving from state: Pause");
            if(nextState == List_State::Zero){
                StateController::popState();
                StateController::popState();
                StateController::popState();
                StateController::popState();
            }
            else if(nextState == List_State::Game){
                StateController::popState();
            }
            else lError("States do not match");
            break;

        case List_State::Language:
            lDebug("Moving from state: Language");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else lError("States do not match");
            break;

        case List_State::Keybinding:
            lDebug("Moving from state: Keybinding");
            if(nextState == List_State::Zero){
                StateController::popState();
            }
            else lError("States do not match");
            break;
        case List_State::Game_Done:
            break;
    }
}

void StateController::StartStateStack() {

    lInfo("Starting state stack");

    if(!isEmpty())
        lError("Tried to start state stack, state stack not empty");

    pushState(List_State::Zero);
}


