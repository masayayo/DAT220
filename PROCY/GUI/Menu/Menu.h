//
// Created by Chrim14 on 05.10.2017.
//

#ifndef PROCY_GUI_MAINMENU_H
#define PROCY_GUI_MAINMENU_H

#define bWidthStart 0.33f
#define bLength 0.33f
#define bHeight 0.1f

#include "../../Game.h"
#include "SettingButtons.h"
#include "../../Engine/Settings.h"

class Menu{
public:
    Menu() = default;

    void Main(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    void Option(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    void SingelPlayer(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    void MultiPlayer(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    void LanguageSetting(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    void KeybindingSettings(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    void getNewGameMenu(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager);

    static void setBackground(tgui::Gui &gui);
};


#endif //PROCY_GUI_MAINMENU_H
