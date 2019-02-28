//
// Created by Chrim14 on 17.11.2017.
//

#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include "Direction.h"

#ifndef PROCY_TELEPORT_H
#define PROCY_TELEPORT_H

struct Node_Teleport {
    sf::Vector2i coordinate_from;
    std::vector<int> direction{};
    std::vector<int> weights{};
    std::map<int,std::vector<int>> map;
    sf::Vector2i coordinate_to;
    int time;
};


class Teleport : Direction {
public:
    Teleport() = default;
    void setTeleportNodes(Settings &json);
    std::vector<int> getDirectionTeleport(sf::Vector2i position);
    std::vector<int> getTeleportPosition(sf::Vector2i position);

private:
    std::vector<Node_Teleport> teleport;
};


#endif //PROCY_TELEPORT_H
