//
// Created by Masaya on 11/9/2017.
//

#ifndef PROCY_PLAYERCLASS_H
#define PROCY_PLAYERCLASS_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../../GUI/Sound/Sound.h"

class PlayerClass {
public:
    void setPlayerSprite(sf::Texture &texture);
    void setSpeed(float value);
    void setMaxHealth(int amount);
    void setMaxMana(int amount);
    void setDamage(int amount);
    void setClassName(std::string name);
    std::string getClassName();
    sf::Sprite getPlayerSprite();
    float getSpeed();
    int getMaxHealth();
    int getMaxMana();
    int getDamage();
    void setStartGold(int amount);
    int getStartGold();
private:
    sf::Sprite playerSprite;
    sf::IntRect spriteRect;
    std::string className;
    float speed;
    int maxHealth;
    int maxMana;
    int damage;
    int startGold;
};

#endif //PROCY_PLAYERCLASS_H
