//
// Created by Chrim14 on 23.10.2017.
//

#ifndef PROCY_MAPEVENTS_H
#define PROCY_MAPEVENTS_H

#include <SFML/Graphics.hpp>
#include "../../Engine/StateMachine.h"
#include "Map.h"
#include "../Game/Timer.h"
#include "../Game/Player.h"
#include "../Game/HUD.h"

class MapEvents : public Map {

public:

    void eventHandler(std::vector<tgui::Panel::Ptr> &panels,Timer &gameTimer,sf::RenderWindow &window, sf::Event &event, StateMachine &state, Settings &json, tgui::Gui &gui, Sound &sound, WaveManager &waveManager);

    void moveView(bool view_Locked, sf::RenderWindow &window, StateMachine &state, Settings &json, std::vector<tgui::Panel::Ptr> &panels, tgui::Gui &gui);

    void clickEvent(Player &player,WaveManager &waveManager,HUD &hud,bool &placedTowerSelected,std::vector<Tower> &towersPlaced,std::string &towerSelected,std::vector<tgui::Panel::Ptr> &panels,sf::VertexArray &mapTiles, sf::VertexArray &bitTiles, sf::Event &event, StateMachine &state, Settings &json, sf::RenderWindow &window, tgui::Gui &gui);

    void clickReleaseEvent(std::vector<tgui::Panel::Ptr> &panels,sf::VertexArray &mapTiles, sf::VertexArray &bitTiles, sf::Event &event, StateMachine &state, Settings &json, sf::RenderWindow &window, tgui::Gui &gui);

private:
    void clickEventMiniMap(sf::Vector2f &gamePosition, Settings &json);
};


#endif //PROCY_MAPEVENTS_H
