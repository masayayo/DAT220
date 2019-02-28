//
// Created by Chrim14 on 31.10.2017.
//

#ifndef PROCY_EDITORCHILDWINDOWS_H
#define PROCY_EDITORCHILDWINDOWS_H

#include <TGUI/Gui.hpp>
#include "EditorSetup.h"
#include "../../System/Map/FileHandler.h"

class EditorSetup;

class EditorChildWindows{
public:
    void getTileChildMenu(tgui::Gui &gui, sf::RenderWindow &window, Settings &json);

    void getSaveChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json);

    void getLoadChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json, StateMachine &state, Sound &sound);

    void getPlayerMonsterChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json);

    void getInformation(tgui::Gui &gui, sf::RenderWindow &window, Settings &json);

    void getSelectedTileChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json);

    void updateSelectedTileChildWindow(tgui::Gui &gui, Settings &json);

    void getDescriptionChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json);

private:

    void RadioOptionShearedOrDivided(tgui::Gui& gui, int option, Settings &json);

    void RadioOptionDividedTrueOrFalse(tgui::Gui &gui, Settings &json);

    void RadioOptionFixedOrDefinedWaves(tgui::Gui &gui, Settings &json, int option);
};


#endif //PROCY_EDITORCHILDWINDOWS_H
