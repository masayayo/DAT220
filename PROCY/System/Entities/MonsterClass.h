//
// Created by Masaya on 12/9/2017.
//

#ifndef PROCY_MONSTERCLASS_H
#define PROCY_MONSTERCLASS_H

#include <SFML/Graphics.hpp>

class MonsterClass{
public:
    void setMonsterSprite(sf::Texture &texture);
    void setSpeed(float value);
    void setMaxHealth(int amount);
    void setDamage(int amount);
    void setValue(int amount);
    void setClassName(std::string name);
    sf::Sprite getMonsterSprite();
    float getSpeed();
    int getMaxHealth();
    int getDamage();
    int getValue();
    std::string getClassName();

private:
    sf::Sprite monsterSprite;
    sf::IntRect spriteRect;
    float speed;
    int maxHealth;
    int damage;
    int value;
    std::string className;
};



#endif //PROCY_MONSTERCLASS_H
