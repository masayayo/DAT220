//
// Created by Masaya on 11/9/2017.
//

#include "Player.h"

Player::Player(PlayerClass &playerClass, Settings &json){
    playerSprite = playerClass.getPlayerSprite();
    rectSourceSprite = playerClass.getPlayerSprite().getTextureRect();
    this->playerClass = playerClass;
    speed = playerClass.getSpeed();
    health = playerClass.getMaxHealth();
    maxHealth = health;
    mana = playerClass.getMaxMana();
    damage = playerClass.getDamage();
    gold = playerClass.getStartGold();
    setProgressBar(json.texture["progressBar"]);
}

void Player::postDefinePlayer(PlayerClass &playerClass, Settings &json){
    playerSprite = playerClass.getPlayerSprite();
    rectSourceSprite = playerClass.getPlayerSprite().getTextureRect();
    this->playerClass = playerClass;
    speed = playerClass.getSpeed();
    health = playerClass.getMaxHealth();
    maxHealth = health;
    mana = playerClass.getMaxMana();
    damage = playerClass.getDamage();
    gold = playerClass.getStartGold();
    setProgressBar(json.texture["progressBar"]);
}

bool Player::checkIsBusy(){
    return isBusy;
}

void Player::setBusy(bool busy){
    isBusy = busy;
}

int Player::getGold(){
    return gold;
}

void Player::addToGold(int amount){
    gold += amount;
}

void Player::useGold(int amount){
    gold -= amount;
}

void Player::loseHealth(int amount){
    health -= amount;
}
void Player::addHealth(int amount){
    health += amount;
}
int Player::getHealth(){
    return health;
}
int Player::getMaxHealth(){
    return maxHealth;
}
void Player::checkBuildingQueue(std::vector<Tower> &towersPlaced, float &frameTime){
    if(!buildingQueue.empty()){
        if(!buildingQueue.front().isBuilt && isBusy && targetReached){
            if(buildingTimer.bPaused){
                buildingTimer.Start();
            }
            updateBuildTimer(frameTime);
        }else if(!buildingQueue.front().isBuilt && !isBusy){
            targetPosition = buildingQueue.front().tex.getPosition();
            isBusy = true;
        }else if(buildingQueue.front().isBuilt){
            Tower tower = buildingQueue.front();
            towersPlaced.push_back(tower);
            buildingQueue.pop();
            isBusy = false;
            currentBuildingTime = 0;
            buildingTimer.Reset();
            buildingTimer.Pause();
        }
    }else{
        currentBuildingTime = 0;
        progressBar.setScale(0,1);
    }
}
void Player::updateBuildTimer(float &frameTime){
    currentBuildingTime = buildingTimer.GetElapsedSeconds();
    progressBar.setScale(1*(buildingTimer.GetElapsedSeconds()/buildingQueue.front().buildTime),1);
    if(buildingTimer.GetElapsedSeconds() >= buildingQueue.front().buildTime){
        buildingQueue.front().isBuilt = true;
        progressBar.setScale(0,1);
    }
}

void Player::addToBuildingQueue(Tower &tower){
    buildingQueue.push(tower);
}
std::queue<Tower>& Player::getBuildingQueue(){
    return buildingQueue;
}

void Player::setProgressBar(sf::Texture &texture){
    progressBar.setTexture(&texture,false);
    progressBar.setSize(sf::Vector2f(playerSprite.getLocalBounds().width,playerSprite.getLocalBounds().width/10));
    progressBar.setScale(0,1);
}

sf::RectangleShape Player::getProgressBar(){
    return progressBar;
}

sf::IntRect Player::getIntRect(){
    return rectSourceSprite;
}

sf::Sprite Player::getSprite() {
    return playerSprite;
}

void Player::spawnPlayer(float startX, float startY){
    isActive = true;
    playerPosition.x = startX;
    playerPosition.y = startY;
    playerSprite.setPosition(playerPosition.x,playerPosition.y);
    progressBar.setPosition(playerPosition.x-(progressBar.getSize().x/2),playerPosition.y-(playerSprite.getLocalBounds().height/2));
    buildingTimer.Reset();
    buildingTimer.Pause();
}

void Player::updatePlayer() {

    double currentPosition = sqrt(std::pow((double) (targetPosition.x - playerPosition.x), 2) +
                                  std::pow((double) (targetPosition.y - playerPosition.y), 2));

    if (currentPosition > 5 && (targetPosition.x != 0 && targetPosition.y != 0)) {
        float v = 1;

        float distance = sqrt((targetPosition.x - playerPosition.x) * (targetPosition.x - playerPosition.x) +
                              (targetPosition.y - playerPosition.y) * (targetPosition.y - playerPosition.y));

        playerDistanceX = v * (targetPosition.x - playerPosition.x) / distance;
        playerDistanceY = v * (targetPosition.y - playerPosition.y) / distance;
        playerPosition.x += playerDistanceX;
        playerPosition.y += playerDistanceY;

        if(isWalking){
            if(targetPosition.x > playerPosition.x){ // Right side
                if(targetPosition.y > playerPosition.y){ // Bottom
                    if(targetPosition.x - playerPosition.x > targetPosition.y-playerPosition.y){ // X is bigger than Y, walk right
                        rectSourceSprite.top = rectSourceSprite.height*2;
                    }else if(targetPosition.x - playerPosition.x < targetPosition.y-playerPosition.y){ // X is less than Y, walk down
                        rectSourceSprite.top = 0;
                    }
                }else if(targetPosition.y < playerPosition.y){ // Top
                    if(targetPosition.x - playerPosition.x < targetPosition.y-playerPosition.y){ // X is less than Y, walk right
                        rectSourceSprite.top = rectSourceSprite.height*2;
                    }if(targetPosition.x - playerPosition.x > targetPosition.y-playerPosition.y){ // X is less than Y, walk up
                        rectSourceSprite.top = rectSourceSprite.height*3;
                    }
                }
            }else if(targetPosition.x < playerPosition.x){ //Left side
                if(targetPosition.y > playerPosition.y){ // Bottom
                    if(playerPosition.x - targetPosition.x > playerPosition.y - targetPosition.y){ // X is bigger than Y, walk left
                        rectSourceSprite.top = rectSourceSprite.height;
                    }if(playerPosition.x - targetPosition.x < playerPosition.y - targetPosition.y){ // X is less than Y, walk down
                        rectSourceSprite.top = 0;
                    }
                }else if(targetPosition.y < playerPosition.y){ // Top
                    if(targetPosition.x - playerPosition.x < targetPosition.y-playerPosition.y){ // X is bigger than Y, walk left
                        rectSourceSprite.top = rectSourceSprite.height;
                    }if(targetPosition.x - playerPosition.x > targetPosition.y-playerPosition.y){ // X is less than Y, walk up
                        rectSourceSprite.top = rectSourceSprite.height*3;
                    }
                }
            }



            if(rectSourceSprite.left != rectSourceSprite.width*3){
                rectSourceSprite.left += rectSourceSprite.width;
            }else{
                rectSourceSprite.left = 0;
            }
        }

        playerSprite.setTextureRect(rectSourceSprite);

        playerSprite.setPosition(playerPosition);
        progressBar.setPosition(playerPosition.x-(progressBar.getSize().x/2),playerPosition.y-(playerSprite.getLocalBounds().height/2));
        progressBar.setScale(0,1);
        isWalking = true;
        targetReached = false;
    }else{
        isWalking = false;
        targetReached = true;
    }
}

PlayerClass Player::getPlayerClass(){
    return playerClass;
}

void Player::setPlayerTarget(float targetX, float targetY){
    targetPosition = sf::Vector2f(targetX,targetY);
    playerDistanceX = targetX - playerPosition.x;
    playerDistanceY = targetY - playerPosition.y;
    /*double angle = (atan2((playerSprite.getPosition().y+playerSprite.getOrigin().y)-
                          targetPosition.y,(playerSprite.getPosition().x+playerSprite.getOrigin().x)-
                                           targetPosition.x)) * 180 / M_PI;
    playerSprite.setRotation((float)angle+270);*/
}

sf::Vector2f Player::getPlayerTarget(){
    return targetPosition;
}

void Player::setPlayerClass(PlayerClass &someClass){
    playerClass = someClass;
}

void Player::setActive(bool active){
    isActive = active;
}

bool Player::checkIsAlive(){
    return isActive;
}

bool Player::checkIsSelected(){
    return isSelected;
}
void Player::setSelected(bool value){
    isSelected = value;
}