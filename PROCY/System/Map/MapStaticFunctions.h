//
// Created by Chrim14 on 03.11.2017.
//

#ifndef PROCY_MAPSTATICFUNCTIONS_H
#define PROCY_MAPSTATICFUNCTIONS_H

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include "../../Engine/Settings.h"

///mf = map functions
class mf {
public:

    static sf::Vector2i getMapSize(Settings &json);

    static bool isMousePointerInsideMap(sf::Vector2f &tilePosition,Settings &json);

    ///TILE
    static sf::Vector2i getMapTilesCoordinates(sf::Vector2f &tilePosition, Settings &json);

    static int getTileRotationValue(unsigned int tile);

    static void setTileRotationCoordinates(sf::Vector2i &tile_Start_Poistion, sf::Vector2i &Tile_Size, int Rotation_Value);

    static int getTileIdValue(unsigned int tileId);

    static void setTileRotationValue(unsigned int &Tile_Selected, int &Rotation_Value);

    static unsigned int getTileValue(sf::Vector2i &coordinates, Settings &json);

    ///BIT
    static unsigned int getBitValueFromType(unsigned int tileNumber, Settings &json);

    static std::string getBitNameFromValue(unsigned int tileNumber);

    static unsigned int getBitTileFocusedValue(sf::Vector2f &tilePosition, Settings &json);

    static sf::Vector2i getBitCoordinates(sf::Vector2f &tilePosition, Settings &json);

    static sf::Vector2f getBitPixelStartCoordinates(sf::Vector2f &tilePosition, Settings &json);

    static void setBitMapHighlightPanel(sf::VertexArray &Bit_Layer, Settings &json);

    static void drawBitHighlightSpecifiedTile(sf::VertexArray &Bit_Layer, sf::Vector2i position, Settings &json);
};


#endif //PROCY_MAPSTATICFUNCTIONS_H
