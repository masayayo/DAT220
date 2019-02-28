//
// Created by Masaya on 11/4/2017.
//

#ifndef PROCY_TOWER_H
#define PROCY_TOWER_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Bullet.h"
#include "Timer.h"

class Monster;

struct Tower{
    Tower() = default;

    sf::Sprite tex;
    sf::CircleShape towerRadius;
    std::string towerName = "Tower";
    std::string soundName;
    std::string towerDescription;
    Monster *enemyTarget = nullptr;
    unsigned int w;
    unsigned int h;
    std::vector<Bullet> bullets;
    Timer towerTimer;
    std::string bulletType;
    std::string towerType;
    float fireRate;
    float range;
    sf::VertexArray coordinates;
    bool isSelected = false;
    bool isBuilt = false;
    float buildTime = 2.0f;
    int buildingCost;
    int damage;
    int health;
    int maxHealth;
};

#endif //PROCY_TOWER_H
