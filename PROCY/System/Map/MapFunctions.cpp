//
// Created by Chrim14 on 01.11.2017.
//

#include "MapFunctions.h"
#include "MapStaticFunctions.h"
#include "../MapEditor/MapEditorStaticFunctions.h"


/** A Class Function that replaces selected tiles with a new tile.
 * @param mapTiles A VertaxArray that stores the information about all the tiles
 * @param xPos the mouse X-coordinates
 * @param yPos the mouse Y-coordinates
 * @param tileSelected The tile number that will replace selected tile
 * @param json Information about the map
 * @param window
 * @param tileTexture texture in use
 */
void MapFunctions::drawSelectedTileToPosition(sf::VertexArray &mapTiles, float &xPos, float &yPos, unsigned int tileSelected, Settings &json, sf::RenderWindow &window) {

    sf::Vector2f pointer = sf::Vector2f(xPos,yPos);
    if(!mf::isMousePointerInsideMap(pointer,json) || tileSelected == 0) return;

    sf::Vector2i tileStart, tileSize, position;

    int rotation = json.editor["rotate"];

    getTileCoordinates(tileSelected, tileStart, tileSize, json);
    unsigned int bitTileValue = mf::getBitValueFromType(tileSelected, json);
    rotateTile(tileSelected,tileStart,tileSize,rotation);

    position = mf::getMapTilesCoordinates(pointer,json);

    //A mathematical formula for finding tile position
    int v = ((position.y * mf::getMapSize(json).x + position.x) * 4);

    if(rotation % 2 == 0) {
        mapTiles[v].texCoords = sf::Vector2f(tileStart.x, tileStart.y);
        mapTiles[v + 1].texCoords = sf::Vector2f(tileStart.x + tileSize.x, tileStart.y);
        mapTiles[v + 2].texCoords = sf::Vector2f(tileStart.x + tileSize.x, tileStart.y + tileSize.y);
        mapTiles[v + 3].texCoords = sf::Vector2f(tileStart.x, tileStart.y + tileSize.y);
    }
    else {
        mapTiles[v].texCoords = sf::Vector2f(tileStart.x, tileStart.y);
        mapTiles[v + 1].texCoords = sf::Vector2f(tileStart.x, tileStart.y + tileSize.y);
        mapTiles[v + 2].texCoords = sf::Vector2f(tileStart.x + tileSize.x, tileStart.y + tileSize.y);
        mapTiles[v + 3].texCoords = sf::Vector2f(tileStart.x + tileSize.x, tileStart.y);
    }

    //Adding tile value in the right position in layer 1 for easy saving

    json.tileValue[position.x][position.y] = tileSelected;

    mef::setTileClickInfo(pointer,json);
    mef::setSpecialTile(bitTileValue, pointer,json);

    for (int i = 0; i < Bits_To_Tiles; ++i) {
        for (int j = 0; j < Bits_To_Tiles; ++j) {
            json.bitTileValue[position.x*Bits_To_Tiles+j][position.y*Bits_To_Tiles+i] = bitTileValue;
        }
    }
}


///From: Map::clickEvent
///Function: get information about tile position and tile type
void MapFunctions::getMouseTilePositionInformation(sf::Vector2f &tilePosition, Settings &json, tgui::Gui &gui) {
    tgui::Label::Ptr label = gui.get<tgui::Label>("positionText");
    if (label != nullptr) {

        if (!mf::isMousePointerInsideMap(tilePosition,json)) {
            label->setText("");
            return;
        }

        sf::Vector2i temp = mf::getBitCoordinates(tilePosition,json);

        unsigned int bit_value = json.bitTileValue[temp.x][temp.y];
        std::string bit_name = mf::getBitNameFromValue(bit_value);

        temp = mf::getMapTilesCoordinates(tilePosition,json);

        std::string x_String = std::to_string(temp.x);
        std::string y_String = std::to_string(temp.y);

        label->setText(x_String + ", " + y_String + " [" + bit_name + "]");
    }
}


///From: Map::clickEvent
///Function: draw tile to layer 2
void MapFunctions::drawToBitLayer(Player &player,std::vector<Tower> &towersPlaced,sf::VertexArray &bitTiles, sf::Vector2f &mapPosition, unsigned int towerWidth, unsigned int towerHeight, std::string &towerSelected, Settings &json, sf::RenderWindow &window) {

    // Get the tower to draw
    Tower tower;
    tower.tex = json.towerSprites[towerSelected].tex;
    tower.w = json.towerSprites[towerSelected].w;
    tower.h = json.towerSprites[towerSelected].h;
    tower.fireRate = json.towerSprites[towerSelected].fireRate;
    tower.range = json.towerSprites[towerSelected].range;
    tower.bulletType = json.towerSprites[towerSelected].bulletType;
    tower.towerType = json.towerSprites[towerSelected].towerType;
    tower.buildingCost = json.towerSprites[towerSelected].buildingCost;
    tower.damage = json.towerSprites[towerSelected].damage;
    tower.towerName = json.towerSprites[towerSelected].towerName;
    tower.soundName = json.towerSprites[towerSelected].soundName;
    tower.towerDescription = json.towerSprites[towerSelected].towerDescription;
    tower.health = json.towerSprites[towerSelected].health;
    tower.maxHealth = json.towerSprites[towerSelected].maxHealth;

    sf::CircleShape towerRadius = sf::CircleShape(tower.range,255);
    towerRadius.setOutlineColor(sf::Color::Yellow);
    towerRadius.setOutlineThickness(1.2f);
    towerRadius.setFillColor(sf::Color(255,255,0,70));
    tower.towerRadius = towerRadius;

    int x =  (int) mapPosition.x / (Tile_Size / Bits_To_Tiles);
    int y =  (int) mapPosition.y / (Tile_Size / Bits_To_Tiles);
    int width = json.map["width"];
    int height = json.map["height"];

    float sizeX = tower.w * (Tile_Size/Bits_To_Tiles);
    float sizeY = tower.h * (Tile_Size/Bits_To_Tiles);

    //Control if inside map, (check under 0 is not needed, because of unsigned tile_size)
    if(towerSelected.empty()|| x +(tower.w - 1) >= (width * Bits_To_Tiles) || y + (tower.h - 1) >= (height * Bits_To_Tiles)) return;

    int tempY = y;

    //Controls if there is another tower there
    for (int i = 0; i < tower.h; ++i) {
        int tempX = x;
        for (int j = 0; j < tower.w; ++j) {
            if(json.bitTileValue[tempX][tempY] != 0){
                return;
            }
            tempX++;
        }
        tempY++;
    }

    tempY = y;
    for (int i = 0; i < tower.h; ++i) {

        int tempX = x;

        for (int j = 0; j < tower.w; ++j) {
            json.bitTileValue[tempX][tempY] = 2;
            mf::drawBitHighlightSpecifiedTile(bitTiles,sf::Vector2i(tempX,tempY),json);
            tempX++;
            }
        tempY++;
        }

        sf::VertexArray coordinates(sf::Quads,4);
        sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
        sf::Vector2f gamePosition = window.mapPixelToCoords(pixelPosition);
        sf::Vector2f bitPixelStartCoordinates = mf::getBitPixelStartCoordinates(gamePosition,json);

        sf::Vector2f position = bitPixelStartCoordinates;

        coordinates[0].position = position;
        coordinates[1].position = sf::Vector2f(position.x+sizeX, position.y);
        coordinates[2].position = sf::Vector2f(position.x+sizeX, position.y+sizeY);
        coordinates[3].position = sf::Vector2f(position.x, position.y+sizeY);

        coordinates[0].texCoords     = sf::Vector2f(bitPixelStartCoordinates.x,bitPixelStartCoordinates.y);
        coordinates[1].texCoords = sf::Vector2f(bitPixelStartCoordinates.x+sizeX,bitPixelStartCoordinates.y);
        coordinates[2].texCoords = sf::Vector2f(bitPixelStartCoordinates.x+sizeX,bitPixelStartCoordinates.y+sizeY);
        coordinates[3].texCoords = sf::Vector2f(bitPixelStartCoordinates.x,bitPixelStartCoordinates.y+sizeY);

        //tower.tex.setScale(0.4f,0.4f);
        tower.coordinates = coordinates;

        tower.tex.scale(sizeX/tower.tex.getTexture()->getSize().x,sizeY/tower.tex.getTexture()->getSize().y);
        tower.tex.setOrigin(tower.tex.getTexture()->getSize().x/2 ,tower.tex.getTexture()->getSize().y/2);

        tower.tex.setPosition(bitPixelStartCoordinates.x+sizeX/2,bitPixelStartCoordinates.y+sizeY/2);
        tower.towerTimer.Reset();
        tower.bulletType = json.towerSprites[towerSelected].bulletType;
        tower.towerType = json.towerSprites[towerSelected].towerType;
        tower.towerRadius.setPosition(tower.tex.getPosition().x - tower.range,tower.tex.getPosition().y - tower.range);

        player.addToBuildingQueue(tower);

        player.useGold(tower.buildingCost);
}

/** A function that mathematically calculate the tile position.
 * @param tileNumber The tile number that is choosen
 * @param xStart The tile start position in x-direction
 * @param yStart The tile start position in y-direction
 * @param tileSize The size in length and width of the tile
 * @param tileTexture a string that refere to the tile texture
 */
void MapFunctions::getTileCoordinates(unsigned int tileNumber, sf::Vector2i &tileStart, sf::Vector2i &tileSize, Settings &json) {


    if(json.TextureInUse == "tiles.png"){

        int rotation = mf::getTileRotationValue(tileNumber);
        tileNumber -= 1;
        int tile = mf::getTileIdValue(tileNumber);

        //32 is the number of pixel each tile has in this texture
        tileSize = sf::Vector2i(32,32);

        //23 + 1 is the first tile in next line.
        tileStart.y = (tile / 23) * tileSize.x;

        tileStart.x = (tile - (23*(tileStart.y/tileSize.x))) * tileSize.x;

        mf::setTileRotationCoordinates(tileStart, tileSize, rotation);
    } else {
        lFatal("Did not find right tile map");
    }
}

///From:  Map::getMap, Map::drawSelectedTileToPosition
///Function: change texture start position if rotation value > 0
void MapFunctions::rotateTile(unsigned int &tileSelected, sf::Vector2i &start, sf::Vector2i &Tile_size, int rotation) {

    mf::setTileRotationCoordinates(start,Tile_size,rotation);
    mf::setTileRotationValue(tileSelected,rotation);
}


