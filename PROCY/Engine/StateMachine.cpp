//
// Created by Chrim14 on 05.10.2017.
//

#include <SFML/Window.hpp>
#include "StateMachine.h"
#include "../GUI/Menu/Menu.h"
#include "../GUI/MapEditor/EditorSetup.h"
#include "../System/Game/Timer.h"
#include "../GUI/Menu/MenuPanels.h"
#include "Div/KeyBinds.h"

void message(const std::string stateInfo){
    lDebug("updating interface in State: "+stateInfo);
}

void StateMachine::updateInterface(Timer &gameTimer,tgui::Gui &gui,sf::RenderWindow &window, StateMachine &stateMachine, Settings &json, Sound &sound, WaveManager &waveManager) {

    Menu menu;
    EditorSetup editorSetup;

    switch (StateController::getState()){

        case List_State::Zero:break;

        case List_State::Main_Menu:
            message("Main_Menu");
            gui.removeAllWidgets();
            menu.Main(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;

        case List_State::Option_Menu:
            message("Option_Menu");
            gui.removeAllWidgets();
            menu.Option(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;

        case List_State::EditorSetup:
            message("EditorSetup");
            gui.removeAllWidgets();
            editorSetup.getEditorSetupMenu(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;

        case List_State::MapEditor:
            message("MapEditor");
            gui.removeAllWidgets();
            editorSetup.getEditorMenu(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;

        case List_State::Settings:
            message("Settings");
            gui.removeAllWidgets();
            Menu::setBackground(gui);
            menuPanel::getSettings(json.system["setting"],gameTimer,gui,window,stateMachine,json,sound,waveManager);
            break;

        case List_State::Singleplayer_Menu:
            message("Singleplayer_Menu");
            gui.removeAllWidgets();
            menu.SingelPlayer(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;

        case List_State::New_Game:
            message("New_Game");
            gui.removeAllWidgets();
            menu.getNewGameMenu(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;

        case List_State::Load_Game:
            message("Load_Game");
            gui.removeAllWidgets();
            Menu::setBackground(gui);
            menuPanel::getLoadPanel(gameTimer,gui,window,stateMachine,json,sound,waveManager);

            break;

        case List_State::Multiplayer_Menu:
            message("Multiplayer_Menu");
            gui.removeAllWidgets();
            menu.MultiPlayer(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;

        case List_State::Host_Game:
            message("Host_Game");
            break;

        case List_State::Join_Game:
            message("Join_Game");
            break;

        case List_State::Game:
            message("Game");
            gui.removeAllWidgets();
            break;

        case List_State::Pause:
            message("Pause");
            menuPanel::getPause(gameTimer, gui, window, stateMachine, json, sound, waveManager);
            break;

        case List_State::Language:
            message("Language");
            gui.removeAllWidgets();
            menu.LanguageSetting(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;

        case List_State::Keybinding:
            message("Keybinding");
            gui.removeAllWidgets();
            menu.KeybindingSettings(gameTimer,gui, window, stateMachine, json, sound, waveManager);

            break;
        case List_State::Game_Done:
            break;
    }
}

