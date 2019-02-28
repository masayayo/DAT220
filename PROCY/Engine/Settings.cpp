//
// Created by Chrim14 on 07.10.2017.
//


#include "Settings.h"
#include "Div/Tile_List.h"
#include "Div/Language.h"
#include "Div/KeyBinds.h"
#include "../System/Entities/waveClass.h"


///From: Game::Game
///Function: holding most of the stored and used data in the game
Settings::Settings() {

    getSettings();
    Language::getLanguage(language, setting);
    KeyBinds::getKeys(keys);
    Tile_List::setTileList(tiles);
    getTextures();
    getTowers();
    getMonsters();
    getPlayerClasses();
    getViewSizeList();
}

///From: SettingButtons::applySettings, Settings::getSettings
///Function: change json original settings to original settings.
void Settings::standardSettings() {

    lDebug("Getting standard settings");

    //window size
    setting["wWidth"] = 1280;
    setting["wHeight"] = 720;
    setting["wFullScreen"] = false;
    setting["version"] = "pre-alpha";

    //music start volum
    setting["music"] = 50;
    setting["sound"] = 50;
    setting["system"] = 50;
    setting["mute"] = false;
    setting["sync"] = false;
    setting["anti"] = 0;
    setting["fps"] = 0;
    setting["bullets"] = true;
    setting["texture"] = false;


    setting["startView"] = 10.0f;
    setting["zoom"] = 5.0f;
    setting["viewSpeed"] = 8.0f;
    setting["tilesOut"] = 2.0f;

    setting["language"] = "English";
    setting["name"] = "Player";

}


///From: SettingButtons::applySettings, Settings::getSettings
///Function: saving settings to .json file.
void Settings::saveSettings() {

    lInfo("Saving new settings to Settings.json");

    std::ofstream file("Texture/Settings.json");

    if(!file){
        lWarning("File settings.json could not be saved");
        return;
    }

    file << std::setw(4) << setting << std::endl;
}


///From: Menu::MenuSettings
///Function: Get settings stored in settings.json
void Settings::getSettings() {

    lDebug("Getting setting settings");

    std::string filePathSettings = "Texture/Settings.json"; //repeated in catch
    try {
        if (std::ifstream(filePathSettings)) {
            lInfo("Getting settings file information");
            std::ifstream file(filePathSettings);
            file >> setting;

            controlSettings();

            return;
        }
    }
    catch (...){
        if( std::remove("Texture/Settings.json") != 0){
            lFatal("settings.json corrupt, could not delete it");
        }else{
            lWarning("settings.json corrupt, deleted it");
        }
    }
    standardSettings();
    saveSettings();
}


///From: EditorSetup::getEditorSetupMenu, EditorSetup::getLoadChildWindow, EditorSetup::setNewMapValues
///Function: setting values that is used in editor
void Settings::editorSettings(int height, int length, int startTile, std::string mapName) {

    editor["height"] = height;
    editor["width"] = length;
    editor["tile"] = startTile;         //Only used when new map is created
    editor["name"] = mapName;
    editor["tileType"] = "ground";      //Declaring first tile menu
    editor["draw"] = 0;                 //0 prevent tiles from being drawn before any tiles selected
    editor["rotate"] = 0;               //Roation value
    editor["drawable"] = true;          //Switch between draw and select tile
    editor["info"] = {
            editor["tile_x"] = 0,
            editor["tile_y"] = 0,
            editor["tile_type"] = "",
            editor["tile_id"] = 0
    };

    editor["selected_tile"] = {0, 0};
    editor["selected_type"] = "";

}

///From: Settings::editorSettings
///Function: Setting json objects for all map information, used leater when saving map in editor
void Settings::setMapValues() {
    map.clear();
    map["version"] = setting["version"];
    map["height"] = editor["height"];
    map["width"] = editor["width"];
    map["name"] = editor["name"];
    map["map"] = {};
    map["bmap"] = {};

    map["players"] = 1;
    map["divided"] = false;
    map["team"] = false;
    map["teams"] = 2;
    map["fixed_waves"] = true;
    map["waves"] = 50;
    map["description"] = "";
    map["image"] = "";

    map["spawn"] = {};
    map["divider"] = {};
    map["speed"] = {};
    map["teleport"] = {};
}


///###################################### PRIVATE ###########################################################


///From: Settings::getSetting
///Function: control if setting file have all elements, if not replace missing objects
void Settings::controlSettings() {

    //Storing file settings
    json fileSettings = setting;

    //changing json settings to standard settings
    standardSettings();

    bool noError = true;

    for (json::iterator it = setting.begin(); it != setting.end();it++) {

        for (json::iterator it2 = fileSettings.begin(); it2 != fileSettings.end();it2++) {

            if(it.key() == it2.key()){
                if(it.value().type_name() != it2.value().type_name()) {
                    lWarning("Settings object '"+it2.key()+"' was data type "+ it2.value().type_name()+" wanted "+it.value().type_name());
                    fileSettings.erase(it2);
                }
                break;
            }
        }
    }

    std::vector<std::string> original;

    //Adding all settings from file in a std::vector
    for (json::iterator it = fileSettings.begin(); it != fileSettings.end();it++) {
        original.push_back(it.key());
    }

    //comparing standard objects with the original settings
    for (json::iterator it = setting.begin(); it != setting.end();it++) {

        //if origin list empty: Add standard setting to original settings
        if(original.empty()){
            noError = false;
            lWarning("Language object was missing: " + it.key());
            fileSettings[it.key()] = it.value();
        }

        for (auto it2 = original.begin(); it2 != original.end(); it2++){

            //IF a match: remove element from origin string
            if(it.key() == it2->data()){
                original.erase(it2);
                break;
            }

                //if end reached: add missing key to original settings
            else if(std::next(it2) == original.end()){
                noError = false;
                lWarning("Settings object was missing: " + it.key());
                fileSettings[it.key()] = it.value();
            }
        }
    }

    //Adding back the original settings to settings json
    setting = fileSettings;

    //If a error has happend, store new data
    if(!noError)
        saveSettings();
}

void Settings::getTextures() {


    if (!texture["tiles"].loadFromFile("Texture/Texture/system/tiles.png"))
    {

    }

    /*if (!texture["tower_1"].loadFromFile("Texture/Texture/tower.png"))
    {

    }*/


    if (!image["icon"].loadFromFile("Texture/Texture/system/icon.png")){

    };




    if (!texture["pointer"].loadFromFile("Texture/Texture/system/pointer.png"))
    {

    }
    sprite["pointer"].setTexture(texture["pointer"]);

    // Load tower textures
    if(!texture["tower_1"].loadFromFile("Texture/Texture/cannons/tank1_gun.png")){}
    if(!texture["tower_2"].loadFromFile("Texture/Texture/cannons/tank1_dualgun.png")){}
    if(!texture["tower_3"].loadFromFile("Texture/Texture/cannons/tank2_gun.png")){}
    if(!texture["tower_4"].loadFromFile("Texture/Texture/cannons/tank2_dualgun.png")){}
    if(!texture["tower_5"].loadFromFile("Texture/Texture/cannons/tank1_dualgun.png")){}
    if(!texture["tower_6"].loadFromFile("Texture/Texture/cannons/tank3c_gun.png")){}
    if(!texture["tower_7"].loadFromFile("Texture/Texture/cannons/magic_ball.png")){}
    if(!texture["tower_8"].loadFromFile("Texture/Texture/cannons/auby.png")){}
    if(!texture["tower_9"].loadFromFile("Texture/Texture/cannons/tank2b_gun_destroyed.png")){}
    if(!texture["tower_10"].loadFromFile("Texture/Texture/cannons/tank3b_gun_destroyed.png")){}
    if(!texture["tower_11"].loadFromFile("Texture/Texture/cannons/tank2b_dualgun_destroyed.png")){}
    if(!texture["tower_12"].loadFromFile("Texture/Texture/cannons/tank2_dualgun_destroyed.png")){}


    if(!texture["bullet"].loadFromFile("Texture/Texture/bullets/bullet.png")){}
    if(!texture["progressBar"].loadFromFile("Texture/Texture/system/progressbar.png")){}
    if(!texture["c++"].loadFromFile("Texture/Texture/bullets/c++.png")){}
    if(!texture["flame"].loadFromFile("Texture/Texture/bullets/flame.png")){}
    if(!texture["manaBar"].loadFromFile("Texture/Texture/system/manabar.png")){}
    if(!texture["bitCoin"].loadFromFile("Texture/Texture/system/bitcoin.png")){}

    //if(!texture["bullet_long"].loadFromFile("Texture/Texture/bullet_long.png")){}

    if(!texture["miniMapFrame"].loadFromFile("Texture/Texture/system/frame.png")){}

    // Load class textures
    if(!texture["paladin"].loadFromFile("Texture/Texture/player/wizard.png")){}
    if (!texture["player"].loadFromFile("Texture/Texture/player/wizard.png")){}
    if (!texture["bagIcon"].loadFromFile("Texture/Texture/items/bagIcon.png")){}
}

void Settings::getTowers(){

    /*sf::Texture t;
    t.loadFromFile("Texture/Texture/t1.png");*/

    std::string normalSound = "sfx16";
    std::string flameSound = "flamethrowerSound";

    // Tower 1
    Tower tower;
    tower.tex.setTexture(texture["tower_1"]);
    tower.bulletType = "bullet";
    tower.towerType = "tower_1";
    tower.towerName = "Basic tower";
    tower.soundName = normalSound;
    tower.towerDescription = "This is the most basic of the basic towers. It features basic firerate, basic damage ourput and basic range.";
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 100;
    tower.damage = 20;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_1"] = tower;

    // Tower 2
    tower.tex.setTexture(texture["tower_2"]);
    tower.bulletType = "bullet";
    tower.towerName = "Basic tower";
    tower.towerType = "tower_2";
    tower.towerDescription = "";
    tower.soundName = normalSound;
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 500;
    tower.damage = 20;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_2"] = tower;

    // Tower 3
    tower.tex.setTexture(texture["tower_3"]);
    tower.bulletType = "bullet";
    tower.towerName = "Basic tower";
    tower.towerType = "tower_3";
    tower.towerDescription = "";
    tower.soundName = normalSound;
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 900;
    tower.damage = 20;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_3"] = tower;

    // Tower 4
    tower.tex.setTexture(texture["tower_4"]);
    tower.bulletType = "bullet";
    tower.towerName = "Basic tower";
    tower.towerType = "tower_4";
    tower.towerDescription = "";
    tower.soundName = normalSound;
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 700;
    tower.damage = 20;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_4"] = tower;

    // Tower 5
    tower.tex.setTexture(texture["tower_5"]);
    tower.bulletType = "bullet";
    tower.towerName = "Basic tower";
    tower.towerType = "tower_5";
    tower.towerDescription = "";
    tower.soundName = normalSound;
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 200;
    tower.damage = 20;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_5"] = tower;

    // Tower 6
    tower.tex.setTexture(texture["tower_6"]);
    tower.bulletType = "bullet";
    tower.towerName = "Basic tower";
    tower.towerType = "tower_6";
    tower.towerDescription = "";
    tower.soundName = normalSound;
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 200;
    tower.damage = 20;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_6"] = tower;

    // Tower 7
    tower.tex.setTexture(texture["tower_7"]);
    tower.bulletType = "bullet";
    tower.towerName = "Basic tower";
    tower.towerType = "tower_7";
    tower.soundName = normalSound;
    tower.towerDescription = "";
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 150;
    tower.damage = 20;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_7"] = tower;

    tower.tex.setTexture(texture["tower_8"]);
    tower.bulletType = "c++";
    tower.towerName = "Christian Auby";
    tower.towerType = "tower_8";
    tower.soundName = normalSound;
    tower.towerDescription = "Before this tower had some meaning, but now it's useless.";
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 150;
    tower.damage = 1;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_8"] = tower;

    tower.tex.setTexture(texture["tower_9"]);
    tower.bulletType = "bullet";
    tower.towerName = "Endless destoyer";
    tower.towerType = "tower_9";
    tower.soundName = normalSound;
    tower.towerDescription = "This is the heaviest tower there is. Really high damage, low firerate.";
    tower.fireRate = 0.5;
    tower.range = 100;
    tower.buildingCost = 150;
    tower.damage = 1;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_9"] = tower;

    tower.tex.setTexture(texture["tower_10"]);
    tower.bulletType = "flame";
    tower.towerName = "Flamethrower";
    tower.towerType = "tower_10";
    tower.soundName = flameSound;
    tower.towerDescription = "Ready to burn you enemies to crisp? Place this tower and watch the world burn.";
    tower.fireRate = 0.1;
    tower.range = 100;
    tower.buildingCost = 150;
    tower.damage = 1;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 3;
    tower.h = 3;
    towerSprites["tower_10"] = tower;

    tower.tex.setTexture(texture["tower_11"]);
    tower.bulletType = "bullet";
    tower.towerName = "Ragnarok";
    tower.towerType = "tower_11";
    tower.soundName = normalSound;
    tower.towerDescription = "Instantly oneshots most enemies every 30 seconds.";
    tower.fireRate = 10;
    tower.range = 100;
    tower.buildingCost = 150;
    tower.damage = 1000;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 6;
    tower.h = 6;
    towerSprites["tower_11"] = tower;

    tower.tex.setTexture(texture["tower_12"]);
    tower.bulletType = "bullet";
    tower.towerName = "Something";
    tower.towerType = "tower_12";
    tower.soundName = normalSound;
    tower.towerDescription = "Derp tower.";
    tower.fireRate = 10;
    tower.range = 100;
    tower.buildingCost = 150;
    tower.damage = 1000;
    tower.health = 1000;
    tower.maxHealth = 1000;
    tower.w = 6;
    tower.h = 6;
    towerSprites["tower_12"] = tower;

    Bullet bullet1;
    bullet1.setSprite(texture["bullet"],.5f,.5f);
    bullet1.setBulletSpeed(10);
    bullet1.setBulletRange(200);
    bullet["bullet"] = bullet1;

    bullet1;
    bullet1.setSprite(texture["c++"],.5f,.5f);
    bullet1.setBulletSpeed(1);
    bullet1.setBulletRange(200);
    bullet["c++"] = bullet1;

    bullet1;
    bullet1.setSprite(texture["flame"],.5f,.5f);
    bullet1.setBulletSpeed(4);
    bullet1.setBulletRange(200);
    bullet["flame"] = bullet1;
}

void Settings::getPlayerClasses(){
    PlayerClass class1;
    class1.setPlayerSprite(texture["paladin"]);
    class1.setClassName("Paladin");
    class1.setMaxHealth(100);
    class1.setDamage(200);
    class1.setMaxMana(100);
    class1.setSpeed(0.5f);
    class1.setStartGold(1000);
    playerClasses["paladin"] = class1;
}

void Settings::setViews(sf::RenderWindow &window){

    //Mini map view
    view["map"];

    //Main view
    view["main"].setViewport(sf::FloatRect(0,0,1,1));

    //Windows view
    view["fixed"].reset(sf::FloatRect(0,0, window.getSize().x,window.getSize().y));

    //Game panel view
    view["hud"].setViewport(sf::FloatRect(0,0,1,1));

}

void Settings::getViewSizeList() {

    system["x_list"] ={};
    system["setting"] = 0;
    system["focused"] = false;
    system["panel"] = "";
    system["player_position"] = 0;
    system["difficulty"] = 1.0;

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    std::vector<sf::Vector2i> screen_size;

    screen_size.push_back(sf::Vector2i(640,360));
    screen_size.push_back(sf::Vector2i(896,504));
    screen_size.push_back(sf::Vector2i(1024,576));
    screen_size.push_back(sf::Vector2i(1280,720)); // HD
    screen_size.push_back(sf::Vector2i(1664,936));
    screen_size.push_back(sf::Vector2i(1920,1080)); // Full HD
    screen_size.push_back(sf::Vector2i(2176,1224));
    screen_size.push_back(sf::Vector2i(2560,1440));
    screen_size.push_back(sf::Vector2i(2688,1512));
    screen_size.push_back(sf::Vector2i(2816,1584));
    screen_size.push_back(sf::Vector2i(3840,2160)); // 4K
    screen_size.push_back(sf::Vector2i(5120,2880)); // 5K Ratina
    screen_size.push_back(sf::Vector2i(7680,4320)); // 8K

    /*
    // Delete all modes that does not have have a 16/9 aspect ratio
    for(std::size_t i = 0; i < modes.size(); i++){
        if(fabs(((double)modes[i].width / (double)modes[i].height) - ((double)16 / (double)9)) != 0){
            modes.erase(modes.begin() + i);
            i--;
        }
            //IF resolution is larger then screen, remove.
        else if(sf::VideoMode::getDesktopMode().width < modes[i].width ||  sf::VideoMode::getDesktopMode().height < modes[i].height){
            modes.erase(modes.begin() + i);
            i--;
        }
    }

    for (auto it = modes.end(); it != modes.begin() ; it--){
        for (int i = 0; i < system["x_list"].size(); i+=2) {
            if(system["x_list"][i] == it->width) goto label;
        }
        system["x_list"] += it->width;
        system["x_list"] += it->height;
    }
    label:;*/

    for(auto& temp : screen_size){
        if(temp.x <= sf::VideoMode::getDesktopMode().width){
            system["x_list"] += temp.x;
            system["x_list"] += temp.y;
        }
    }
}

void Settings::getMonsters(){
    int counter = 0;
    std::string path = "Texture/Texture/monster/";


    std::string type = "blue";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(0.8f);
        defaultMonster.setDamage(1);
        defaultMonster.setValue(10);
        defaultMonster.setMaxHealth(50);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(15);
        waveClass.setSpawnDelaySpeed(1.0);
        waveClass.setMonsterType(type);
        std::string wave_number = std::to_string(counter);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "sadako";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(2.0f);
        defaultMonster.setDamage(1);
        defaultMonster.setValue(12);
        defaultMonster.setMaxHealth(35);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(20);
        waveClass.setSpawnDelaySpeed(1.0);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "jenova";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(1.0f);
        defaultMonster.setDamage(1);
        defaultMonster.setValue(15);
        defaultMonster.setMaxHealth(25);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(10);
        waveClass.setSpawnDelaySpeed(0.8);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "death";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(0.4f);
        defaultMonster.setDamage(1);
        defaultMonster.setValue(20);
        defaultMonster.setMaxHealth(35);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(15);
        waveClass.setSpawnDelaySpeed(1.0);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "ryuk";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(0.2f);
        defaultMonster.setDamage(2);
        defaultMonster.setValue(20);
        defaultMonster.setMaxHealth(100);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(10);
        waveClass.setSpawnDelaySpeed(1.5);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "drax";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(0.9f);
        defaultMonster.setDamage(2);
        defaultMonster.setValue(50);
        defaultMonster.setMaxHealth(110);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(12);
        waveClass.setSpawnDelaySpeed(1.4f);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "redskull";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(0.9f);
        defaultMonster.setDamage(2);
        defaultMonster.setValue(50);
        defaultMonster.setMaxHealth(210);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(12);
        waveClass.setSpawnDelaySpeed(1.4f);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "zemus";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(0.1f);
        defaultMonster.setDamage(3);
        defaultMonster.setValue(50);
        defaultMonster.setMaxHealth(350);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(15);
        waveClass.setSpawnDelaySpeed(0.01f);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "redxiii";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(0.15f);
        defaultMonster.setDamage(2);
        defaultMonster.setValue(60);
        defaultMonster.setMaxHealth(200);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(5);
        waveClass.setSpawnDelaySpeed(2.0);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }


    type = "bahamut";
    if(texture[type].loadFromFile(path+type+".png")){
        MonsterClass defaultMonster;
        defaultMonster.setMonsterSprite(texture[type]);
        defaultMonster.setClassName(type);
        defaultMonster.setSpeed(0.1);
        defaultMonster.setDamage(5);
        defaultMonster.setValue(1000);
        defaultMonster.setMaxHealth(10000);
        monsterClasses[type] = defaultMonster;

        WaveClass waveClass;
        waveClass.setWaveId(counter);
        waveClass.setWaveSize(1);
        waveClass.setSpawnDelaySpeed(2.0);
        waveClass.setMonsterType(type);
        waves[type] = waveClass;
        waveList.push_back(type);
        counter++;
    }else{ lWarning(type+" did not load"); }
}