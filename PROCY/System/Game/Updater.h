//
// Created by Masaya on 11/22/2017.
//

#ifndef PROCY_UPDATER_H
#define PROCY_UPDATER_H

#include "Player.h"
#include "../Entities/WaveManager.h"
#include "../../Engine/StateMachine.h"

class Updater{
public:
    void updateTowers(WaveManager &waveManager,Player &player,Timer &gameTimer,float &frameTime, std::vector<Tower> &towersPlaced, sf::RenderWindow &window, Settings &json, Sound &sound);
    void updatePlayers(Player &player, Timer &gameTimer,float &frameTime, std::vector<Tower> &towersPlaced, sf::RenderWindow &window, Settings &json, Sound &sound);
    void updateMonsters(Player &player,Timer &gameTimer,sf::Shader &shader,sf::RenderWindow &window, WaveManager &waveManager, StateMachine &stateMachine, Settings& json, Paths& paths,Sound &sound);
    void drawPlayers(Player &player,sf::Shader &shader,sf::RenderWindow &window);
    void drawTowers(Timer &gameTimer,sf::Shader &shader,std::string &towerSelected, std::vector<Tower> &towersPlaced,Player &player, sf::RenderWindow &window, Settings &json);
    void drawMonsters(WaveManager &waveManager, sf::RenderWindow &window,sf::Shader &shader);
    bool isPointerOverSprite(sf::Vector2f position, const sf::Sprite &sprite);
};



#endif //PROCY_UPDATER_H
