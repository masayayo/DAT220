//
// Created by Admin on 17.11.2017.
//

#include <vector>
#include <SFML/Audio.hpp>
#include <map>
#include "../../Engine/Settings.h"
#include "Direction.h"

#ifndef PROCY_DIVIDER_H
#define PROCY_DIVIDER_H

struct Node_Divider {
    sf::Vector2i coordinate;
    std::vector<int> direction{};
    std::vector<int> weights{};
    std::map<int,std::vector<int>> map;
};

class Divider : Direction {
public:
    Divider() = default;
    void setDividerNodes(Settings &json);
    std::vector<int> getDirectionDivider(sf::Vector2i position);

private:
    std::vector<Node_Divider> dividers;
};

#endif //PROCY_DIVIDER_H
