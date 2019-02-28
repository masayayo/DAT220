//
// Created by Chrim14 on 10.12.2017.
//

#include "WaveClass.h"

void WaveClass::setSpawnDelaySpeed(float delay_speed) {
    spawnDelay = delay_speed;
}

void WaveClass::setWaveSize(int wave_size) {
    waveSize = wave_size;
}

void WaveClass::setMonsterType(std::string type) {
    monsterType = type;
}

void WaveClass::setMessage(std::string wave_message) {
    message = wave_message;
}

float WaveClass::getSpawnDelaySpeed() {
    return spawnDelay;
}

std::string WaveClass::getMonsterType() {
    return monsterType;
}

int WaveClass::getWaveSize() {
    return waveSize;
}

std::string WaveClass::getMessage() {
    return message;
}

void WaveClass::setWaveId(int wave_id) {
    id = wave_id;
}

int WaveClass::getWaveId() {
    return id;
}
