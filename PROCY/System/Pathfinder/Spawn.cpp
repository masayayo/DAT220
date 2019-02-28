//
// Created by Admin on 16.11.2017.
//

#include "Spawn.h"
#include "../MapEditor/MapEditorStaticFunctions.h"

void Spawn::setSpawnNodes(Settings &json) {
    std::string type = "spawn";
std::vector<sf::Vector2i> position_vector = mef::getAllSelectedTileType(json,type);

    for(const auto& temp : position_vector) {
        Node_Spawn node_spawn;
        node_spawn.coordinate = sf::Vector2i(temp.x, temp.y);
        node_spawn.direction = mef::getTileDirection(node_spawn.coordinate, json, type);
        node_spawn.weights = mef::getTileWeights(node_spawn.coordinate, json, type);
        // std::cout << "Spawn: [" << node_spawn.coordinate.x << ", " << node_spawn.coordinate.y << "]" << std::endl;
        if (node_spawn.direction.size() == 4) {
            for (int i = 0; i < 4; ++i) {
                if (node_spawn.direction[i] == 1) {
                    node_spawn.map[i] = setDirection(i, node_spawn.coordinate, json);
                } else{
                    node_spawn.map[i] = std::vector<int>();
                }
            }
            spawns.push_back(node_spawn);
        }
    }
}

std::vector<int> Spawn::getDirectionSpawn(sf::Vector2i position) {

    for (const auto& temp : spawns) {
        if(temp.coordinate.x == position.x && temp.coordinate.y == position.y){
            int v = giveDirection(temp.direction,temp.weights);
            return temp.map.at(v);
        }
    }
    return std::vector<int>();
}
