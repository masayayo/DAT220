//
// Created by Admin on 17.11.2017.
//

#include "Divider.h"
#include "../MapEditor/MapEditorStaticFunctions.h"

void Divider::setDividerNodes(Settings &json) {
    std::string type = "divider";
    std::vector<sf::Vector2i> position_vector = mef::getAllSelectedTileType(json,type);
    for(const auto& temp : position_vector) {
        Node_Divider node_divider;
        node_divider.coordinate = sf::Vector2i(temp.x, temp.y);
        node_divider.direction = mef::getTileDirection(node_divider.coordinate, json, type);
        node_divider.weights = mef::getTileWeights(node_divider.coordinate, json, type);
        if (node_divider.direction.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                if (node_divider.direction[i] == 1) {
                    node_divider.map[i] = setDirection(i, node_divider.coordinate, json);
                } else
                    node_divider.map[i] = std::vector<int>();
            }
            dividers.push_back(node_divider);
        }
        else{
            std::stringstream message;
            message << "Tried to get divider tile at " << temp.x << " " << temp.y << ", but failed";
            lWarning(message.str());
        }
    }
}

std::vector<int> Divider::getDirectionDivider(sf::Vector2i position) {

    for (const auto& temp : dividers) {
        if(temp.coordinate.x == position.x && temp.coordinate.y == position.y){
            int v = giveDirection(temp.direction,temp.weights);
            return temp.map.at(v);
        }
    }
    return std::vector<int>();
}
