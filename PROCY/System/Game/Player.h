//
// Created by Masaya on 11/9/2017.
//

#ifndef PROCY_PLAYER_H
#define PROCY_PLAYER_H

#include "PlayerClass.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <queue>
#include "../../GUI/Sound/Sound.h"
#include "math.h"
#include "Tower.h"
#include "map"
#include "../../Engine/Settings.h"

class Player {
public:
    Player() = default;
    Player(PlayerClass &playerClass, Settings &json);
    void postDefinePlayer(PlayerClass &playerClass, Settings &json);
    sf::IntRect getIntRect();
    void setProgressBar(sf::Texture &texture);
    sf::RectangleShape getProgressBar();
    sf::Sprite getSprite();
    void spawnPlayer(float startX, float startY);
    void updatePlayer();
    void setPlayerTarget(float targetX, float targetY);
    sf::Vector2f getPlayerTarget();
    bool checkIsAlive();
    void setActive(bool active);
    void setPlayerClass(PlayerClass &someClass);
    PlayerClass getPlayerClass();
    void checkBuildingQueue(std::vector<Tower> &towersPlaced, float &frameTime);
    void addToBuildingQueue(Tower &tower);
    std::queue<Tower>& getBuildingQueue();
    void updateBuildTimer(float &frameTime);
    bool checkIsBusy();
    void setBusy(bool busy);
    int getGold();
    void addToGold(int amount);
    void useGold(int amount);
    void loseHealth(int amount);
    void addHealth(int amount);
    int getHealth();
    int getMaxHealth();
    bool checkIsSelected();
    void setSelected(bool value);
private:
    sf::RectangleShape progressBar;
    sf::IntRect rectSourceSprite;
    sf::Sprite playerSprite;
    sf::Vector2f playerPosition;
    sf::Vector2f targetPosition;
    //std::vector<Tower> buildingQueue;
    std::queue<Tower> buildingQueue;
    float currentBuildingTime = 0;
    Timer buildingTimer;
    int gold;
    int health;
    int maxHealth;
    int mana;
    float speed;
    int damage;
    float playerDistanceX;
    float playerDistanceY;
    bool isActive = false;
    bool isWalking;
    bool isBusy = false;
    bool targetReached = true;
    bool isSelected = false;
    PlayerClass playerClass;
};

#endif //PROCY_PLAYER_H
