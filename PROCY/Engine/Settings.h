//
// Created by Chrim14 on 07.10.2017.
//

#ifndef PROCY_SETTINGS_H
#define PROCY_SETTINGS_H

#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Third party/json.hpp"
#include "../Debugger/Logging.h"
#include "../System/Game/Tower.h"
#include "../System/Game/PlayerClass.h"
#include "../System/Entities/MonsterClass.h"
#include "../System/Entities/waveClass.h"

#define TextSize (gui.getSize().y*0.03f)
#define windowWidth tgui::bindWidth(gui)
#define windowHeight tgui::bindHeight(gui)

using json = nlohmann::json;

unsigned const int  Layer_One_Size = 150;
unsigned const int  Layer_One_Size_Min = 15;
unsigned const int  Tile_Size = 60;
unsigned const int  MAX_WAVES = 100;
unsigned const int  MAX_PLAYERS = 10;
unsigned const int  Bits_To_Tiles = 3;
unsigned const int  Layer_Two_Size = Layer_One_Size*Bits_To_Tiles;


class Settings {
public:

    Settings();

    void standardSettings();
    void getSettings();
    void saveSettings();

    void editorSettings(int height, int length, int startTile, std::string mapName);

    void setMapValues();

    void setViews(sf::RenderWindow &window);

    void getViewSizeList();

    json setting;
    json system;   //For system configuration, like view resolutions
    json language;
    json editor;
    json tiles;
    json map;
    json keys;
    json save;

    std::vector<std::string> waveList;

    sf::Event event{};



    unsigned int tileValue[Layer_One_Size][Layer_One_Size];
    unsigned int bitTileValue[Layer_Two_Size][Layer_Two_Size];
    bool mapLoaded = false;
    bool mapPreview = false;
    bool highlight = false;
    bool mapSelected = false;
    bool mapImage = false;
    bool showFPS = false;

    std::map<std::string,sf::Texture> texture;
    std::map<std::string,sf::Sprite> sprite;
    std::map<std::string,Bullet> bullet;
    std::map<std::string,sf::Image> image;
    std::map<std::string,sf::View> view;
    std::map<std::string,Tower> towerSprites;
    std::map<std::string,PlayerClass> playerClasses;
    std::map<std::string,MonsterClass> monsterClasses;
    std::map<std::string,WaveClass> waves;
    std::map<std::string,std::string> newGamePlayers;
    std::string TextureInUse = "tiles.png";

private:

    void controlSettings();
    void getTextures();
    void getTowers();
    void getPlayerClasses();
    void getMonsters();
};


#endif //PROCY_SETTINGS_H
