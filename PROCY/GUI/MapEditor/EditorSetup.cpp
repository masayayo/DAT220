//
// Created by Chrim14 on 10.10.2017.
//

#include "EditorSetup.h"
#include "../../System/Map/MapStaticFunctions.h"
#include "../Menu/Menu.h"


/// A Class function that stores all values in editor setup state for mapeditor state
void EditorSetup::setNewMapValues(tgui::Gui &gui, Settings &json) {

    //Getting value
    std::string height = gui.get<tgui::EditBox>("height")->getText();
    std::string length = gui.get<tgui::EditBox>("length")->getText();
    std::string tile   = gui.get<tgui::ListBox>("tile")  ->getSelectedItemId();


    //Converting string to integer
    int intHeight = std::stoi(height);
    int intLength = std::stoi(length);
    int intTile   = std::stoi(tile);

    //Adding value to json edit memory
    json.editorSettings(intHeight, intLength, intTile, "new");//must be "new" for leather functions
}


///A class function that create all overlaying GUI in Editor Setup state
void EditorSetup::getEditorSetupMenu(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {


    try{

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        Menu::setBackground(gui);

        tgui::Button::Ptr bBack, bCreate, bLoad;

        std::string backString   = json.language["back"];
        std::string createString = json.language["create"];
        std::string loadString   = json.language["loadmap"];
        std::string newString    = json.language["newmap"];
        std::string heightString = json.language["height"];
        std::string lengthString = json.language["length"];
        std::string tileString = json.language["starttile"];


        ///BUTTON: BACK
        bBack = theme->load("Button");
        bBack ->setSize(windowWidth*0.15f, windowHeight*0.07f);
        bBack ->setPosition(windowWidth*0.01f, windowHeight*0.92f);
        bBack ->setText(sf::String::fromUtf8(backString.begin(), backString.end()));
        gui.add(bBack);


        ///BUTTON: CREATE SETTINGS
        bCreate = tgui::Button::copy(bBack);
        bCreate ->setPosition(windowWidth*0.32f, windowHeight*0.92f);
        bCreate ->setText(sf::String::fromUtf8(createString.begin(), createString.end()));
        gui.add(bCreate);

        FileHandler fileHandler;

        ///BUTTON: CREATE LOAD MAP
        bLoad = tgui::Button::copy(bBack);
        bLoad ->setPosition(windowWidth*0.53f, windowHeight*0.92f);
        bLoad ->setText(sf::String::fromUtf8(loadString.begin(), loadString.end()));
        bLoad ->disable();
        bLoad ->setOpacity(0.3f);
        bLoad ->connect("clicked", [&]() {
                    lDebug("Button load map clicked"),
                    sound.SoundClick(),
                    fileHandler.loadMap("list","",json,gui);
                    tgui::Label::Ptr errorLabel = gui.get<tgui::Label>("fileMessage");
                    std::string message = gui.get<tgui::Label>("fileMessage")->getText();
                    if(errorLabel != nullptr && message.empty()) {
                        fileHandler.refectorJsonInto2DArray(json);
                        std::string selectedMap = gui.get<tgui::ListBox>("list")->getSelectedItem();
                        if (selectedMap.empty()) selectedMap = "Map";
                        json.editorSettings(json.map["height"], json.map["width"], 1, selectedMap);
                        state.NextState(List_State::MapEditor),
                                state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
                    }
        });
        gui.add(bLoad, "bLoad");


        ///LISTBOX: LOAD MAP LIST
        tgui::ListBox::Ptr list;
        list = theme->load("ListBox");
        list->setSize(windowWidth*0.46f, windowHeight*0.81f);
        list->setPosition(windowWidth*0.53f, windowHeight*0.1f);
        list->connect("ItemSelected", [&]() {
                    gui.get<tgui::Button>("bLoad")->setOpacity(1.0f),
                    gui.get<tgui::Button>("bLoad")->enable();
        });
        list->setTextSize(20);
        gui.add(list, "list");

        fileHandler.getFiles("Texture/Maps", "list","", gui);


        //HARDCODED, for testing on linux and mac
        #ifdef _WIN32
        #else
        list->addItem("TEMP");
        #endif

        //load game label
        tgui::Label::Ptr label;
        label = theme->load("label");
        label->setPosition(windowWidth*0.53f, windowHeight*0.02f);
        label->setTextSize(30);
        label->setText(sf::String::fromUtf8(loadString.begin(), loadString.end()));
        gui.add(label);

        //error label
        tgui::Label::Ptr errorLabel;
        errorLabel = theme->load("label");
        errorLabel->setPosition(bLoad->getPosition().x + bLoad->getSize().x + 10, bLoad->getPosition().y + (bLoad->getSize().y/8));
        errorLabel->setTextSize(20);
        gui.add(errorLabel, "fileMessage");

        ///LISTBOX tile image
        tgui::ListBox::Ptr tileImage;
        tileImage = theme->load("ListBox");
        tileImage->setSize(windowWidth*0.09f, windowWidth*0.09f);
        tileImage->setPosition(windowWidth*0.01f, windowHeight*0.27f);
        gui.add(tileImage, "image");

        ///LISTBOX: SELECT START TILE
        tgui::ListBox::Ptr tile;
        tile = theme->load("ListBox");
        tile->setSize(windowWidth*0.46f, windowHeight*0.4f);
        tile->setPosition(windowWidth*0.01f, windowHeight*0.5f);

        getTileList("ground", tile, gui, json);

        tile->setTextSize(20);

        gui.add(tile, "tile");

        //start tile label
        label = theme->load("label");
        label->setPosition(windowWidth*0.01f, windowHeight*0.45f);
        label->setTextSize(24);
        label->setText(sf::String::fromUtf8(tileString.begin(), tileString.end()));
        gui.add(label);

        //New map label
        label = theme->load("label");
        label->setPosition(windowWidth*0.01f, windowHeight*0.02f);
        label->setTextSize(30);
        label->setText(sf::String::fromUtf8(newString.begin(), newString.end()));
        gui.add(label);

        tgui::EditBox::Ptr height, length;

        ///EDITBOX: LENGTH
        length = theme->load("EditBox");
        length->setSize(windowWidth*0.1f,windowHeight*0.05f);
        length->setPosition(windowWidth*0.01f,windowHeight*0.13f);
        length->setTextSize(15);
        length->setDefaultText("");
        length->setInputValidator("^[0-9]{0,4}$");
        gui.add(length, "length");
        //label height
        label = theme->load("label");
        label->setPosition(windowWidth*0.12f, windowHeight*0.135f);
        label->setTextSize(18);
        label->setText(sf::String::fromUtf8(lengthString.begin(), lengthString.end())+" [15,150]");
        gui.add(label);

        ///EDITBOX: HEIGHT
        height = theme->load("EditBox");
        height->setSize(windowWidth*0.1f,windowHeight*0.05f);
        height->setPosition(windowWidth*0.01f,windowHeight*0.20f);
        height->setTextSize(15);
        height->setDefaultText("");
        height->setInputValidator("^[0-9]{0,4}$");
        gui.add(height, "height");
        //label height
        label = theme->load("label");
        label->setPosition(windowWidth*0.12f, windowHeight*0.205f);
        label->setTextSize(18);
        label->setText(sf::String::fromUtf8(heightString.begin(), heightString.end())+"  [15,150]");
        gui.add(label);


        bBack->connect("clicked", [&]() {
                    lDebug("Button back clicked"),
                    sound.SoundClickBack(),
                    state.NextState(List_State::Zero),
                    state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
        });

        tile->connect("ItemSelected", [&]() {
            drawImage(false, false, gui, json);
        });

        bCreate->connect("clicked", [&]() {
                    lDebug("Button create clicked"),
                    sound.SoundClick();
                    tgui::EditBox::Ptr y = gui.get<tgui::EditBox>("height");
                    tgui::EditBox::Ptr x = gui.get<tgui::EditBox>("length");
                    tgui::ListBox::Ptr t = gui.get<tgui::ListBox>("tile");
                    if(y != nullptr && x != nullptr && t != nullptr){

                        std::string sHeight = y->getText();
                        std::string sWidth =  x->getText();
                        std::string tileSelected = t->getSelectedItem();

                        if(!sHeight.empty() && !sWidth.empty() && !tileSelected.empty()){

                            bool notInteger = false;

                            for(const auto& temp : sHeight){
                                if((int)temp < 58 && (int)temp > 47){}
                                else{
                                    notInteger = true;
                                    break;
                                }
                            }

                            for(const auto& temp : sWidth){
                                if((int)temp < 58 && (int)temp > 47){}
                                else{
                                    notInteger = true;
                                    break;
                                }
                            }

                            if(!notInteger){
                                int tempY = std::stoi(sHeight);
                                int tempX = std::stoi(sWidth);

                                if((tempX <= Layer_One_Size && tempX >= Layer_One_Size_Min) && (tempY <= Layer_One_Size && tempY >= Layer_One_Size_Min)){
                                            setNewMapValues(gui,json),
                                            json.setMapValues(),
                                            state.NextState(List_State::MapEditor),
                                            state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
                                }
                                else{
                                    lWarning("Creating new map, Size not match. size given: " + std::to_string(tempX) + ", " + std::to_string(tempY));
                                    //TODO: SIMEN legg in beskjed her
                                }
                            }
                            else{
                                lWarning("Creating new map, wrong value given: " + sWidth + ", " + sHeight);
                                //TODO: SIMEN legg in beskjed her
                            }
                        }
                        else{
                            lWarning("Creating new map, one or more value missing");
                            //TODO: SIMEN legg in beskjed her
                        }
                    }else{
                        lWarning("Creating new map, one or more tgui object got null pointer");
                        //TODO: SIMEN legg in beskjed her
                    }
        });
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}


/// A class function that create all overlaying GUI in Mapeditor state and connect all underlaying GUI
void EditorSetup::getEditorMenu(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    EditorChildWindows editorChildWindows;

    try{

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        tgui::Button::Ptr bBack, bCreate, bLoad;

        std::string menu1   = json.language["file"];
        std::string menu1_1 = json.language["load"];
        std::string menu1_2 = json.language["save"];
        std::string menu1_3 = json.language["exit"];

        menu1   = sf::String::fromUtf8(menu1.begin(),menu1.end());
        menu1_1 = sf::String::fromUtf8(menu1_1.begin(),menu1_1.end());
        menu1_2 = sf::String::fromUtf8(menu1_2.begin(),menu1_2.end());
        menu1_3 = sf::String::fromUtf8(menu1_3.begin(),menu1_3.end());

        tgui::MenuBar::Ptr menu = theme->load("MenuBar");
        menu->setSize((float)window.getSize().x, 22.f);
        menu->addMenu(menu1);
        menu->addMenuItem(menu1, menu1_1);
        menu->addMenuItem(menu1, menu1_2);
        menu->addMenuItem(menu1, menu1_3);
        menu->connect("MenuItemClicked", [&](const sf::String& item) {

            std::string temp_1 = json.language["load"];
            std::string temp_2 = json.language["save"];
            std::string temp_3 = json.language["exit"];

            temp_1 = sf::String::fromUtf8(temp_1.begin(),temp_1.end());
            temp_2 = sf::String::fromUtf8(temp_2.begin(),temp_2.end());
            temp_3 = sf::String::fromUtf8(temp_3.begin(),temp_3.end());

            if (item == temp_3){
                lDebug("Menu Bar, Exitting MapEditor");
                sound.SoundClickBack(),
                state.NextState(List_State::Zero);
                state.updateInterface(gameTimer,gui,window,state,json,sound, waveManager);
            }
            else if(item == temp_2){
                editorChildWindows.getSaveChildWindow(gui,window,json);

            }
            else if(item == temp_1){
                editorChildWindows.getLoadChildWindow(gui,window,json,state,sound);
            }
        });

        std::string tools = "Tools";
        menu->addMenu(tools);
        menu->addMenuItem(tools, "Tiles");
        menu->addMenuItem(tools, "Player/Monster menu");
        menu->addMenuItem(tools, "Hide information");
        menu->addMenuItem(tools, "Map description");

        menu->connect("MenuItemClicked", [&](const sf::String& item) {

            if (item == "Tiles"){
                lDebug("Menu Bar, opening tile menu");
                editorChildWindows.getTileChildMenu(gui, window, json);
            }
            else if (item == "Player/Monster menu"){
                editorChildWindows.getPlayerMonsterChildWindow(gui,window,json);
            }
            else if (item == "Map description"){
                editorChildWindows.getDescriptionChildWindow(gui,window,json);
            }
            if(gui.get<tgui::Label>("positionText") != nullptr){
                if(item == "Hide information"){
                    gui.get<tgui::MenuBar>("menu")->removeMenuItem("Tools", "Hide information");
                    gui.get<tgui::MenuBar>("menu")->addMenuItem("Tools", "Show information");
                    gui.remove(gui.get<tgui::Label>("positionText"));
                }
            }
            else if (item == "Show information"){
                gui.get<tgui::MenuBar>("menu")->removeMenuItem("Tools", "Show information");
                gui.get<tgui::MenuBar>("menu")->addMenuItem("Tools", "Hide information");
                editorChildWindows.getInformation(gui,window,json);
            }
        });

        editorChildWindows.getInformation(gui,window,json);
        gui.add(menu,"menu");


    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}


/// From: EditorSetup::getEditorSetupMenu() and EditorSetup::getTileChildMenu()
/// Function: Generation a list of tiles
void EditorSetup::getTileList(const std::string tileName, const tgui::ListBox::Ptr &tile, tgui::Gui &gui, Settings &json) {

    std::vector<std::string> terrainList = json.tiles[tileName];

    for (int i = 0; i < terrainList.size(); i += 2) {
        tile->addItem(terrainList[i+1],terrainList[i]);
    }
}


///From: EditorChildWindows::getTileChildMenu, EditorSetup::getEditorSetupMenu
/// A Class function used for drawing image of selected tile
void EditorSetup::drawImage(bool panel, bool childWindow, tgui::Gui &gui, Settings &json) {

    try{
        MapFunctions mapFunctions;
        sf::Texture texture;
        std::string tileUsed = "tiles.png";

        sf::Vector2i tileStart, tileSize;
        std::string tile;

        tgui::ListBox::Ptr tileWindow;
        tgui::ListBox::Ptr imageWindow;
        tgui::ChildWindow::Ptr cWindow;
        tgui::Panel::Ptr cPanel;
        unsigned int rotation;

        //child window only used in editor state
        if(childWindow){
            rotation = json.editor["rotate"];
            cWindow = gui.get<tgui::ChildWindow>("tileChildMenu");
            if(cWindow != nullptr){
                tileWindow = cWindow->get<tgui::ListBox>("list");
                imageWindow = cWindow->get<tgui::ListBox>("image");
                tile = tileWindow->getSelectedItemId();
            }
        }
        else if(panel){
            rotation = json.editor["rotate"];
            cWindow = gui.get<tgui::ChildWindow>("selectedTileChildWindow");
            if(cWindow != nullptr){
                cPanel = cWindow->get<tgui::Panel>("mainPanel");
                imageWindow = cPanel->get<tgui::ListBox>("imageFrame");
                int temp = mf::getTileIdValue(json.editor["tile_id"]);
                json.editor["rotate"] = mf::getTileRotationValue(json.editor["tile_id"]);
                tile = std::to_string(temp);
            }
        }
        else{
            tileWindow = gui.get<tgui::ListBox>("tile");
            imageWindow = gui.get<tgui::ListBox>("image");
            tile = tileWindow->getSelectedItemId();
        }

        auto intTile = std::stoul(tile);

        mapFunctions.getTileCoordinates(intTile, tileStart, tileSize, json);

        texture.loadFromFile("Texture/Texture/system/tiles.png", {tileStart.x,tileStart.y,tileSize.x,tileSize.y});

        json.image["image_icon"] = texture.copyToImage();

        for (int i = 0; i < json.editor["rotate"]; ++i) {
            json.image["image_icon"] = rotateImage90degree(json.image["image_icon"]);
        }

        texture.loadFromImage(json.image["image_icon"]);

        tgui::Picture::Ptr picture2 = tgui::Picture::create(texture);

        picture2->setPosition(
                imageWindow->getPosition().x + imageWindow->getSize().x * 0.1f,
                imageWindow->getPosition().y + imageWindow->getSize().y * 0.1f);

        picture2->setSize(
                imageWindow->getSize().x - imageWindow->getSize().x * 0.2f,
                imageWindow->getSize().y - imageWindow->getSize().y * 0.2f);

        if(panel){
            cPanel->add(picture2, "image2");
            json.editor["rotate"] = rotation;
        }
        else if(!childWindow)
            gui.add(picture2, "image");
        else
            cWindow->add(picture2, "image");
    }
    catch (...){
        lError("Tried to draw tile image, but no correct value given");
    }
}


/** A Class function used for getting tile lists in Tile Menu child window in MapEditor state
 * @param tileName The name of the tile list that needed to be drawn
 */
void EditorSetup::changeTileList(const std::string tileName, tgui::Gui &gui, Settings &json) {

    tgui::ListBox::Ptr tile = gui.get<tgui::ChildWindow>("tileChildMenu")->get<tgui::ListBox>("list");

    std::vector<std::string> terrainList = json.tiles[tileName];

    if(tile != nullptr) {
        tile->removeAllItems();
        json.editor["tileType"] = tileName; //Used when transforming to bitmap

        for (int i = 0; i < terrainList.size(); i += 2) {
            tile->addItem(terrainList[i + 1], terrainList[i]);
        }
    }
    else
        lError("Tried to change tile menu, but failed");
}


///From:
///Funtion: A Class function that take tile selected in TileMenu child window and store it for later use in a draw function
void EditorSetup::changeDrawTile(tgui::Gui &gui, Settings &json){

    std::string tile = gui.get<tgui::ChildWindow>("tileChildMenu")->get<tgui::ListBox>("list")->getSelectedItemId();

    try {
        int v = std::stoi(tile);

        json.editor["draw"] = v;
    } catch (...){
        lError("Tried to get tile id, no id found");
    }
}


///From: EditorSetup::drawImage
///Function: Taking a sf::Image and rotate it 90 degree
sf::Image EditorSetup::rotateImage90degree(const sf::Image &temp) {

    unsigned int maxY = temp.getSize().y;
    unsigned int maxX = temp.getSize().x;
    sf::Image val = temp;
    for (unsigned int x = 0; x < maxX; x++) {
        for (unsigned int y = 0; y < maxY; y++) {
            val.setPixel(maxY - y, x, temp.getPixel(x, y));
        }
    }
    return val;
}

