#ifndef PROCY_WAVEMANAGER_H
#define PROCY_WAVEMANAGER_H

#include <list>
#include <vector>
#include "Wave.h"
#include "../../Engine/Settings.h"
#include "../Game/Player.h"

class WaveManager {
public:

    WaveManager(Settings &json, Paths &paths);
    void tick(Player &player,Timer &gameTimer,sf::Shader &shader,sf::RenderWindow &window, Settings& json, Paths& paths,Sound &sound);
    bool mapStart(Settings &json, Paths &paths);
    void newWave(Settings &json, Paths &paths);
    std::list<Monster*> getActiveMonsters();
    bool saveState(Settings &json);
    bool loadState(Settings &json,std::string& path);

    bool start;
    bool next_monster;
    bool first_round;
    std::vector<Wave> waves;
    sf::Clock clock;
    unsigned long long int counter;
    std::vector<sf::Vector2i> spawn;
    std::list<Monster> monster_list;
    std::list<Monster> active_mosters;
    int monsterCount;
    Paths paths;
    int unique_monster_id;

};


#endif