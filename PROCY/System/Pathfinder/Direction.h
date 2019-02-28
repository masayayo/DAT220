//
// Created by Admin on 16.11.2017.
//

#ifndef PROCY_DIRECTION_H
#define PROCY_DIRECTION_H


#include "../../Engine/Settings.h"

class Direction {
public:
    Direction() = default;
    std::vector<int> setDirection(int direction, sf::Vector2i position, Settings &json);
    int giveDirection(std::vector<int> directions, std::vector<int> weighs);
};


#endif //PROCY_DIRECTION_H
