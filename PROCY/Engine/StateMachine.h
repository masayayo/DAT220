//
// Created by Chrim14 on 05.10.2017.
//

#ifndef PROCY_STATEMACHINE_H
#define PROCY_STATEMACHINE_H

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include "StateController.h"
#include "Settings.h"
#include "../GUI/Sound/Sound.h"
#include "../System/Game/Timer.h"
#include "../System/Entities/WaveManager.h"

class StateMachine : public StateController {
public:
    StateMachine() = default;

    void updateInterface(Timer &gameTimer,tgui::Gui &gui,sf::RenderWindow &window, StateMachine &stateMachine, Settings &json, Sound &sound, WaveManager &waveManager);

private:

};


#endif //PROCY_STATEMACHINE_H
