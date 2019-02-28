//
// Created by Masaya on 10/24/2017.
//

#ifndef PROCY_HUD_H
#define PROCY_HUD_H

#include <SFML/Graphics.hpp>
#include "../../Engine/StateMachine.h"
#include <TGUI/Gui.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include "../Map/Map.h"
#include "Timer.h"

class HUD {
public:
    void initializeHUD(std::string &towerSelected,std::vector<tgui::Panel::Ptr> &panels,tgui::Gui& gui, StateMachine &state, sf::RenderWindow &window, Settings &json, Sound& sound, sf::View &view);
    void updateGameTimer(Timer &gameTimer);
    void hudHandler(std::string &towerSelected,Timer &gameTimer,bool &hudLoaded,std::vector<tgui::Panel::Ptr> &panels,tgui::Gui& gui,StateMachine &state, sf::RenderWindow &window, Settings &json, Sound& sound, sf::View &view);
    void handleHealthBar(tgui::Gui &gui, Settings &json);
    void handleSelection(std::string &towerSelected,Player* player,tgui::Gui &gui, Settings &json);
    void checkWidget(int &x, int &y);
    void updatePlayerGold(int playerGold);
    void checkTowerAvailable(int playerGold);
    void setTowerSelected(Tower* tower);
    void setPlayerSelected(Player* player);
    void setMonsterSelected(Monster* monster);
private:
    Tower* towerSelected = nullptr;
    Player* playerSelected = nullptr;
    Monster* monsterSelected = nullptr;
    sf::RectangleShape healthBarRect;
    sf::RectangleShape manaBarRect;
    sf::Font font;
    sf::Text healthText;
    sf::Text manaText;
    sf::Sprite healthFrame;
    sf::Sprite manaFrame;
    tgui::Label::Ptr gold;
    std::map<std::string,std::pair<int,tgui::Picture::Ptr>> towerGrid;
};


#endif //PROCY_HUD_H
