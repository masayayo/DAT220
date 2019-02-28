//
// Created by Chrim14 on 10.10.2017.
//

#ifndef PROCY_MAP_H
#define PROCY_MAP_H

#include "MapFunctions.h"
#include "../Game/Player.h"
#include "../Entities/WaveManager.h"
#include "../Pathfinder/Paths.h"

class Map : public MapFunctions {
public:
    Map() = default;

    void mapHandler(sf::Shader &shader,Player &player,Timer &gameTimer,std::vector<Tower> &towersPlaced,std::string &towerSelected, sf::VertexArray &mapTiles, sf::VertexArray &bitTiles, StateMachine &state, sf::RenderWindow &window, Settings &json,sf::VertexArray &miniMapSquare, tgui::Gui &gui, Sound &sound,Paths& path, WaveManager &waveManager);

    void getMiniMapView(tgui::Gui &gui,sf::RenderWindow &window, Settings &json, sf::VertexArray &mapTiles,sf::VertexArray &miniMapSquare);

protected:
    int getViewFocused(std::vector<tgui::Panel::Ptr> &panels,bool dynamical_focus, sf::Vector2i &pixelPosition, Settings &json, StateMachine &state, sf::RenderWindow &window, tgui::Gui &gui);

private:

    void setView(sf::View &view, Settings &json);

    void setMiniMapView(sf::RenderWindow &window, Settings &json,sf::VertexArray &miniMapSquare);

    void getMap(sf::VertexArray &mapTiles, sf::VertexArray &bitTiles, Settings &json);

    void CreateNewMap(Settings &json);
};


#endif //PROCY_MAP_H
