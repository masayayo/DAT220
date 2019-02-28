//
// Created by Chrim14 on 23.10.2017.
//

#include "MapEvents.h"
#include "../../GUI/MapEditor/EditorChildWindows.h"
#include "../MapEditor/MapEditorStaticFunctions.h"
#include "MapStaticFunctions.h"
#include "../../GUI/Menu/MenuPanels.h"
#include "../../Engine/Div/KeyBinds.h"

#define FOCUSED_MAP 1
#define FOCUSED_MINIMAP 2
#define FOCUSED_TGUI 3

///From: Game::Game()
///Function: Handle most key event, excepts Arrow keys.
void MapEvents::eventHandler(std::vector<tgui::Panel::Ptr> &panels, Timer &gameTimer,sf::RenderWindow &window, sf::Event &event, StateMachine &state, Settings &json, tgui::Gui &gui, Sound &sound, WaveManager &waveManager) {


    if (state.getState() == List_State::MapEditor || state.getState() == List_State::Game) {

            sf::View view = json.view["main"];

            if (event.type == sf::Event::MouseWheelMoved) {

                sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);

                int focusValue = getViewFocused(panels,true, pixelPosition, json, state, window, gui);

                if(focusValue == FOCUSED_MAP || focusValue == FOCUSED_MINIMAP) {

                // sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
                // sf::Vector2f gamePosition = window.mapPixelToCoords(pixelPosition);

                float zoom = json.setting["zoom"]; //Zoom 4%
                zoom = zoom / 100.0f;

                //IF zooming in
                if (event.mouseWheel.delta > 0 && view.getSize().x > Tile_Size * 10.0f) {
                    view.zoom(1.0f - zoom);
                    // view.move(gamePosition.x*0.1f - view.getCenter().x*0.1f, gamePosition.y*0.1f - view.getCenter().y*0.1f);
                }
                    //IF zooming out
                else if (event.mouseWheel.delta < 0) {

                    sf::Vector2f viewMin = view.getCenter() - (view.getSize() / 2.0f);
                    sf::Vector2f viewMax = viewMin + view.getSize();
                    sf::Vector2f zoomChange = view.getSize() * (zoom / 2.0f);

                    float settingTilesOut = json.setting["tilesOut"];
                    float maxTilesOut = Tile_Size * settingTilesOut;

                    float height = json.map["height"];
                    float width = json.map["width"];

                    float maxX = (width * Tile_Size + maxTilesOut);
                    float maxY = (height * Tile_Size + maxTilesOut);
                    if(state.getState() == List_State::Game) maxY = (height * Tile_Size + maxTilesOut) +(window.getSize().y/4.0f);

                    //Checks first if view are into a wall and not into max and min view value of that direction
                    if (
                            (viewMax.x + zoomChange.x > maxX && viewMin.x - zoomChange.x > -maxTilesOut) ||
                            (viewMax.x + zoomChange.x < maxX && viewMin.x - zoomChange.x < -maxTilesOut) ||
                            (viewMax.y + zoomChange.y > maxY && viewMin.y - zoomChange.y > -maxTilesOut) ||
                            (viewMax.y + zoomChange.y < maxY && viewMin.y - zoomChange.y < -maxTilesOut)) {

                        float moveX = zoomChange.x;
                        float moveY = zoomChange.y;

                        //Checking if x Max reached but not x Min
                        if (viewMax.x + zoomChange.x > maxX && viewMin.x - zoomChange.x > -maxTilesOut) {

                            view.move(-moveX, 0);
                        } else if (viewMax.x + zoomChange.x < maxX && viewMin.x - zoomChange.x < -maxTilesOut) {

                            view.move(moveX, 0);
                        }
                        if (viewMax.y + zoomChange.y > maxY && viewMin.y - zoomChange.y > -maxTilesOut) {

                            view.move(0, -moveY);
                        } else if (viewMax.y + zoomChange.y < maxY && viewMin.y - zoomChange.y < -maxTilesOut) {

                            view.move(0, moveY);
                        }

                        view.zoom(1.0f + zoom);
                    }

                        //Else if view not into a wall or view max value reached in one direction, zoom if the other direction have space left.
                    else if (
                            (viewMax.x + zoomChange.x <= maxX && viewMin.x - zoomChange.x >= -maxTilesOut) ||
                            (viewMax.y + zoomChange.y <= maxY && viewMin.y - zoomChange.y >= -maxTilesOut)) {
                        view.zoom(1.0f + zoom);
                    }
                }
                window.setView(view);
            }
        }
        json.view["main"] = view;
    }

    if(event.type == sf::Event::KeyReleased){
        if(json.system["focused"]){ //only for key settings menu
            menuPanel::setKey(gui,json);
        }
        else if(event.key.code == json.keys["Escape"]){

            if(menuPanel::panelThere(gui)){
                json.getSettings();
                KeyBinds::getKeys(json.keys);
                sound.setSound(json.setting["mute"], json.setting["music"], json.setting["sound"], json.setting["system"]);
                json.system["focused"] = false;
            }
            if(state.getState() == List_State::Game) {
                lDebug("Key pause game clicked");
                gameTimer.Pause();
                state.NextState(List_State::Pause);
                sound.StartPauseMusic();
                state.updateInterface(gameTimer, gui, window, state, json, sound, waveManager);
            }
            else if(state.getState() == List_State::Pause){
                lDebug("Key resume game clicked");
                sound.SoundClickBack();
                menuPanel::removePanel(gui);
                state.NextState(List_State::Game);
                sound.restoreLastMusic();
                gameTimer.Start();
            }
            else if(state.getState() != List_State::MapEditor && state.getState() != List_State::Main_Menu){
                state.NextState(List_State::Zero);
                sound.SoundClickBack();
                state.updateInterface(gameTimer, gui, window, state, json, sound, waveManager);
            }
        }
        else if(event.key.code == json.keys["Mute"] && state.getState() != List_State::Settings && state.getState() != List_State::Pause){
            json.setting["mute"] = json.setting["mute"] == false;
            sound.setSound(json.setting["mute"], json.setting["music"], json.setting["sound"], json.setting["system"]);
            json.saveSettings();
        }
        else if(json.event.key.code == json.keys["Info"]){
            json.showFPS = !json.showFPS;
        }
    }
}


///From: Game::Game()
///Function: Move map view
void MapEvents::moveView(bool view_Locked, sf::RenderWindow &window, StateMachine &state, Settings &json, std::vector<tgui::Panel::Ptr> &panels, tgui::Gui &gui) {

    if (!view_Locked && (state.getState() == List_State::MapEditor || state.getState() == List_State::Game)) {

        sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
        int focusValue = getViewFocused(panels,true, pixelPosition, json, state, window, gui);
        if(focusValue == FOCUSED_TGUI) return;

        float   moveSpeedWidth = 0.0f,
                moveSpeedHeight = 0.0f,
                speed = json.setting["viewSpeed"],
                height = json.map["height"],
                width = json.map["width"],
                settingTilesOut = json.setting["tilesOut"],
                maxTilesOut = Tile_Size*settingTilesOut;     //Max Tiles out

        sf::Vector2f viewMin = json.view["main"].getCenter() - (json.view["main"].getSize() / 2.0f);
        sf::Vector2f viewMax = viewMin + json.view["main"].getSize();

        if (sf::Keyboard::isKeyPressed(json.keys["Right"])) {

            float max = (width*Tile_Size+maxTilesOut);

            if(speed < max-viewMax.x)
                moveSpeedWidth = speed;
            else if(max > viewMax.x){
                moveSpeedWidth = max-viewMax.x;
            }
        }

        else if (sf::Keyboard::isKeyPressed(json.keys["Left"])) {

            float min = (width*Tile_Size) - (width*Tile_Size+maxTilesOut);

            if(speed < viewMin.x-min)
                moveSpeedWidth = -speed;
            else if(min < viewMin.x){
                moveSpeedWidth = min-viewMin.x;
            }
        }

        if (sf::Keyboard::isKeyPressed(json.keys["Up"])) {

            float min = (height*Tile_Size) - (height*Tile_Size+maxTilesOut);

            if(speed < viewMin.y-min)
                moveSpeedHeight = -speed;
            else if(min < viewMin.y){
                moveSpeedHeight = min-viewMin.y;
            }
        }

        else if (sf::Keyboard::isKeyPressed(json.keys["Down"])) {

            float max = (height*Tile_Size+maxTilesOut);
            if(state.getState() == List_State::Game) max = (height * Tile_Size + maxTilesOut) +(window.getSize().y/4.0f);
            if(speed < max-viewMax.y)
                moveSpeedHeight = speed;
            else if(max > viewMax.y){
                moveSpeedHeight = max-viewMax.y;
            }
        }

        json.view["main"].move(moveSpeedWidth, moveSpeedHeight);
        window.setView(json.view["main"]);
    }
}


///From: Game::Game
///Function: Handle all click events in all views that is not related to tgui
void MapEvents::clickEvent(Player &player,WaveManager &waveManager,HUD &hud,bool &placedTowerSelected,std::vector<Tower> &towersPlaced,std::string &towerSelected,std::vector<tgui::Panel::Ptr> &panels, sf::VertexArray &mapTiles, sf::VertexArray &bitTiles, sf::Event &event, StateMachine &state, Settings &json, sf::RenderWindow &window, tgui::Gui &gui) {

    if(state.getState() == List_State::MapEditor || state.getState() == List_State::Game) {

        sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
        sf::Vector2f gamePosition = window.mapPixelToCoords(pixelPosition);

        int focusValue = getViewFocused(panels,false,pixelPosition,json,state,window, gui);

        if(state.getState() == List_State::MapEditor){
            getMouseTilePositionInformation(gamePosition,json, gui);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


            if (focusValue == FOCUSED_MINIMAP) {
                window.setView(json.view["map"]);
                pixelPosition = sf::Mouse::getPosition(window);
                gamePosition = window.mapPixelToCoords(pixelPosition);
                clickEventMiniMap(gamePosition,json);
                window.setView(json.view["main"]);
            }

            //Only left click action in editor state
            if (state.getState() == List_State::MapEditor) {

                if(focusValue == FOCUSED_MAP) {

                    if(json.editor["drawable"]) {
                        unsigned int draw = json.editor["draw"];
                        drawSelectedTileToPosition(mapTiles, gamePosition.x, gamePosition.y, draw, json, window);
                    }
                    else{

                    }
                }
            }


                //Only click action in game state
            else if(state.getState() == List_State::Game){

                if(focusValue == FOCUSED_MAP) {
                    tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
                    tgui::Panel::Ptr selectionPicturePanel = gui.get<tgui::Panel>("selectionPicturePanel", true);
                    tgui::Panel::Ptr selectionInfoPanel = gui.get<tgui::Panel>("selectionInfoPanel", true);
                    selectionPicturePanel->removeAllWidgets();
                    selectionInfoPanel->removeAllWidgets();

                    tgui::Picture::Ptr frame = tgui::Picture::create(json.texture["miniMapFrame"],false);



                    //
                    if (mf::getBitTileFocusedValue(gamePosition, json) == FOCUSED_MINIMAP) {
                        for (auto &i : towersPlaced) {
                            i.isSelected = false;
                        }
                        bool towerWasSelected = false;
                        for (int i = 0; i < towersPlaced.size(); i++) {
                            if (gamePosition.x > towersPlaced[i].coordinates.getBounds().left &&
                                gamePosition.x < (towersPlaced[i].coordinates.getBounds().left +
                                                  towersPlaced[i].coordinates.getBounds().width) &&
                                gamePosition.y > towersPlaced[i].coordinates.getBounds().top &&
                                gamePosition.y < (towersPlaced[i].coordinates.getBounds().top +
                                                  towersPlaced[i].coordinates.getBounds().height)) {


                                tgui::Picture::Ptr towerPic = tgui::Picture::create(
                                        json.texture[towersPlaced[i].towerType], false);
                               // std::cout << towersPlaced[i].towerType << std::endl;
                                towerPic->setSize(selectionPicturePanel->getSize().x*0.8f,selectionPicturePanel->getSize().x*0.8f);
                                towerPic->setPosition(selectionPicturePanel->getSize().x*0.1f,selectionPicturePanel->getSize().x*0.1f);
                                towerPic->moveToFront();
                                frame->setSize(towerPic->getSize());
                                frame->setPosition(towerPic->getPosition());

                                selectionPicturePanel->add(towerPic);
                                selectionPicturePanel->add(frame);
                                towersPlaced[i].isSelected = true;
                                placedTowerSelected = true;
                                // Add a whole info panel here with the info
                                tgui::Label::Ptr label = theme->load("Label");
                                label->setText(towersPlaced[i].towerName);
                                label->setTextSize(24);
                                label->setPosition(selectionInfoPanel->getSize().x*0.5f-label->getSize().x/2,selectionInfoPanel->getSize().y*0.1f);
                                label->setPosition(tgui::bindWidth(selectionInfoPanel)*0.5f - tgui::bindWidth(label)*0.5f,tgui::bindHeight(selectionInfoPanel)*0.1f);
                                selectionInfoPanel->add(label);

                                frame = tgui::Picture::create(json.texture["miniMapFrame"],false);
                                tgui::Picture::Ptr bulletPic = tgui::Picture::create(
                                        json.texture[towersPlaced[i].bulletType], false);
                                // std::cout << towersPlaced[i].towerType << std::endl;
                                bulletPic->setSize(50*(1280/window.getSize().x),50*(1280/window.getSize().x));
                                bulletPic->setPosition(selectionInfoPanel->getSize().x*0.1f,label->getPosition().y+label->getSize().y);
                                bulletPic->moveToFront();
                                frame->setSize(bulletPic->getSize());
                                frame->setPosition(bulletPic->getPosition());
                                selectionInfoPanel->add(bulletPic);
                                selectionInfoPanel->add(frame);

                                tgui::Label::Ptr label2 = theme->load("Label");
                                label2->setText("Damage: " + std::to_string(towersPlaced[i].damage));
                                label2->setTextSize(16);
                                label2->setPosition(frame->getPosition().x + frame->getSize().x + frame->getSize().x*+0.1f,(frame->getPosition().y+(frame->getSize().y/2))-label->getSize().y/3);
                                selectionInfoPanel->add(label2);

                                tgui::Label::Ptr label3 = theme->load("Label");
                                label3->setText("Firerate: " +  std::to_string(towersPlaced[i].fireRate));
                                label3->setTextSize(16);
                                label3->setPosition(label2->getPosition().x,(label2->getPosition().y+(frame->getSize().y/2)));
                                selectionInfoPanel->add(label3);

                                tgui::Label::Ptr label4 = theme->load("Label");
                                label4->setText("Range: " + std::to_string((int)towersPlaced[i].range));
                                label4->setTextSize(16);
                                label4->setPosition(label3->getPosition().x,(label3->getPosition().y+(frame->getSize().y/2)));
                                selectionInfoPanel->add(label4);

                                player.setSelected(false);
                                hud.setPlayerSelected(nullptr);
                                hud.setMonsterSelected(nullptr);
                                hud.setTowerSelected(&towersPlaced[i]);
                                towerWasSelected = true;
                                break;

                                /*tgui::Picture::Ptr selectionPic = tgui::Picture::create(json.texture["tower_1"],false);
                                selectPanel->add(selectionPic, "selected");*/
                            }
                        }
                    }else{
                        for (auto &i : towersPlaced) {
                            i.isSelected = false;
                        }
                        bool monsterWasSelected = false;
                        std::list<Monster*> activeMonsters = waveManager.getActiveMonsters();
                        for(auto &Monster : activeMonsters){
                            Monster->isSelected = false;
                        }

                        for (auto &Monster : activeMonsters) {
                            if (gamePosition.x > Monster->sprite.getGlobalBounds().left &&
                                gamePosition.x < (Monster->sprite.getGlobalBounds().left +
                                                  Monster->sprite.getGlobalBounds().width) &&
                                gamePosition.y > Monster->sprite.getGlobalBounds().top &&
                                gamePosition.y < (Monster->sprite.getGlobalBounds().top +
                                                  Monster->sprite.getGlobalBounds().height)) {


                                tgui::Texture tex(json.texture[Monster->monsterType.getClassName()], sf::IntRect(json.texture[Monster->monsterType.getClassName()].getSize().x/4, 0, json.texture[Monster->monsterType.getClassName()].getSize().x/4, json.texture[Monster->monsterType.getClassName()].getSize().y/4), sf::IntRect());
                                tgui::Picture::Ptr monsterPic = tgui::Picture::create(
                                        tex, false);
                                // std::cout << towersPlaced[i].towerType << std::endl;
                                monsterPic->setSize(selectionPicturePanel->getSize().x*0.8f,selectionPicturePanel->getSize().x*0.8f);
                                monsterPic->setPosition(selectionPicturePanel->getSize().x*0.1f,selectionPicturePanel->getSize().x*0.1f);
                                monsterPic->moveToFront();
                                frame->setSize(monsterPic->getSize());
                                frame->setPosition(monsterPic->getPosition());

                                selectionPicturePanel->add(monsterPic);
                                selectionPicturePanel->add(frame);
                                // Add a whole info panel here with the info
                                tgui::Label::Ptr label = theme->load("Label");
                                label->setText(Monster->monsterType.getClassName());
                                label->setTextSize(24);
                                label->setPosition(tgui::bindWidth(selectionInfoPanel)*0.5f - tgui::bindWidth(label)*0.5f,tgui::bindHeight(selectionInfoPanel)*0.1f);
                                selectionInfoPanel->add(label);

                                tgui::Label::Ptr label2 = theme->load("Label");
                                label2->setText("Damage: " + std::to_string(Monster->damage));
                                label2->setTextSize(16);
                                label2->setPosition(selectionInfoPanel->getSize().x*0.2f,label->getPosition().y + label->getSize().y + selectionInfoPanel->getSize().y*0.1f);
                                selectionInfoPanel->add(label2);

                                tgui::Label::Ptr label3 = theme->load("Label");
                                std::stringstream stream;
                                stream << std::fixed << std::setprecision(1) << Monster->speed;
                                std::string s = stream.str();
                                label3->setText("Speed: " + s);
                                label3->setTextSize(16);
                                label3->setPosition(label2->getPosition().x,label2->getPosition().y + label2->getSize().y + selectionInfoPanel->getSize().y*0.1f);
                                selectionInfoPanel->add(label3);

                                placedTowerSelected = false;
                                player.setSelected(true);
                                hud.setPlayerSelected(nullptr);
                                hud.setMonsterSelected(Monster);
                                hud.setTowerSelected(nullptr);
                                monsterWasSelected = true;
                                Monster->isSelected = true;
                                break;
                            }
                        }
                        if(!monsterWasSelected) {
                            selectionPicturePanel->removeAllWidgets();
                            selectionInfoPanel->removeAllWidgets();
                            placedTowerSelected = false;
                            hud.setPlayerSelected(&player);
                            hud.setMonsterSelected(nullptr);
                            hud.setTowerSelected(nullptr);
                            player.setSelected(false);
                        }
                    }

                    if (!towerSelected.empty()) {
                        unsigned int towerX_Size = 4;
                        unsigned int towerY_size = 4;
                        drawToBitLayer(player,towersPlaced, bitTiles, gamePosition, towerX_Size, towerY_size, towerSelected, json,
                                       window);
                        towerSelected = "";
                        json.highlight = false;
                    }
                }


                if(focusValue == 4){ // For clicking in inside the hud

                }
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if (state.getState() == List_State::MapEditor) {
                if(focusValue == FOCUSED_MAP) {
                    mef::setTileClickInfo(gamePosition,json);
                    tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("selectedTileChildWindow");
                    EditorChildWindows editorChildWindows; //Move update to map functions later
                    if(childWindow != nullptr){
                        editorChildWindows.updateSelectedTileChildWindow(gui,json);
                    }else{
                        editorChildWindows.getSelectedTileChildWindow(gui,window,json);
                    }
                }
            }
            if (state.getState() == List_State::Game) {

                /*if(!player.getBuildingQueue().empty()){
                    player.setBusy(false);
                    player.getBuildingQueue().erase(player.getBuildingQueue().begin());
                    std::cout << player.getBuildingQueue().size() << std::endl;

                    player.setPlayerTarget(gamePosition.x,gamePosition.y);
                    std::cout << "Right click" << std::endl;
                }else{
                    player.setPlayerTarget(gamePosition.x,gamePosition.y);
                    std::cout << "Right click" << std::endl;
                }*/

                // Clear the whole queue and set busy to false
                if(!player.getBuildingQueue().empty()) {
                    for(int i = 0;i < player.getBuildingQueue().size();i++){

                        int tempY = (int)player.getBuildingQueue().front().coordinates.getBounds().top / (Tile_Size / Bits_To_Tiles);
                        for (int i = 0; i < player.getBuildingQueue().front().h; ++i) {

                            int tempX = (int)player.getBuildingQueue().front().coordinates.getBounds().left / (Tile_Size / Bits_To_Tiles);

                            for (int j = 0; j < player.getBuildingQueue().front().w; ++j) {
                                json.bitTileValue[tempX][tempY] = 0;
                                mf::drawBitHighlightSpecifiedTile(bitTiles,sf::Vector2i(tempX,tempY),json);
                                tempX++;
                            }
                            tempY++;
                        }
                        player.addToGold(player.getBuildingQueue().front().buildingCost);
                        player.getBuildingQueue().pop();
                    }
                    player.setBusy(false);

                }

                // Set the player target to the gamePosition
                player.setPlayerTarget(gamePosition.x,gamePosition.y);


            }
        }
    }
}

void MapEvents::clickReleaseEvent(std::vector<tgui::Panel::Ptr> &panels, sf::VertexArray &mapTiles, sf::VertexArray &bitTiles, sf::Event &event, StateMachine &state, Settings &json, sf::RenderWindow &window, tgui::Gui &gui) {

    if(state.getState() == List_State::MapEditor /*|| state.getState() == List_State::Game*/) {

        sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
        sf::Vector2f gamePosition = window.mapPixelToCoords(pixelPosition);

        int focusValue = getViewFocused(panels,false,pixelPosition,json,state,window, gui);

    if(event.type == sf::Event::MouseButtonReleased) {

        if (event.mouseButton.button == sf::Mouse::Right) {

            if (state.getState() == List_State::MapEditor) {

                if (focusValue == FOCUSED_MAP) {

                    mef::setTileClickInfo(gamePosition, json);
                    tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("selectedTileChildWindow");
                    EditorChildWindows editorChildWindows; //Move update to map functions later

                        if (childWindow != nullptr) {
                            editorChildWindows.updateSelectedTileChildWindow(gui, json);
                        } else {
                            editorChildWindows.getSelectedTileChildWindow(gui, window, json);
                        }
                    }
                }
            }
        }
    }
}

/** ################################### PRIVATE ##################################################################### */


///From: MapEvents::clickEvent
///Function: change main view to the position clicked on in minimap
void MapEvents::clickEventMiniMap(sf::Vector2f &gamePosition, Settings &json) {

    sf::Vector2f sizeMap = sf::Vector2f(json.map["width"], json.map["height"]);

    float tileOutOfMap = json.setting["tilesOut"];

    //will only move X view if view.x are not max
    if(json.view["main"].getSize().x < (sizeMap.x * Tile_Size) + (tileOutOfMap * Tile_Size)) {

        //IF clicking outside max x
        if (gamePosition.x + json.view["main"].getSize().x / 2.0f > sizeMap.x * Tile_Size + (tileOutOfMap * Tile_Size)) {

            gamePosition.x = (sizeMap.x * Tile_Size - json.view["main"].getSize().x / 2.0f) + tileOutOfMap * Tile_Size;
        }
            //IF clicking outside min x
        else if (gamePosition.x - json.view["main"].getSize().x / 2.0f < -tileOutOfMap * Tile_Size) {

            gamePosition.x = (json.view["main"].getSize().x / 2.0f) - tileOutOfMap * Tile_Size;
        }
        json.view["main"].move(gamePosition.x - json.view["main"].getCenter().x, 0);
    }

    //will only move Y view if view.y are not max
    if(json.view["main"].getSize().y < (sizeMap.y * Tile_Size) + (tileOutOfMap * Tile_Size)) {

        //IF clicking outside max y
        if (gamePosition.y + (json.view["main"].getSize().y / 2.0f) > sizeMap.y * Tile_Size + (tileOutOfMap * Tile_Size)) {

            gamePosition.y = (sizeMap.y * Tile_Size - json.view["main"].getSize().y / 2.0f) + tileOutOfMap * Tile_Size;
        }

            //IF clicking outside min y
        else if (gamePosition.y - (json.view["main"].getSize().y / 2.0f) < -tileOutOfMap * Tile_Size) {

            gamePosition.y = (json.view["main"].getSize().y / 2.0f) - tileOutOfMap * Tile_Size;
        }
        json.view["main"].move(0, gamePosition.y - json.view["main"].getCenter().y);
    }
}


