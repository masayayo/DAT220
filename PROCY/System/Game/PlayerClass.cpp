//
// Created by Masaya on 11/9/2017.
//

#include "PlayerClass.h"

#include <utility>

//
// Created by Masaya on 12/9/2017.
//

void PlayerClass::setPlayerSprite(sf::Texture &texture){
    playerSprite.setTexture(texture);
    spriteRect = sf::IntRect(0,0,playerSprite.getTexture()->getSize().x/4,playerSprite.getTexture()->getSize().y/4);
    playerSprite.setTextureRect(spriteRect);
    playerSprite.setOrigin(spriteRect.width/2,spriteRect.height/2);
}
void PlayerClass::setSpeed(float value){
    speed = value;
}
void PlayerClass::setMaxHealth(int amount){
    maxHealth = amount;
}
void PlayerClass::setMaxMana(int amount){
    maxMana = amount;
}
void PlayerClass::setDamage(int amount){
    damage = amount;
}
void PlayerClass::setClassName(std::string name){
    className = std::move(name);
}
std::string PlayerClass::getClassName(){
    return className;
}
sf::Sprite PlayerClass::getPlayerSprite(){
    return playerSprite;
}

float PlayerClass::getSpeed(){
    return speed;
}

int PlayerClass::getMaxHealth(){
    return maxHealth;
}
int PlayerClass::getMaxMana(){
    return maxMana;
}
int PlayerClass::getDamage(){
    return damage;
}

void PlayerClass::setStartGold(int amount){
    startGold = amount;
}

int PlayerClass::getStartGold(){
    return startGold;
}