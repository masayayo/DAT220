//
// Created by Chrim14 on 10.10.2017.
//

#include "Map.h"
#include "MapStaticFunctions.h"


///From: Game::Game
///Function: create map and update map changes in views
void Map::mapHandler(sf::Shader &shader, Player &player,Timer &gameTimer,std::vector<Tower> &towersPlaced,std::string &towerSelected, sf::VertexArray &mapTiles, sf::VertexArray &bitTiles, StateMachine &state, sf::RenderWindow &window, Settings &json,sf::VertexArray &miniMapSquare, tgui::Gui &gui, Sound &sound,Paths& path, WaveManager &waveManager) {

    if (state.getState() == List_State::MapEditor || state.getState() == List_State::Game ||
        state.getState() == List_State::Pause) {

        if (!json.mapLoaded) {
            if (state.getState() == List_State::MapEditor) {
                json.view["map"].setViewport(sf::FloatRect(0.80f, 0.74f, 0.18f, 0.22f));
                lInfo("Starting MapEditor");
                if (json.editor["name"] == "new") CreateNewMap(json);
            } else if (state.getState() == List_State::Game) {
                //json.view["map"].setViewport(sf::FloatRect(0.01f, 0.72f, 0.25f, 0.25f));
                json.view["map"].setViewport(sf::FloatRect(0.01f, 0.68f, 0.23f, 0.30f));
                lInfo("Starting Game");
            }

            setView(json.view["main"], json);
            window.setView(json.view["main"]);
            getMap(mapTiles, bitTiles, json);
            setMiniMapView(window, json, miniMapSquare);
            towersPlaced.clear();

            if (state.getState() == List_State::Game) {
                mf::setBitMapHighlightPanel(bitTiles, json);
                Paths new_path;
                new_path.setPaths(json);
                path = new_path;
                waveManager.mapStart(json, path);
            }
            json.mapLoaded = true;
        }

        window.setView(json.view["main"]);

        window.draw(mapTiles, &json.texture["tiles"]);

        if (!towerSelected.empty()) json.highlight = true;
        if (json.highlight) window.draw(bitTiles);

        if (state.getState() == List_State::Pause) getMiniMapView(gui, window, json, mapTiles, miniMapSquare);
        if (state.getState() != List_State::MapEditor) gui.draw();
        if (state.getState() != List_State::Pause) getMiniMapView(gui, window, json, mapTiles, miniMapSquare);
        if (state.getState() == List_State::MapEditor) gui.draw();

        window.setView(json.view["main"]);
    }
    else if (state.getState() == List_State::New_Game && json.mapSelected) {
        if (!json.mapPreview) {
            getMap(mapTiles, bitTiles, json);
            setMiniMapView(window, json, miniMapSquare);
            json.mapPreview = true;
        }
        else {
            gui.draw();
            getMiniMapView(gui, window, json, mapTiles, miniMapSquare);
        }
    }
    else {
            gui.draw();
            json.mapLoaded = false;
        }
    }
/** ##################################### PROTECTED ##################################################################### */


///From: Map::clickEvent
///Function: Return a INT value after which view clicked on
int Map::getViewFocused(std::vector<tgui::Panel::Ptr> &panels,bool dynamical_focus, sf::Vector2i &pixelPosition, Settings &json, StateMachine &state, sf::RenderWindow &window, tgui::Gui &gui) {

    //IF the view excist in both states, like mini map
    if(state.getState() == List_State::MapEditor || state.getState() == List_State::Game) {

        //Checking if MiniMap is focused
        if(
                pixelPosition.y >= json.view["map"].getViewport().top*window.getSize().y &&
                pixelPosition.x >= json.view["map"].getViewport().left*window.getSize().x &&
                pixelPosition.y <= (json.view["map"].getViewport().top+json.view["map"].getViewport().height)*window.getSize().y &&
                pixelPosition.x <= (json.view["map"].getViewport().left+json.view["map"].getViewport().width)*window.getSize().x
                ){
            return 2;
        }

        // Check if the mouse is inside the hudView
        if(state.getState() == List_State::Game){
            for (auto &panel : panels) {
                tgui::Panel* temp = panel.get();

                if(pixelPosition.x >= temp->getAbsolutePosition().x &&
                   pixelPosition.x <= (temp->getSize().x + temp->getAbsolutePosition().x)&&
                   pixelPosition.y >= temp->getAbsolutePosition().y &&
                   pixelPosition.y <= (temp->getSize().y + temp->getAbsolutePosition().y)){
                    return 4;
                }

            }
        }

        //If the view only excist in Map editor, like child windows
        if(state.getState() == List_State::MapEditor){

            try{
                tgui::MenuBar::Ptr toolbar = gui.get<tgui::MenuBar>("menu");

                if (toolbar != nullptr) {
                    if(!dynamical_focus && toolbar->isFocused()) return 3;
                    if( pixelPosition.y < toolbar->getSize().y){
                        return 3;
                    }
                }
            } catch (...) {
                lError("Tried to check if TGUI focused, failed");
            }

            std::vector<std::string> list = {"tileChildMenu", "saveChildMenu", "loadChildMenu", "pmChildMenu", "changeTileChildMenu", "selectedTileChildWindow", "description"};

            for (const auto& temp : list) {
                try {
                    tgui::ChildWindow::Ptr menu = gui.get<tgui::ChildWindow>(temp);

                    if (menu != nullptr) {
                        //if (!dynamical_focus && menu->isFocused()) return 3;
                        if (pixelPosition.x >= menu->getPosition().x &&
                                 pixelPosition.x <= menu->getPosition().x + menu->getSize().x &&
                                 pixelPosition.y >= menu->getPosition().y &&
                                 pixelPosition.y <= menu->getPosition().y + menu->getSize().y+30) {
                            return 3;
                        }
                    }
                }
                catch (...) {
                    lError("Tried to check if TGUI child window was focused, failed on: "+temp);
                }
            }
        }
    }
    return 1;
}


/** ################################### PRIVATE ##################################################################### */


///From: Map::mapHandler
///Function: Setting the start view, max view and view center
void Map::setView(sf::View &view, Settings &json) {

    float height = json.map["height"];
    float width = json.map["width"];
    float centerHeight = (height*Tile_Size)/2;
    float centerWidth = (width*Tile_Size)/2;
    float minSize = 10.0f;



    if(height <= minSize || width <= minSize){
            view.setSize(sf::Vector2f((minSize*Tile_Size)*(16.f/9.f),(minSize*Tile_Size)));
            view.setCenter(centerWidth,centerHeight);

    }
    else{
        float temp = json.setting["startView"];

        //error handling if someone alter the "startView" number in file
        if(temp < minSize) temp = minSize;
        else if(temp > Layer_One_Size) temp = Layer_One_Size;

        view.setSize(sf::Vector2f((temp*Tile_Size)*(16.f/9.f),(temp*Tile_Size)));


        //TODO: Add player center position here
        view.setCenter(centerWidth,centerHeight);
    }
}


///From: Map::mapHandler
///Function: initialize the MiniMap view
void Map::setMiniMapView(sf::RenderWindow &window, Settings &json,sf::VertexArray &miniMapSquare) {

    float height = json.map["height"];
    float width = json.map["width"];
    float max;

    if(height > width)
        max = height;
    else
        max = width;

    float length = max * Tile_Size;

    json.view["map"].setSize(sf::Vector2f(length,length));
    json.view["map"].setCenter(sf::Vector2f(length/2.0f,length/2.0f));

    if(height > width){
        max = height-width;

        max = max / 2.0f;
        length = max * Tile_Size;
        json.view["map"].move(-length, 0);
    } else{
        max = width-height;

        max = max / 2.0f;
        length = max * Tile_Size;
        json.view["map"].move(0,-length);
    }

    sf::Vector2f viewMin = json.view["main"].getCenter() - (json.view["main"].getSize() / 2.0f);
    sf::Vector2f viewMax = viewMin + json.view["main"].getSize();
    if(json.mapLoaded) {
        miniMapSquare[0].position = sf::Vector2f(viewMin.x + 1, viewMin.y + 1);
        miniMapSquare[1].position = sf::Vector2f(viewMax.x, viewMin.y + 1);
        miniMapSquare[2].position = sf::Vector2f(viewMax.x, viewMax.y - 1);
        miniMapSquare[3].position = sf::Vector2f(viewMin.x + 1, viewMax.y - 1);
        miniMapSquare[4].position = sf::Vector2f(viewMin.x + 1, viewMin.y + 1);

    for (int i = 0; i <= 4; ++i) {
        miniMapSquare[i].color = sf::Color::Yellow;
    }
    }
}


///From: Map::mapHandler
///Function: Drawing the MiniMap view
void Map::getMiniMapView(tgui::Gui &gui,sf::RenderWindow &window, Settings &json, sf::VertexArray &mapTiles,sf::VertexArray &miniMapSquare) {

    sf::RectangleShape rectangle(sf::Vector2f(Layer_One_Size*Tile_Size*2,Layer_One_Size*Tile_Size*2));
    rectangle.setPosition(-(signed)(Layer_One_Size*Tile_Size),-(signed)(Layer_One_Size*Tile_Size));
    rectangle.setFillColor(sf::Color(0, 0, 0));

    sf::Vector2f viewMin = json.view["main"].getCenter() - (json.view["main"].getSize() / 2.0f);
    sf::Vector2f viewMax = viewMin + json.view["main"].getSize();

    if(json.mapLoaded) {
        miniMapSquare[0].position = sf::Vector2f(viewMin.x + 1, viewMin.y + 1);
        miniMapSquare[1].position = sf::Vector2f(viewMax.x, viewMin.y + 1);
        miniMapSquare[2].position = sf::Vector2f(viewMax.x, viewMax.y - 1);
        miniMapSquare[3].position = sf::Vector2f(viewMin.x + 1, viewMax.y - 1);
        miniMapSquare[4].position = sf::Vector2f(viewMin.x + 1, viewMin.y + 1);
    }

    float height = json.view["hud"].getSize().y;
    float width = json.view["hud"].getSize().x;
    //0.01f,0.72f,0.25f,0.25f
    sf::RectangleShape frame(sf::Vector2f(json.view["map"].getViewport().width*width,json.view["map"].getViewport().height*height));
    frame.setPosition(sf::Vector2f(json.view["map"].getViewport().left*width,json.view["map"].getViewport().top*height));
    frame.setTexture(&json.texture["miniMapFrame"]);

    if(!json.mapImage || json.mapLoaded) {
        window.setView(json.view["map"]);
        window.draw(rectangle);
        window.draw(mapTiles, &json.texture["tiles"]);
    }

    if(json.mapLoaded) window.draw(miniMapSquare);
    window.setView(json.view["hud"]);
    window.draw(frame);
}


///From: Map::mapHandler
///Function: Drawing up all map tiles
void Map::getMap(sf::VertexArray &mapTiles, sf::VertexArray &bitTiles, Settings &json) {

    const size_t width = json.map["width"];
    const size_t height = json.map["height"];

    //clearing VerexArrays to prevent old data
    mapTiles.clear();
    mapTiles.resize(width*height*4);

    bitTiles.clear();
    bitTiles.resize(width*Bits_To_Tiles*height*Bits_To_Tiles*4);


    sf::Vector2i tileStart, tileSize;

    int counter = 0;
    int tempY = 0;

    for (int y = 0; y < height; ++y) {
        int tempX = 0;
        for (int x = 0; x < width; ++x) {

            unsigned int tile = json.tileValue[x][y];

            getTileCoordinates(tile, tileStart, tileSize, json);

            mapTiles[counter].position = sf::Vector2f(tempX, tempY);
            mapTiles[counter + 1].position = sf::Vector2f(tempX + Tile_Size, tempY);
            mapTiles[counter + 2].position = sf::Vector2f(tempX + Tile_Size, tempY + Tile_Size);
            mapTiles[counter + 3].position = sf::Vector2f(tempX, tempY + Tile_Size);

            if((((tile >> 31) & 1) && ((tile >> 30) & 1)) || (!((tile >> 31) & 1) && !((tile >> 30) & 1))) {
                mapTiles[counter].texCoords = sf::Vector2f(tileStart.x, tileStart.y);
                mapTiles[counter + 1].texCoords = sf::Vector2f(tileStart.x + tileSize.x, tileStart.y);
                mapTiles[counter + 2].texCoords = sf::Vector2f(tileStart.x + tileSize.x, tileStart.y + tileSize.y);
                mapTiles[counter + 3].texCoords = sf::Vector2f(tileStart.x, tileStart.y + tileSize.y);
            }
            else {
                mapTiles[counter].texCoords = sf::Vector2f(tileStart.x, tileStart.y);
                mapTiles[counter + 1].texCoords = sf::Vector2f(tileStart.x, tileStart.y + tileSize.y);
                mapTiles[counter + 2].texCoords = sf::Vector2f(tileStart.x + tileSize.x, tileStart.y + tileSize.y);
                mapTiles[counter + 3].texCoords = sf::Vector2f(tileStart.x + tileSize.x, tileStart.y);
            }
            counter += 4;
            tempX += Tile_Size;
        }
        tempY += Tile_Size;
    }
}


///From: Map::mapHandler
///Function: Fills a 2D array with information about what tile is there
void Map::CreateNewMap(Settings &json) {

    size_t startTile = json.editor["tile"];

    memset(json.bitTileValue,0, sizeof(json.bitTileValue));

    for (auto &i : json.tileValue) {
        for (unsigned int &j : i) {
            j = (unsigned int) startTile;
        }
    }
}



