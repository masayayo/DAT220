//
// Created by Chrim14 on 16.11.2017.
//

#ifndef PROCY_NODES_H
#define PROCY_NODES_H

#include "Spawn.h"
#include "Divider.h"
#include "Teleport.h"

class Paths : Spawn, Divider, Teleport {
public:
    Paths() = default;
    void setPaths(Settings& json);
    std::vector<int> getPath(int bit_type, sf::Vector2i position);
};


#endif //PROCY_NODES_H
