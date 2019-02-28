#ifndef PROCY_WAVE_H
#define PROCY_WAVE_H

#include <vector>
#include <list>
#include "Monster.h"
#include "../../Engine/Settings.h"
#include "../Game/Player.h"

class Wave {
public:

    Wave(std::vector<sf::Vector2i> &spawn);
    void makeDefaultWave(Settings &json, Paths& paths,std::string& monster_type,int wave_size,std::list<Monster> &list,int &unique_monster_id);
    void tick(Player &player,Timer &gameTimer,sf::Shader &shader,sf::RenderWindow &window, Paths& paths,std::list<Monster> &active_mosnter);

    unsigned long long int spawnCounter;
    WaveClass wave_info;
    std::vector<sf::Vector2i> spawn;
};


#endif