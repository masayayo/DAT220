//
// Created by Chrim14 on 17.11.2017.
//

#include "Teleport.h"
#include "../MapEditor/MapEditorStaticFunctions.h"

void Teleport::setTeleportNodes(Settings &json) {
    std::string type = "teleport";
    std::vector<sf::Vector2i> position_vector = mef::getAllSelectedTileType(json,type);

    for(const auto& temp : position_vector) {
        Node_Teleport node_Teleport;
        node_Teleport.coordinate_from = sf::Vector2i(temp.x, temp.y);
        node_Teleport.direction = mef::getTileDirection(node_Teleport.coordinate_from, json, type);
        node_Teleport.weights = mef::getTileWeights(node_Teleport.coordinate_from, json, type);
        std::vector<int> vector = mef::getAllSpecialTileInfo(node_Teleport.coordinate_from, json, type);
        node_Teleport.time = vector.back();
        node_Teleport.coordinate_to = sf::Vector2i(vector[vector.size() - 3], vector[vector.size() - 2]);
        if (node_Teleport.direction.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                if (node_Teleport.direction[i] == 1) {
                    node_Teleport.map[i] = setDirection(i, node_Teleport.coordinate_from, json);
                } else
                    node_Teleport.map[i] = std::vector<int>();
            }
            teleport.push_back(node_Teleport);
        }
    }
}

std::vector<int> Teleport::getDirectionTeleport(sf::Vector2i position) {

    for (const auto& temp : teleport) {
        if(temp.coordinate_from.x == position.x && temp.coordinate_from.y == position.y){
            int v = giveDirection(temp.direction,temp.weights);
            return temp.map.at(v);
        }
    }
    return std::vector<int>();
}

std::vector<int> Teleport::getTeleportPosition(sf::Vector2i position) {

    for (const auto& temp : teleport) {
        if(temp.coordinate_from.x == position.x && temp.coordinate_from.y == position.y) {
            std::vector<int> vector = {10, temp.coordinate_to.x, temp.coordinate_to.y, temp.time};
            return vector;
        }
    }
}
