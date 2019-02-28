//
// Created by Chrim14 on 06.11.2017.
//

#ifndef PROCY_EDITORSTATICGUIFUNCTIONS_H
#define PROCY_EDITORSTATICGUIFUNCTIONS_H


#include <TGUI/Gui.hpp>
#include "../../Engine/Settings.h"

class esf {
public:
    static void getWeightTguiChange(bool already_checked, std::string direction, tgui::Gui &gui, Settings &json);

    static void setWeightChangeLabel(std::string direction, tgui::Gui &gui);

    ///Calculate the different between all four sliders
    static void setWeightSliderChanges(std::string direction, std::string panel,  tgui::Gui &gui);

    static void getPanelCreateSplitter(tgui::Gui &gui, Settings &json);

    static void setRoadTileOption(int check_box, tgui::Gui &gui, Settings &json);

    static void clearSpecialTileView(tgui::Gui &gui);

    static void updatePanels(tgui::Gui &gui, Settings &json, std::string Tile_Type);

    static void getPanelDirection(tgui::Gui &gui, Settings &json, std::string &Tile_Type);

    static void getPanelWeight(tgui::Gui &gui, Settings &json, std::string &Tile_Type);

    static void getPanelSpeed(tgui::Gui &gui, Settings &json, std::string &Tile_Type);

    static void getPanelSelectPlayers(tgui::Gui &gui, Settings &json, std::string &Tile_Type);

    static void setMainPanelInfo(tgui::Gui &gui, Settings &json);

    static void getPanelTeleport(tgui::Gui &gui, Settings &json, std::string &Tile_Type);

    static void getPanelDestination(tgui::Gui &gui, Settings &json, std::string &Tile_Type);

    static void getTeleportList(tgui::Gui &gui, Settings &json, std::string &Tile_Type);

};


#endif //PROCY_EDITORSTATICGUIFUNCTIONS_H
