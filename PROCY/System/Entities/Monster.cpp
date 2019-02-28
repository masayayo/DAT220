#include <cstdint>
#include <stdint-gcc.h>
#include "Monster.h"

void Monster::addHealth(int amount){
    health += amount;
}
int Monster::getHealth(){
    return health;
}

void Monster::setHealthBar(sf::Texture &texture){
    healthBar.setTexture(&texture,false);
    healthBar.setSize(sf::Vector2f(sprite.getLocalBounds().width,sprite.getLocalBounds().width/10));
    healthBar.setScale(1,1);
}

sf::RectangleShape Monster::getHealthBar(){
    return healthBar;
}

sf::Sprite Monster::getSprite() {
    return this->sprite;
}

Monster::Monster(sf::Vector2i spawn, Settings &json, Paths& paths, MonsterClass &monsterType){
    this->spawn = spawn;
    //sprite = sf::RectangleShape(sf::Vector2f(20, 20));

    float sizeX = 3 * (Tile_Size/Bits_To_Tiles);
    float sizeY = 3 * (Tile_Size/Bits_To_Tiles);


    sprite = monsterType.getMonsterSprite();
    spriteRect = monsterType.getMonsterSprite().getTextureRect();
    this->monsterType = monsterType;
    speed = monsterType.getSpeed();
    value = monsterType.getValue();
    maxHealth = monsterType.getMaxHealth();
    health = maxHealth;
    damage = monsterType.getDamage();

    visible = true;
    //setPosition takes spawn position x and y calculate monster size to center
    sprite.setPosition(spawn.x*Tile_Size+((Tile_Size/2.0f)), spawn.y*Tile_Size+((Tile_Size/2.0f)));
    healthBar.setPosition(currentPosition.x-(healthBar.getSize().x/2),currentPosition.y-(sprite.getLocalBounds().height/2));
    direction_left = INT8_MIN; //Just a number that never will occure by its own
    direction = paths.getPath(3,sf::Vector2i(spawn.x,spawn.y));
    teleport_time = 0;
}

void Monster::tick(Player &player,Timer &gameTimer,sf::Shader &shader,sf::RenderWindow &window, Paths& paths){

    //IF monster visible and not teleporting to another position
    if (visible && teleport_time <= 0) {
        sf::Vector2f move = sf::Vector2f(0, 0);

        if (direction.size() > 3) {
            //IF there still some distance left to move
            if (direction_left > 0) {
                if (direction.back() == 0) {
                    move = sf::Vector2f(0, -speed);
                    spriteRect.top = (sprite.getTexture()->getSize().y/4)*3;
                } else if (direction.back() == 1) {
                    move = sf::Vector2f(speed, 0);
                    spriteRect.top = (sprite.getTexture()->getSize().y/4)*2;
                } else if (direction.back() == 2) {
                    move = sf::Vector2f(0, speed);
                    spriteRect.top = 0;
                } else if (direction.back() == 3) {
                    move = sf::Vector2f(-speed, 0);
                    spriteRect.top = (sprite.getTexture()->getSize().y/4);
                }
                // Increment the spriteRect with spriteWidth/4, zero if at last image position

                if(textureUpdateTimer >= 3) {
                    if (spriteRect.left != (sprite.getTexture()->getSize().x / 4) * 3) {
                        spriteRect.left += spriteRect.width;
                    } else {
                        spriteRect.left = 0;
                    }
                    sprite.setTextureRect(spriteRect);
                    textureUpdateTimer = 0;
                }
                direction_left -= speed;
                textureUpdateTimer += speed;
            }
            //ELSE find new distance and direction to move
            else {
                if (direction_left != INT8_MIN) {   //IF this is first move not remove front
                    direction.pop_back();
                    direction.pop_back();
                }
                if (direction_left == INT8_MIN) {   //IF this is first move add extra value to direction left
                    direction_left = direction[direction.size() - 2] * Tile_Size + Tile_Size;
                }
                direction_left = direction[direction.size() - 2] * Tile_Size;
            }
        }
        if(direction.size() == 3) {
            //Getting new direction from getPath
            direction = paths.getPath(direction.front(), sf::Vector2i(direction[1], direction[2]));

            //IF direction element is 10, do some advance stuff
            if(!direction.empty() && direction.front() == 10){

                // teleport_time = direction.back();
                teleport_time = 0;

                sprite.setPosition(direction.at(direction.size()-3)*Tile_Size+((Tile_Size/2.0f)),
                                   direction.at(direction.size()-2)*Tile_Size+((Tile_Size/2.0f)));
                direction = paths.getPath(10, sf::Vector2i(direction.at(direction.size()-3), direction.at(direction.size()-2)));
            }
            direction_left = INT8_MIN;
        }

        sprite.move(move);
        currentPosition = sprite.getPosition();
        healthBar.setPosition(currentPosition.x-(healthBar.getSize().x/2),currentPosition.y-(sprite.getLocalBounds().height/2));
    }
}

bool Monster::isPointerOverMonster(sf::Vector2f gamePosition, sf::Sprite &monsterSprite){
    return	(gamePosition.x < (monsterSprite.getPosition().x - (monsterSprite.getOrigin().x*monsterSprite.getScale().x))  + ((monsterSprite.getLocalBounds().width)*monsterSprite.getScale().x)) && ((monsterSprite.getPosition().x - (monsterSprite.getOrigin().x*monsterSprite.getScale().x)) < gamePosition.x) &&
              (gamePosition.y < (monsterSprite.getPosition().y - (monsterSprite.getOrigin().y*monsterSprite.getScale().y)) + ((monsterSprite.getLocalBounds().height)*monsterSprite.getScale().y)) && ((monsterSprite.getPosition().y - (monsterSprite.getOrigin().y*monsterSprite.getScale().y)) < gamePosition.y);
}


void Monster::hit(Player &player,int damage, std::list<Monster> &monster_active, int unique_id){

    health -= damage;

    if(health <= 0){
        player.addToGold(value);
        removeMonster(monster_active,unique_id);
    }
    else{
        healthBar.setScale((float)1*((float)health/(float)maxHealth),1);
    }
}

void Monster::removeMonster(std::list<Monster> &monster_active, int unique_id) {

    for (auto it = monster_active.begin(); it != monster_active.end(); it++) {
        if (it->unique_id == unique_id) {
            monster_active.erase(it);
            break;
        }
    }
}
