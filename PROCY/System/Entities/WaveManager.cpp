#include "WaveManager.h"
#include "../MapEditor/MapEditorStaticFunctions.h"

WaveManager::WaveManager(Settings &json, Paths &paths) {
    this->paths = paths;
    counter = 0;
    clock.restart();
    start = false;
    next_monster = false;
    unique_monster_id = 0;
    first_round = true;
}

void WaveManager::tick(Player &player,Timer &gameTimer,sf::Shader &shader,sf::RenderWindow &window, Settings& json, Paths& paths,Sound &sound){

    waves.at(counter).tick(player,gameTimer, shader, window, paths, active_mosters);

    if(!first_round && !next_monster && clock.getElapsedTime().asSeconds() >= 15 || !start && first_round && gameTimer.mC.getElapsedTime().asSeconds() >= 20){
        monsterCount = 0;
        start = true;
        clock.restart();
        next_monster = true;
    }
    else if(next_monster && !waves.empty() && counter < waves.size()) {

        if(start){
            start = false;
            sound.getWaveStarted();
            if(!first_round) counter++;
            else if(first_round) first_round = false;
        }
        if (next_monster && clock.getElapsedTime().asSeconds() >= waves.at(counter).wave_info.getSpawnDelaySpeed()) {
            active_mosters.push_back(monster_list.front());
            monster_list.pop_front();
            monsterCount++;
            clock.restart();
            if (monsterCount >= waves.at(counter).wave_info.getWaveSize()) next_monster = false;
        }
    }
}


bool WaveManager::mapStart(Settings &json, Paths &paths){

    try {
        this->paths = paths;
        counter = 0;
        start = false;
        next_monster = false;
        unique_monster_id = 0;
        first_round = true;
        monster_list.clear();
        active_mosters.clear();

        std::string testString = "spawn";
        spawn = mef::getAllSelectedTileType(json, testString);
        newWave(json, paths);
        return true;
    } catch (...){
        return false;
    }
}

void WaveManager::newWave(Settings &json, Paths &paths){
    unsigned long long int v = 0;
    for(int i = 0; i < json.map.at("waves"); i++){

        Wave wave(spawn);
        std::string wave_type = json.waveList.at(v);
        wave.wave_info = json.waves[wave_type];
        wave.makeDefaultWave(json, paths,wave_type,json.waves.at(wave_type).getWaveSize(),monster_list,unique_monster_id);
        waves.push_back(wave);
        ++v;
        v = v % json.waveList.size();
    }
}


bool WaveManager::saveState(Settings &json){

    //Save format: Monster type, X position, Y position, Health, Direction_left, Direction, Spawn X, Spawn Y, Visible
   /* try {
        waveCount = (int)waves.size();
        json.save["wavemanager"] = {waveCount, counter};
        for(int i = 0; i < waveCount; i++){
            monsterCount = (int)waves.at(i).wave.size();
            json.save["wave"] = {monsterCount, waves.at(i).counter};
            for(int j = 0; j < monsterCount; j++){
               // json.save["monster"] = {waves.at(i).wave.at(j).monsterType, waves.at(i).wave.at(j).sprite.getPosition().x, waves.at(i).wave.at(j).sprite.getPosition().y, waves.at(i).wave.at(j).health, waves.at(i).wave.at(j).direction_left, waves.at(i).wave.at(j).direction, waves.at(i).wave.at(j).spawn.x, waves.at(i).wave.at(j).spawn.y, waves.at(i).wave.at(j).visible};
                json.save["wave"] += json.save["monster"];
            }
            json.save["wavemanager"] += json.save["wave"];
        }

        json.save["wave"] = {};
        json.save["monster"] = {};

    }catch (std::exception& e){
        std::string error = e.what();
        lWarning("Saving monsters failed: "+error);
        return false;
    }*/
    return true;
}

bool WaveManager::loadState(Settings &json,std::string& path){
/*
    try {
        if (std::ifstream(path)) {
            std::ifstream file(path);
            file >> json.save;
        } else {
            lWarning("Unable to load save");
            return false;
        }

        waves.clear();

        counter = json.save["wavemanager"].at(1);

        int waveManagerIndent = 2;
        int waveIndent = 2;

        for (int i = waveManagerIndent; i < (int) json.save["wavemanager"].at(0) + waveManagerIndent; i++) {
            Wave tempWave(spawn);
            tempWave.counter = json.save["wavemanager"].at(i).at(1);
            for (int j = waveIndent; j < (int) json.save["wavemanager"].at(i).at(0) + waveIndent; j++) {
                std::vector<int> tempVector = json.save["wavemanager"].at(i).at(j).at(5);
                Monster tempMonster(sf::Vector2i(json.save["wavemanager"].at(i).at(j).at(6),
                                                 json.save["wavemanager"].at(i).at(j).at(7)), json, paths, json.monsterClasses["default"]);

                tempMonster.sprite.setPosition(json.save["wavemanager"].at(i).at(j).at(1), json.save["wavemanager"].at(i).at(j).at(2));
                tempMonster.health = json.save["wavemanager"].at(i).at(j).at(3);
                tempMonster.direction_left = json.save["wavemanager"].at(i).at(j).at(4);
                tempMonster.direction = tempVector;
                tempMonster.visible = json.save["wavemanager"].at(i).at(j).at(8);
                tempWave.wave.push_back(tempMonster);
            }
            waves.push_back(tempWave);
        }
    }catch (std::exception& e){
        std::string error = e.what();
        lWarning("Failed to load: " + error);
        return false;
    }*/
    return true;
}

std::list<Monster*> WaveManager::getActiveMonsters(){

    std::list<Monster*> temp_list;

    for(auto& temp : active_mosters){
        temp_list.push_back(&temp);
    }

    return temp_list;
}