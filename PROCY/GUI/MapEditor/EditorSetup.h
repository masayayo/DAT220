//
// Created by Chrim14 on 10.10.2017.
//

#ifndef PROCY_EDITORSETUP_H
#define PROCY_EDITORSETUP_H

#include <vector>
#include <TGUI/TGUI.hpp>
#include "EditorChildWindows.h"
#include "../Sound/Sound.h"
#include "../../Engine/StateMachine.h"
#include "../../Engine/Settings.h"
#include "../../System/Map/Map.h"
#include "../../System/Map/FileHandler.h"
#include "../../System/Game/Timer.h"

class EditorChildWindows;

class EditorSetup {
public:
    EditorSetup() = default;

    void setNewMapValues(tgui::Gui &gui, Settings &json);

    void getEditorSetupMenu(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    void getEditorMenu(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    void getTileList(std::string tileName, const tgui::ListBox::Ptr &tile,tgui::Gui &gui, Settings &json);

    void drawImage(bool panel, bool childWindow, tgui::Gui &gui, Settings &json);

    void changeTileList(std::string tileName, tgui::Gui &gui, Settings &json);

    void changeDrawTile(tgui::Gui &gui, Settings &json);

    sf::Image rotateImage90degree(const sf::Image &temp);
};

#endif //PROCY_EDITORSETUP_H
