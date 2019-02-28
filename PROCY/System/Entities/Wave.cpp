#include "Wave.h"

Wave::Wave(std::vector<sf::Vector2i> &set_spawn){
    spawn = set_spawn;
    spawnCounter = 0;
    WaveClass wave_info;
}

void Wave::tick(Player &player,Timer &gameTimer,sf::Shader &shader,sf::RenderWindow &window, Paths& paths,std::list<Monster> &active_monster){

    for(auto it = active_monster.begin(); it != active_monster.end();it++){
        if(it->direction.empty()){
            player.loseHealth(it->damage);
            it = active_monster.erase(it);
            continue;
        }
        it->tick(player,gameTimer,shader,window, paths);
    }
}

void Wave::makeDefaultWave(Settings &json, Paths& paths,std::string& monster_type,int wave_size,std::list<Monster> &list,int &unique_monster_id) {

    for (int i = 0; i < wave_size; i++) {

        Monster mon(spawn.at(spawnCounter), json, paths, json.monsterClasses[monster_type]);
        mon.setHealthBar(json.texture["progressBar"]);
        mon.unique_id = unique_monster_id++;
        list.push_back(mon);

        if (spawnCounter < (int) spawn.size() - 1) {
            spawnCounter++;
        } else {
            spawnCounter = 0;
        }
    }
}