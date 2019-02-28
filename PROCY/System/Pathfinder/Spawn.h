//
// Created by Chrim14 on 16.11.2017.
//

#ifndef PROCY_SPAWN_H
#define PROCY_SPAWN_H


#include <array>
#include <SFML/Graphics.hpp>
#include "../../Engine/Settings.h"
#include "Direction.h"

struct Node_Spawn {
    sf::Vector2i coordinate;
    std::vector<int> direction{};
    std::vector<int> weights{};
    std::map<int,std::vector<int>> map;
};

class Spawn : Direction{
public:
    Spawn() = default;
    void setSpawnNodes(Settings &json);
    std::vector<int> getDirectionSpawn(sf::Vector2i position);

private:
    std::vector<Node_Spawn> spawns;
};


#endif //PROCY_SPAWN_H
