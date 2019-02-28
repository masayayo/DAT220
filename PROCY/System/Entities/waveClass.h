//
// Created by Chrim14 on 10.12.2017.
//

#ifndef PROCY_WAVECLASS_H
#define PROCY_WAVECLASS_H

#include <iostream>
#include <SFML/Audio.hpp>
#include "../../Third party/json.hpp"
//#include "../Pathfinder/Paths.h"

using json = nlohmann::json;

class Monster;

class WaveClass {
public:
    void setWaveId(int wave_id);
    void setSpawnDelaySpeed(float delay_speed);
    void setWaveSize(int wave_size);
    void setMonsterType(std::string type);
    void setMessage(std::string wave_message);

    int getWaveId();
    float getSpawnDelaySpeed();
    int getWaveSize();
    std::string getMonsterType();
    std::string getMessage();

private:
    float spawnDelay{};
    int waveSize{};
    int id{};
    std::string monsterType;
    std::string message;
};

#endif //PROCY_WAVECLASS_H
