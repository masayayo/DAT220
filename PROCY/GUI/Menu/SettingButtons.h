//
// Created by Admin on 08.10.2017.
//

#ifndef PROCY_SETTINGBUTTONS_H
#define PROCY_SETTINGBUTTONS_H

#include <TGUI/TGUI.hpp>
#include "../../Debugger/Logging.h"
#include "../../Engine/Div/Language.h"
#include "../../Engine/Settings.h"
#include "../Sound/Sound.h"

class SettingButtons {
public:
    SettingButtons() = default;

    void applySettings(bool reset, sf::RenderWindow &window, tgui::Gui &gui, Settings &json,Sound &sound);

    static void setSettings(sf::RenderWindow &window, tgui::Gui &gui, Settings &json,Sound &sound);

    void applySelectedLanguage(Settings &json, tgui::Gui &gui);

    static void getResolution(tgui::Gui &gui, Settings &json);
};

#endif //PROCY_SETTINGBUTTONS_H
