//
// Created by Chrim14 on 10.10.2017.
//

#ifndef PROCY_MAPEDITOR_H
#define PROCY_MAPEDITOR_H


#include <TGUI/Gui.hpp>
#include "../../Engine/StateMachine.h"

///me = Map Editor Functions
class mef {
public:

    static void setTileClickInfo(sf::Vector2f &Mouse_pointer, Settings &json);

    static void setSpecialTile(unsigned int &bitValue, sf::Vector2f &Mouse_pointer, Settings &json);

    static void removeSpecialTile(sf::Vector2f &Mouse_pointer, Settings &json, std::string type);

    static std::vector<sf::Vector2i> getAllSelectedTileType(Settings &json, std::string &type);

    static std::vector<int> getTileDirection(sf::Vector2i position, Settings &json, std::string &type);

    static std::vector<int> getTileWeights(sf::Vector2i position, Settings &json, std::string &type);

    static std::vector<int> getTeleportTilesPositions(sf::Vector2i position, Settings &json, std::string &type);

    static std::vector<int> getAllSpecialTileInfo(sf::Vector2i position, Settings &json, std::string &type);

    static std::vector<bool> getPlayersSelected(sf::Vector2i position, Settings &json, std::string &type, bool teams);

    static void setTileDirection(int direction, Settings &json);

    static void setTileWeights(int direction, int value, Settings &json);

    static void setTileTeleportNext(tgui::Gui &gui, Settings &json);

    static void setTileValueSpecified(int value, int position, Settings &json);

    static void setTileValuePlayers(tgui::Gui &gui, Settings &json);

    ///setValue...; are giving start values when a special tile placed
    static void setValueDirection(Settings &json);

    static void setValueSpeed(Settings &json);

    static void setValueTeleport(Settings &json);

    static void setValueSpawn(Settings &json);

    static void setValueDestination(Settings &json);
    ///

};


#endif //PROCY_MAPEDITOR_H
