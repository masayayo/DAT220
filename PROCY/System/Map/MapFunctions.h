//
// Created by Chrim14 on 01.11.2017.
//

#ifndef PROCY_MAPFUNCTIONS_H
#define PROCY_MAPFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "../../Engine/StateMachine.h"
#include "../Game/Player.h"

class MapFunctions {
public:
    void drawSelectedTileToPosition(sf::VertexArray &mapTiles, float &xPos, float &yPos, unsigned int tileSelected, Settings &json, sf::RenderWindow &window);

    void getMouseTilePositionInformation(sf::Vector2f &tilePosition, Settings &json, tgui::Gui &gui);

    void drawToBitLayer(Player &player,std::vector<Tower> &towersPlaced,sf::VertexArray &bitTiles, sf::Vector2f &mapPosition, unsigned int towerWidth, unsigned int towerHeight, std::string &towerSelected, Settings &json, sf::RenderWindow &window);

    void getTileCoordinates(unsigned int tileNumber, sf::Vector2i &tileStart, sf::Vector2i &tileSize, Settings &json);

    void rotateTile(unsigned int &tileSelected, sf::Vector2i &start, sf::Vector2i &Tile_size, int rotation);
};




#endif //PROCY_MAPFUNCTIONS_H
