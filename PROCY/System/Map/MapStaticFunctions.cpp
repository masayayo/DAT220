//
// Created by Chrim14 on 03.11.2017.
//

#include "MapStaticFunctions.h"


sf::Vector2i mf::getBitCoordinates(sf::Vector2f &Mouse_Position, Settings &json) {

    sf::Vector2i temp;

    if (mf::isMousePointerInsideMap(Mouse_Position, json)) {

        temp.x = (unsigned int) Mouse_Position.x / (Tile_Size / Bits_To_Tiles);
        temp.y = (unsigned int) Mouse_Position.y / (Tile_Size / Bits_To_Tiles);

        return temp;
    }
}

sf::Vector2f mf::getBitPixelStartCoordinates(sf::Vector2f &tilePosition, Settings &json) {

    sf::Vector2i temp = mf::getBitCoordinates(tilePosition, json);

    return sf::Vector2f((float)temp.x*(Tile_Size/Bits_To_Tiles),(float)temp.y*(Tile_Size/Bits_To_Tiles));
}


sf::Vector2i mf::getMapTilesCoordinates(sf::Vector2f &Mouse_Position, Settings &json) {

    return sf::Vector2i((int) Mouse_Position.x / Tile_Size, (int) Mouse_Position.y / Tile_Size);
}

sf::Vector2i mf::getMapSize(Settings &json) {

    return sf::Vector2i(json.map["width"], json.map["height"]);
}

bool mf::isMousePointerInsideMap(sf::Vector2f &tilePosition,Settings &json) {

    return (tilePosition.x <= getMapSize(json).x * Tile_Size) && (tilePosition.y <= getMapSize(json).y * Tile_Size) &&
            tilePosition.x >= 0 && tilePosition.y >= 0;
}


///Function: Transform tile to bit value
///Warning: bit value change mf::getBitValueFromType, mf::getBitNameFromValue, mef::setSpecialTile
unsigned int mf::getBitValueFromType(unsigned int tileNumber, Settings &json) {

    if(json.editor["tileType"] == "ground"){
        tileNumber = 0;
    }
    else if(json.editor["tileType"] == "road"){
        tileNumber = 1;
    }
    else if(json.editor["tileType"] == "decorate"){
        tileNumber = 8;
    }
    else if(json.editor["tileType"] == "spawn"){
        tileNumber = 3;
    }
    else if(json.editor["tileType"] == "destination"){
        tileNumber = 4;
    }
    else if(json.editor["tileType"] == "teleport"){
        tileNumber = 5;
    }
    else if(json.editor["tileType"] == "divider"){
        tileNumber = 6;
    }
    else if(json.editor["tileType"] == "speed"){
        tileNumber = 7;
    }
    else{
        lError("Did not get bit value");
        tileNumber = 0;
    }
    return tileNumber;
}

///Function: Getting in bit value, giving back tile type
///Warning: bit value change mf::getBitValueFromType, mf::getBitNameFromValue, mef::setSpecialTile
std::string mf::getBitNameFromValue(unsigned int tileNumber) {

    std::string temp;
    if(tileNumber == 0){
        temp = "ground";
    }
    else if(tileNumber == 1){
        temp = "road";
    }
    else if(tileNumber == 8){
        temp = "decorate";
    }
    else if(tileNumber == 2){
        temp = "tower";
    }
    else if(tileNumber == 3){
        temp = "spawn";
    }
    else if(tileNumber == 4){
        temp = "destination";
    }
    else if(tileNumber == 5){
        temp = "teleport";
    }
    else if(tileNumber == 6){
        temp = "divider";
    }
    else if(tileNumber == 7){
        temp = "speed";
    }
    else{
        lError("Did not get bit name");
    }
    return temp;
}

unsigned int mf::getBitTileFocusedValue(sf::Vector2f &tilePosition, Settings &json) {

    sf::Vector2i temp = mf::getBitCoordinates(tilePosition,json);

    if(temp.x >= 0 && temp.y >= 0 && temp.x < Layer_Two_Size && temp.y < Layer_Two_Size)
        return json.bitTileValue[temp.x][temp.y];

    return Layer_Two_Size;
}

int mf::getTileRotationValue(unsigned int tile) {
    if(((tile >> 31) & 1) && ((tile >> 30) & 1)) return 2;
    else if(((tile >> 31) & 1) && !((tile >> 30) & 1)) return 1;
    else if(!((tile >> 31) & 1) && ((tile >> 30) & 1)) return 3;
    return 0;
}

int mf::getTileIdValue(unsigned int tileId) {
    tileId &= ~(1u << 31);
    tileId &= ~(1u << 30);
    return tileId;
}

unsigned int mf::getTileValue(sf::Vector2i &coordinates, Settings &json) {

    return json.tileValue[coordinates.x][coordinates.y];
}

void mf::setTileRotationCoordinates(sf::Vector2i &tileStart, sf::Vector2i &tileSize, int rotation) {

    if(rotation == 1){
        tileStart.y += tileSize.y;
        tileSize.y = -tileSize.y;
    }
    else if(rotation == 2){

        tileStart.y += tileSize.y;
        tileSize.y = -tileSize.y;

        tileStart.x += tileSize.x;
        tileSize.x = -tileSize.x;
    }
    else if(rotation == 3){

        tileStart.x += tileSize.x;
        tileSize.x = -tileSize.x;
    }
}

void mf::setTileRotationValue(unsigned int &Tile_Selected, int &Rotation_Value) {
    switch(Rotation_Value){
        case 1:
            Tile_Selected |= 1 << 31;
            break;
        case 2:
            Tile_Selected |= 1 << 31;
            Tile_Selected |= 1 << 30;
            break;
        case 3:
            Tile_Selected |= 1 << 30;
            break;
        default:
            break;
    }
}

void mf::setBitMapHighlightPanel(sf::VertexArray &Bit_Layer, Settings &json) {


    sf::Vector2i size = mf::getMapSize(json);

    int counter = 0;
    int tempY = 0;
    //Did not find tower, draws tower at position
    for (int i = 0; i < size.y*Bits_To_Tiles; ++i) {
        int tempX = 0;
        for (int j = 0; j < size.x*Bits_To_Tiles; ++j) {

            Bit_Layer[counter+0].position = sf::Vector2f(tempX * (Tile_Size / Bits_To_Tiles), tempY * (Tile_Size / Bits_To_Tiles));
            Bit_Layer[counter+1].position = sf::Vector2f(tempX * (Tile_Size / Bits_To_Tiles) + (Tile_Size/Bits_To_Tiles), (tempY * (Tile_Size / Bits_To_Tiles)));
            Bit_Layer[counter+2].position = sf::Vector2f(tempX * (Tile_Size / Bits_To_Tiles) + (Tile_Size/Bits_To_Tiles), tempY * (Tile_Size / Bits_To_Tiles) + (Tile_Size/Bits_To_Tiles));
            Bit_Layer[counter+3].position = sf::Vector2f(tempX * (Tile_Size / Bits_To_Tiles), tempY * (Tile_Size / Bits_To_Tiles) + (Tile_Size/Bits_To_Tiles));

            mf::drawBitHighlightSpecifiedTile(Bit_Layer,sf::Vector2i(tempX,tempY),json);

            counter += 4;
            tempX++;
        }
        tempY++;
    }
}

void mf::drawBitHighlightSpecifiedTile(sf::VertexArray &Bit_Layer, sf::Vector2i position, Settings &json) {

    sf::Color color;
   // sf::Color second;

    if (json.bitTileValue[position.x][position.y] == 0) {
        color = sf::Color(0,255,0, 0);
      //  second = sf::Color(35, 155, 86, 200);
    } else {
        color = sf::Color(255, 0, 0, 130);
       // second = sf::Color(176, 58, 46, 200);
    }

    int v = (((position.y * (mf::getMapSize(json).x * Bits_To_Tiles)) + position.x) * 4);

    Bit_Layer[v + 0].color = color;
    Bit_Layer[v + 1].color = color;
    Bit_Layer[v + 2].color = color;
    Bit_Layer[v + 3].color = color;

}

