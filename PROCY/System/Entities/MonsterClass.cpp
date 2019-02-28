//
// Created by Masaya on 12/9/2017.
//

#include "MonsterClass.h"

#include <utility>

void MonsterClass::setMonsterSprite(sf::Texture &texture){
    monsterSprite.setTexture(texture);
    spriteRect = sf::IntRect(0,0,texture.getSize().x/4,texture.getSize().y/4);
    monsterSprite.setTextureRect(spriteRect);
    monsterSprite.setOrigin(spriteRect.width/2,spriteRect.height/2);
}
void MonsterClass::setSpeed(float value){
    speed = value;
}
void MonsterClass::setMaxHealth(int amount){
    maxHealth = amount;
}
void MonsterClass::setDamage(int amount){
    damage = amount;
}
void MonsterClass::setClassName(std::string name){
    className = std::move(name);
}

sf::Sprite MonsterClass::getMonsterSprite(){
    return monsterSprite;
}

float MonsterClass::getSpeed(){
    return speed;
}

int MonsterClass::getMaxHealth(){
    return maxHealth;
}

int MonsterClass::getDamage(){
    return damage;
}


void MonsterClass::setValue(int amount) {
    value = amount;
}

int MonsterClass::getValue() {
    return value;
}

std::string MonsterClass::getClassName(){
    return className;
}
