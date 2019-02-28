//
// Created by Chrim14 on 01.12.2017.
//

#ifndef PROCY_MENUPANELS_H
#define PROCY_MENUPANELS_H

#include "../../Engine/Settings.h"
#include "../../Engine/StateMachine.h"

class menuPanel {
public:
    static void getSettings(int panelChosen, Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    static void getPause(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    static void getGame(tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound);

    static void getLanguage(tgui::Gui &gui, Settings &json, Sound &sound);

    static void getKeys(tgui::Gui &gui, Settings &json, Sound &sound, sf::RenderWindow &window);

    static void setKey(tgui::Gui &gui, Settings &json);

    static void removePanel(tgui::Gui &gui);

    static bool panelThere(tgui::Gui &gui);

    static void getPlayers(Settings &json,tgui::Gui &gui);

    static void getMapSelected(Settings &json,tgui::Gui &gui, tgui::Label::Ptr label,tgui::ListBox::Ptr lMaps, tgui::Label::Ptr lSize, tgui::Label::Ptr lMapName, tgui::Label::Ptr lPlayers, tgui::Label::Ptr lSpawns, tgui::Label::Ptr story, tgui::Picture::Ptr image, tgui::Button::Ptr bLoad, tgui::Panel::Ptr pPlayers);

    static void getSavePanel(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    static void getLoadPanel(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);
};


#endif //PROCY_MENUPANELS_H
