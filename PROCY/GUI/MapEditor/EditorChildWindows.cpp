//
// Created by Chrim14 on 31.10.2017.
//

#include "EditorChildWindows.h"
#include "../../System/Map/MapStaticFunctions.h"
#include "../../System/MapEditor/MapEditorStaticFunctions.h"
#include "EditorStaticGuiFunctions.h"

#define selectedTileChildWindow "selectedTileChildWindow"
#define Transparency 0.5f

/// From: EditorSetup::getEditorSetupMenu
/// A Class function that create a child window for all tiles in Mapeditor state
void EditorChildWindows::getTileChildMenu(tgui::Gui &gui, sf::RenderWindow &window, Settings &json) {

    EditorSetup editorSetup;

    try {
        tgui::ChildWindow::Ptr tileChildMenu = gui.get<tgui::ChildWindow>("tileChildMenu");
        if (tileChildMenu == nullptr) {

            tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

            float mHeight = gui.get<tgui::MenuBar>("menu")->getSize().y;

            //Creating the child window
            tileChildMenu = theme->load("ChildWindow");
            tileChildMenu->setSize(200, 306);
            tileChildMenu->setPosition(windowWidth - tileChildMenu->getSize().x, mHeight);
            tileChildMenu->setTitle("Tile Menu");


            //Creating all buttons needed
            tgui::Button::Ptr bGround, bRoad, bSpawn, bDestination, bTeleport, bDecorate, bRotateRight, bRotateLeft;

            bRotateRight = theme->load("Button");
            bRotateRight->setSize(30, 30);
            bRotateRight->setPosition(tileChildMenu->getSize().x * 0.05f, 50);
            bRotateRight->setText("->");

            bRotateLeft = tgui::Button::copy(bRotateRight);
            bRotateLeft->setPosition(tileChildMenu->getSize().x * 0.05f, 20);
            bRotateLeft->setText("<-");

            bGround = theme->load("Button");
            bGround->setSize(tileChildMenu->getSize().x * 0.48f, 17);
            bGround->setPosition(tileChildMenu->getSize().x * 0.01f, 240);
            bGround->setText("Ground");

            bRoad = tgui::Button::copy(bGround);
            bRoad->setPosition(tileChildMenu->getSize().x * 0.51f, 240);
            bRoad->setText("Road");

            bSpawn = tgui::Button::copy(bGround);
            bSpawn->setPosition(tileChildMenu->getSize().x * 0.01f, 262);
            bSpawn->setText("Spawn");

            bDestination = tgui::Button::copy(bSpawn);
            bDestination->setPosition(tileChildMenu->getSize().x * 0.51f, 262);
            bDestination->setText("Destination");

            bTeleport = tgui::Button::copy(bGround);
            bTeleport->setPosition(tileChildMenu->getSize().x * 0.01f, 284);
            bTeleport->setText("Teleport");

            bDecorate = tgui::Button::copy(bSpawn);
            bDecorate->setPosition(tileChildMenu->getSize().x * 0.51f, 284);
            bDecorate->setText("Decorate");


            tgui::ListBox::Ptr list;
            list = theme->load("ListBox");
            list->setSize(tileChildMenu->getSize().x, 150);
            list->setPosition(0, 85);

            ///LISTBOX tile image
            tgui::ListBox::Ptr tileImage;
            tileImage = theme->load("ListBox");
            tileImage->setSize(75, 75);
            tileImage->setPosition(63, 5);

            editorSetup.getTileList("ground", list, gui, json);

            tileChildMenu->add(bRotateRight, "bRotateRight");
            tileChildMenu->add(bRotateLeft, "bRotateLeft");
            tileChildMenu->add(bGround, "bGround");
            tileChildMenu->add(bRoad, "bRoad");
            tileChildMenu->add(bSpawn, "bSpawn");
            tileChildMenu->add(bDestination, "bDestination");
            tileChildMenu->add(bTeleport, "bTeleport");
            tileChildMenu->add(bDecorate, "bDecorate");
            tileChildMenu->add(list, "list");
            tileChildMenu->add(tileImage, "image");

            gui.add(tileChildMenu, "tileChildMenu");

            list->connect("ItemSelected", [&]() {
                editorSetup.changeDrawTile(gui, json);
                editorSetup.drawImage(false, true, gui, json);
            });
            bGround->connect("clicked", [&]() {
                editorSetup.changeTileList("ground", gui, json);

            });

            bRoad->connect("clicked", [&]() {
                editorSetup.changeTileList("road", gui, json);

            });

            bSpawn->connect("clicked", [&]() {
                editorSetup.changeTileList("spawn", gui, json);

            });

            bDestination->connect("clicked", [&]() {
                editorSetup.changeTileList("destination", gui, json);

            });

            bDecorate->connect("clicked", [&]() {
                editorSetup.changeTileList("decorate", gui, json);

            });

            bTeleport->connect("clicked", [&]() {
                editorSetup.changeTileList("teleport", gui, json);

            });

            bRotateRight->connect("clicked", [&]() {
                int temp = json.editor["rotate"];
                if (temp >= 3)
                    temp = 0;
                else
                    temp++;
                json.editor["rotate"] = temp;
                editorSetup.drawImage(false, true, gui, json);
            });

            bRotateLeft->connect("clicked", [&]() {
                int temp = json.editor["rotate"];
                if (temp <= 0)
                    temp = 3;
                else
                    temp--;
                json.editor["rotate"] = temp;
                editorSetup.drawImage(false, true, gui, json);
            });
        }
    }
    catch (const tgui::Exception& e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}


/// From: EditorSetup::getEditorSetupMenu
/// Function: Creating a child window for map saving
void EditorChildWindows::getSaveChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json) {

    try {
        tgui::ChildWindow::Ptr tileChildMenu = gui.get<tgui::ChildWindow>("saveChildMenu");
        if (tileChildMenu == nullptr) {

            tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

            float mHeight = gui.get<tgui::MenuBar>("menu")->getSize().y;

            std::string bListString = json.language["findFile"];
            std::string bSaveString = json.language["saveFile"];
            std::string eSaveString = json.language["editText"];
            std::string menuString = json.language["menu"];
            std::string saveString = json.language["save"];

            menuString = sf::String::fromUtf8(saveString.begin(), saveString.end()) + " " +
                         sf::String::fromUtf8(menuString.begin(), menuString.end());

            //Creating the child window
            tgui::ChildWindow::Ptr saveChildMenu = theme->load("ChildWindow");
            saveChildMenu->setSize(300, 90);
            saveChildMenu->setPosition((window.getSize().x / 2) - (saveChildMenu->getSize().x / 2),
                                       (window.getSize().y / 2) - (saveChildMenu->getSize().y));
            saveChildMenu->setTitle(menuString);


            //Creating all button needed
            tgui::Button::Ptr bSave, bList;

            bSave = theme->load("Button");
            bSave->setSize(saveChildMenu->getSize().x * 0.45f, 20);
            bSave->setPosition(saveChildMenu->getSize().x * 0.525f, saveChildMenu->getSize().y * 0.7f);
            bSave->setText(sf::String::fromUtf8(bSaveString.begin(), bSaveString.end()));

            bList = tgui::Button::copy(bSave);
            bList->setPosition(saveChildMenu->getSize().x * 0.025f, saveChildMenu->getSize().y * 0.7f);
            bList->setText(sf::String::fromUtf8(bListString.begin(), bListString.end()));


            //Creating the edit box
            tgui::EditBox::Ptr eSave;
            eSave = theme->load("EditBox");
            eSave->setSize(saveChildMenu->getSize().x * 0.9f, mHeight);
            eSave->setPosition(saveChildMenu->getSize().x * 0.05f, saveChildMenu->getSize().y * 0.10f);
            eSave->setDefaultText(sf::String::fromUtf8(eSaveString.begin(), eSaveString.end()));


            tgui::Label::Ptr label;
            label = theme->load("label");
            label->setTextSize(15);
            label->setPosition(eSave->getPosition().x, eSave->getSize().y + eSave->getPosition().y + 5.f);


            tgui::ListBox::Ptr list = theme->load("ListBox");
            list->hide();

            saveChildMenu->add(bList, "bList");
            saveChildMenu->add(bSave, "bSave");
            saveChildMenu->add(eSave, "eSave");
            saveChildMenu->add(label, "fileMessage");
            saveChildMenu->add(list, "list");
            gui.add(saveChildMenu, "saveChildMenu");

            FileHandler fileHandler;

            bSave->connect("clicked", [&]() {
                tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("saveChildMenu");
                if (childWindow != nullptr) {
                    std::string file1 = childWindow->get<tgui::EditBox>("eSave")->getText();
                    std::string file2 = childWindow->get<tgui::ListBox>("list")->getSelectedItem();
                    if (file1.empty() && !file2.empty()) {
                        fileHandler.saveMap(file2, json, gui);
                    } else if (!file1.empty() && file2.empty()) {
                        fileHandler.saveMap(file1, json, gui);
                    } else {
                        tgui::Label::Ptr temp = childWindow->get<tgui::Label>("fileMessage");
                        if (temp != nullptr) {
                            if (!file1.empty() && !file2.empty()) {
                                temp->setTextColor(sf::Color(255, 0, 0));
                                temp->setText("Something failed, reset save window");
                            } else {
                                temp->setTextColor(sf::Color(255, 200, 0));
                                temp->setText("No information given");
                            }
                        }
                    }
                }
            });

            //if button for file listing clicked, show options
            bList->connect("clicked", [&]() {
                tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("saveChildMenu");
                if (childWindow != nullptr) {
                    tgui::Button::Ptr bList2 = childWindow->get<tgui::Button>("bList");
                    tgui::Button::Ptr bSave2 = childWindow->get<tgui::Button>("bSave");
                    tgui::ListBox::Ptr list2 = childWindow->get<tgui::ListBox>("list");

                    if (bList2 != nullptr) bList2->hide();


                    if (list2 != nullptr) {
                        list2->setPosition(childWindow->getSize().x * 0.05f, childWindow->getSize().y - 30);
                        list2->setSize(childWindow->getSize().x * 0.9f, 140);
                        fileHandler.getFiles("Texture/Maps", "list", "saveChildMenu", gui);
                        list2->show();
                    }
                    if (bSave2 != nullptr) {
                        bSave2->setPosition(bSave2->getPosition().x, bSave2->getPosition().y + 150);
                    }

                    childWindow->setSize(childWindow->getSize().x, childWindow->getSize().y + 150);
                }
            });
            eSave->connect("clicked", [&]() {
                tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("saveChildMenu");
                if (childWindow != nullptr) {
                    tgui::ListBox::Ptr list2 = childWindow->get<tgui::ListBox>("list");
                    if (list2 != nullptr) list2->deselectItem();
                }
            });

            list->connect("ItemSelected", [&]() {
                tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("saveChildMenu");
                if (childWindow != nullptr) {
                    tgui::EditBox::Ptr eSave2 = childWindow->get<tgui::EditBox>("eSave");
                    if (eSave2 != nullptr) eSave2->setText("");
                }
            });
        }
    }
    catch (const tgui::Exception& e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}


/// From: EditorSetup::getEditorSetupMenu
/// Function: Creating a child window for map loading
void EditorChildWindows::getLoadChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json, StateMachine &state, Sound &sound) {

    try {
        tgui::ChildWindow::Ptr LoadChildMenu = gui.get<tgui::ChildWindow>("loadChildMenu");
        if (LoadChildMenu == nullptr) {

            tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");


            std::string bLoadString = json.language["load"];
            std::string labelLoadString = json.language["loadmap"];
            std::string eSaveString = json.language["editText"];
            std::string menuString = json.language["menu"];

            menuString = sf::String::fromUtf8(bLoadString.begin(), bLoadString.end()) + " " +
                         sf::String::fromUtf8(menuString.begin(), menuString.end());

            //Creating the child window
            LoadChildMenu = theme->load("ChildWindow");
            LoadChildMenu->setSize(300, 300);
            LoadChildMenu->setPosition((window.getSize().x / 2) - (LoadChildMenu->getSize().x / 2),
                                       (window.getSize().y / 2) - (LoadChildMenu->getSize().y));
            LoadChildMenu->setTitle(menuString);


            tgui::ListBox::Ptr list = theme->load("ListBox");
            list->setSize(LoadChildMenu->getSize().x * 0.90f, 220);
            list->setPosition(LoadChildMenu->getSize().x * 0.05f, 30);

            tgui::Label::Ptr labelLoad;
            labelLoad = theme->load("label");
            labelLoad->setTextSize(18);
            labelLoad->setPosition(LoadChildMenu->getSize().x * 0.05f, 5);
            labelLoad->setText(sf::String::fromUtf8(labelLoadString.begin(), labelLoadString.end()));


            //for error massage
            tgui::Label::Ptr label;
            label = theme->load("label");
            label->setTextSize(15);
            label->setPosition(list->getPosition().x, list->getSize().y + list->getPosition().y + 4);

            //Creating all button needed
            tgui::Button::Ptr bLoad;

            bLoad = theme->load("Button");
            bLoad->setSize(LoadChildMenu->getSize().x * 0.45f, 20);
            bLoad->setPosition((list->getPosition().x + list->getSize().x) - bLoad->getSize().x,
                               LoadChildMenu->getSize().y - 25.0f);
            bLoad->setText(sf::String::fromUtf8(bLoadString.begin(), bLoadString.end()));

            LoadChildMenu->add(bLoad, "bLoad");
            LoadChildMenu->add(label, "fileMessage");
            LoadChildMenu->add(labelLoad, "labelLoad");
            LoadChildMenu->add(list, "list");
            gui.add(LoadChildMenu, "loadChildMenu");

            FileHandler fileHandler;
            fileHandler.getFiles("Texture/Maps", "list", "loadChildMenu", gui);

            bLoad->connect("clicked", [&]() {
                lDebug("Button load map clicked");
                tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("loadChildMenu");
                if (childWindow != nullptr) {
                    std::string file = childWindow->get<tgui::ListBox>("list")->getSelectedItem();
                    if (!file.empty()) {
                        fileHandler.loadMap("list", "loadChildMenu", json, gui);
                        tgui::Label::Ptr errorLabel = childWindow->get<tgui::Label>("fileMessage");
                        std::string message = childWindow->get<tgui::Label>("fileMessage")->getText();
                        if (errorLabel != nullptr && message.empty()) {
                            sound.SoundClick(),
                                    fileHandler.refectorJsonInto2DArray(json);
                            std::string selectedMap = childWindow->get<tgui::ListBox>("list")->getSelectedItem();
                            if (selectedMap.empty()) selectedMap = "Map";
                            json.editorSettings(json.map["height"], json.map["width"], 1, selectedMap);
                            gui.remove(childWindow);
                            json.mapLoaded = false;
                        }
                    }
                } else {
                    tgui::Label::Ptr temp = childWindow->get<tgui::Label>("fileMessage");
                    if (temp != nullptr) {
                        temp->setTextColor(sf::Color(255, 200, 0));
                        temp->setText("No file selected");
                    }
                }
            });
        }
    }
    catch (const tgui::Exception& e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }

}


/// From: EditorSetup::getEditorSetupMenu
/// Function: Creating a child window for showing information
void EditorChildWindows::getInformation(tgui::Gui &gui, sf::RenderWindow &window, Settings &json) {
    try {
        tgui::ChildWindow::Ptr changeTileChildMenu = gui.get<tgui::ChildWindow>("changeTileChildMenu");
        if (changeTileChildMenu == nullptr) {

            tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

            tgui::MenuBar::Ptr menu = gui.get<tgui::MenuBar>("menu");

            tgui::Label::Ptr position = theme->load("label");
            position->setTextSize(20);
            position->setPosition(window.getSize().x*0.01f,window.getSize().y - position->getTextSize() - window.getSize().y*0.01f);

            gui.add(position, "positionText");
        }
    }
    catch (const tgui::Exception& e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}



void EditorChildWindows::getPlayerMonsterChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json) {

    //pm stands for PlayerMonster
    try {
        tgui::ChildWindow::Ptr pmChildMenu = gui.get<tgui::ChildWindow>("pmChildMenu");
        if (pmChildMenu == nullptr) {

            tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");


            std::string menuString = json.language["menu"];

            menuString = sf::String::fromUtf8(menuString.begin(), menuString.end());

            //Creating the child window
            pmChildMenu = theme->load("ChildWindow");
            pmChildMenu->setSize(450, 240);
            pmChildMenu->setPosition((window.getSize().x / 2) - (pmChildMenu->getSize().x / 2), (window.getSize().y / 2) - (pmChildMenu->getSize().y));
            pmChildMenu->setTitle(menuString);


            tgui::Panel::Ptr Red = theme->load("panel");
            Red->setSize(pmChildMenu->getSize().x/0.5f, pmChildMenu->getSize().y);
            Red->setBackgroundColor(sf::Color(255,0,0));
            Red->setOpacity(0.3f);
            pmChildMenu->add(Red);

            tgui::Panel::Ptr Blue = tgui::Panel::copy(Red);
            Blue->setPosition(pmChildMenu->getSize().x/2.0f,0);
            Blue->setBackgroundColor(sf::Color(0,0,255));
            pmChildMenu->add(Blue);

            tgui::Label::Ptr labelPlayer, labelMonster, labelPlayerNumber, labelMosterWave;

            labelPlayer = theme->load("label");
            labelPlayer->setTextSize(25);
            labelPlayer->setText("Players");
            labelPlayer->setPosition(pmChildMenu->getSize().x*0.01f,2.0f);

            labelMonster = tgui::Label::copy(labelPlayer);
            labelMonster->setText("Enemies");
            labelMonster->setPosition(230,labelPlayer->getPosition().y);


            tgui::Slider::Ptr sliderPlayers;
            sliderPlayers = theme->load("slider");
            sliderPlayers->setPosition(11, 65);
            sliderPlayers->setSize(pmChildMenu->getSize().x*0.40f,13);
            sliderPlayers->setMaximum(MAX_PLAYERS);
            sliderPlayers->setMinimum(1);
            sliderPlayers->setValue(json.map["players"]);
            labelPlayerNumber = theme->load("label");
            labelPlayerNumber->setTextSize(15);
            labelPlayerNumber->setPosition(11, 45);
            labelPlayerNumber->setText("Players: "+std::to_string(sliderPlayers->getValue()));


            tgui::Slider::Ptr sliderWaves;
            sliderWaves = tgui::Slider::copy(sliderPlayers);
            sliderWaves->setPosition(235, 140);
            sliderWaves->setMaximum(MAX_WAVES);
            sliderWaves->setMinimum(1);
            sliderWaves->setValue(json.map["waves"]);
            labelMosterWave = theme->load("label");
            labelMosterWave->setTextSize(15);
            labelMosterWave->setPosition(235, sliderWaves->getPosition().y-labelMosterWave->getTextSize()-5);
            labelMosterWave->setText("Waves: "+std::to_string(sliderWaves->getValue()));


            tgui::RadioButton::Ptr rbRandomMonster;
            rbRandomMonster = theme->load("RadioButton");
            rbRandomMonster->setPosition(235,45);
            rbRandomMonster->setSize(20, 20);
            rbRandomMonster->setText("Fixed");

            tgui::RadioButton::Ptr rbDefineMonsters = tgui::RadioButton::copy(rbRandomMonster);
            rbDefineMonsters = theme->load("RadioButton");
            rbDefineMonsters->setPosition(235,70);
            rbDefineMonsters->setSize(20, 20);
            rbDefineMonsters->setText("Specified");

            if(json.map["fixed_waves"]){
                rbRandomMonster->check();
                rbDefineMonsters->uncheck();
            }
            else{
                rbRandomMonster->uncheck();
                rbDefineMonsters->check();
            }

            tgui::Button::Ptr bWaveList;
            bWaveList = theme->load("button");
            bWaveList->setSize(pmChildMenu->getSize().x*0.4,25);
            bWaveList->setPosition(pmChildMenu->getSize().x-bWaveList->getSize().x-5, pmChildMenu->getSize().y-bWaveList->getSize().y-5);
            bWaveList->setText("Wave list...");


            ///PLAYER MENU
            //////////////////////////////////////////////////////////////////////////////////////
            tgui::Panel::Ptr radioGroup1 = theme->load("panel");
            radioGroup1->setPosition(5, 130);
            radioGroup1->setSize(100, 60);
            radioGroup1->setBackgroundColor(sf::Color(0,0,0,0));

            tgui::RadioButton::Ptr rbShered = tgui::RadioButton::copy(rbRandomMonster);
            rbShered->setPosition(0,0);
            rbShered->setText("Sheared");

            tgui::RadioButton::Ptr rbDivided = tgui::RadioButton::copy(rbRandomMonster);
            rbDivided->setPosition(0,25);
            rbDivided->setText("Divided");

            if(json.map["divided"]){
                rbDivided->check();
                rbShered->uncheck();
            }
            else{
                rbDivided->uncheck();
                rbShered->check();
            }
            radioGroup1->add(rbShered,"sheared");
            radioGroup1->add(rbDivided,"divided");
            //////////////////////////////////////////////////////////////////////////////////


            tgui::Label::Ptr labelSpawns = theme->load("label");
            labelSpawns->setText("Sheared or divided spawns:");
            labelSpawns->setTextSize(14);
            labelSpawns->setPosition(5,110);


            ///TEAM PART PLAYER
            ///////////////////////////////////////////////////////////////////////////////////
            tgui::CheckBox::Ptr cTeams = theme->load("CheckBox");
            cTeams->setSize(20,20);
            cTeams->setPosition(5, 190);
            cTeams->setText("Teams");
            if(json.map["team"])
                cTeams->check();
            else
                cTeams->uncheck();

            tgui::Panel::Ptr radioGroup3 = theme->load("panel");
            radioGroup3->setPosition(5, 212);
            radioGroup3->setSize(pmChildMenu->getSize().x/0.3f, 30);
            radioGroup3->setBackgroundColor(sf::Color(0,0,0,0));

            tgui::RadioButton::Ptr teamTwo = theme->load("RadioButton");
            teamTwo->setSize(20,20);
            teamTwo->setText("2");
            teamTwo->setPosition(0, 0);

            tgui::RadioButton::Ptr teamThree = tgui::RadioButton::copy(teamTwo);
            teamThree->setText("3");
            teamThree->setPosition(38, 0);
            teamThree->uncheck();

            tgui::RadioButton::Ptr teamFour = tgui::RadioButton::copy(teamTwo);
            teamFour->setText("4");
            teamFour->setPosition(76, 0);
            teamFour->uncheck();

            tgui::RadioButton::Ptr teamFive = tgui::RadioButton::copy(teamTwo);
            teamFive->setText("5");
            teamFive->setPosition(114, 0);
            teamFive->uncheck();

            radioGroup3->add(teamTwo, "tTwo");
            radioGroup3->add(teamThree, "tThree");
            radioGroup3->add(teamFour, "tFour");
            radioGroup3->add(teamFive, "tFive");


            ////////////////////////////////////////////////////////////////////

            pmChildMenu->add(labelPlayer);
            pmChildMenu->add(labelMonster);
            pmChildMenu->add(labelPlayerNumber, "playerNumber");
            pmChildMenu->add(labelMosterWave, "Waves");
            pmChildMenu->add(labelSpawns, "labelSheared");
            pmChildMenu->add(sliderPlayers, "sliderPlayer");
            pmChildMenu->add(sliderWaves, "sliderWaves");
            pmChildMenu->add(rbRandomMonster, "rbRandom");
            pmChildMenu->add(rbDefineMonsters, "rbDefine");
            pmChildMenu->add(cTeams, "teams");
            pmChildMenu->add(radioGroup1, "radio1");
            pmChildMenu->add(radioGroup3, "radio3");
            pmChildMenu->add(bWaveList, "bWave");
            gui.add(pmChildMenu, "pmChildMenu");

            RadioOptionDividedTrueOrFalse(gui, json);
            if(json.map["fixed_waves"]){
                RadioOptionFixedOrDefinedWaves(gui,json,1);
            } else
                RadioOptionFixedOrDefinedWaves(gui,json,2);

            rbShered->connect("clicked", [&](){
                RadioOptionShearedOrDivided(gui,1, json);
                if(json.editor["selected_type"] == "spawn")
                    esf::updatePanels(gui,json,json.editor["selected_type"]);
            });
            rbDivided->connect("clicked", [&](){
                RadioOptionShearedOrDivided(gui,2, json);
                if(json.editor["selected_type"] == "spawn")
                    esf::updatePanels(gui,json,json.editor["selected_type"]);
            });

            teamTwo->connect("clicked", [&](){
                json.map["teams"] = 2;
                if(json.editor["selected_type"] == "spawn")
                    esf::updatePanels(gui,json,json.editor["selected_type"]);
            });
            teamThree->connect("clicked", [&](){
                json.map["teams"] = 3;
                if(json.editor["selected_type"] == "spawn")
                    esf::updatePanels(gui,json,json.editor["selected_type"]);
            });
            teamFour->connect("clicked", [&](){
                json.map["teams"] = 4;
                if(json.editor["selected_type"] == "spawn")
                    esf::updatePanels(gui,json,json.editor["selected_type"]);
            });
            teamFive->connect("clicked", [&](){
                json.map["teams"] = 5;
                if(json.editor["selected_type"] == "spawn")
                    esf::updatePanels(gui,json,json.editor["selected_type"]);
            });


            cTeams->connect("clicked", [&](){
                if(json.map["team"])
                    json.map["team"] = false;
                else
                    json.map["team"] = true;
                RadioOptionDividedTrueOrFalse(gui, json);
                if(json.editor["selected_type"] == "spawn")
                    esf::updatePanels(gui,json,json.editor["selected_type"]);
            });

            rbRandomMonster->connect("clicked", [&](){  RadioOptionFixedOrDefinedWaves(gui,json,1); });

            rbDefineMonsters->connect("clicked", [&](){ RadioOptionFixedOrDefinedWaves(gui,json,2); });

            sliderPlayers->connect("ValueChanged", [&](){
                tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("pmChildMenu");
                tgui::Slider::Ptr sPlayer = childWindow->get<tgui::Slider>("sliderPlayer");
                if(sPlayer != nullptr){
                    json.map["players"] = sPlayer->getValue();
                    tgui::Label::Ptr player = childWindow->get<tgui::Label>("playerNumber");
                    if(json.editor["selected_type"] == "spawn")
                        esf::updatePanels(gui,json,json.editor["selected_type"]);
                    if(player != nullptr){
                        player->setText("Players: "+std::to_string(sPlayer->getValue()));
                    }
                }
            });

            sliderWaves->connect("ValueChanged", [&](){
                tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("pmChildMenu");
                tgui::Slider::Ptr sWaves = childWindow->get<tgui::Slider>("sliderWaves");
                if(sWaves != nullptr){
                    json.map["waves"] = sWaves->getValue();
                    tgui::Label::Ptr player = childWindow->get<tgui::Label>("Waves");
                    if(player != nullptr){
                        player->setText("Waves: "+std::to_string(sWaves->getValue()));
                    }
                }
            });

        }
    }
    catch (const tgui::Exception& e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}


void EditorChildWindows::getDescriptionChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json) {

    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("description");

        if (childWindow == nullptr) {

            tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

            std::string menuString = json.language["menu"];

            menuString = sf::String::fromUtf8(menuString.begin(), menuString.end());

            //Creating the child window
            childWindow = theme->load("ChildWindow");
            childWindow->setSize(400, 300);
            childWindow->setPosition(window.getSize().x/2.0f - childWindow->getSize().x/2.0f, window.getSize().y/2.0f - childWindow->getSize().y/2.0f);
            childWindow->setTitle(menuString);
            gui.add(childWindow,"description");

            tgui::Label::Ptr label = theme->load("label");
            label->setTextSize(20);
            label->setText("Map description");
            label->setPosition(childWindow->getSize().x*0.01f,childWindow->getSize().y*0.01f);
            childWindow->add(label);

            tgui::TextBox::Ptr textBox = theme->load("textbox");
            textBox->setPosition(label->getPosition().x, label->getPosition().y + label->getTextSize()*1.2f);
            textBox->setSize(childWindow->getSize().x-textBox->getPosition().x*2.0f,200);
            try {
                std::string temp = json.map.at("description");
                textBox->setText(temp);
            }catch (...){
                lWarning("json.map description did not exist");
            }
            textBox->connect("TextChanged", [&,textBox](){
                json.map["description"] = textBox->getText();
            });
            childWindow->add(textBox);

            tgui::EditBox::Ptr imagePath = theme->load("editbox");
            imagePath->setPosition(textBox->getPosition().x, textBox->getPosition().y + textBox->getSize().y*1.1f);
            imagePath->setSize(textBox->getSize().x, 30);
            imagePath->setDefaultText("add image to 'maps->image' folder");
            try {
                std::string temp = json.map.at("image");
                imagePath->setText(temp);
            }catch (...){
                lWarning("json.map image did not exist");
            }
            imagePath->connect("TextChanged", [&,imagePath](){
                json.map["image"] = imagePath->getText();
            });
            childWindow->add(imagePath);

        }
    }
    catch (const tgui::Exception& e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}

void EditorChildWindows::getSelectedTileChildWindow(tgui::Gui &gui, sf::RenderWindow &window, Settings &json) {

    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);
        if (childWindow == nullptr) {

            tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

            std::string menuString = json.language["menu"];

            menuString = sf::String::fromUtf8(menuString.begin(), menuString.end());

            //Creating the child window
            childWindow = theme->load("ChildWindow");
            childWindow->setSize(600, 150);
            childWindow->setPosition(0, (window.getSize().y) - (childWindow->getSize().y)-25);
            childWindow->setTitle(menuString);

            tgui::Panel::Ptr mainPanel = theme->load("panel");

            mainPanel->setSize(160,childWindow->getSize().y);

            mainPanel->setBackgroundColor(sf::Color(255,0,0,150));
            mainPanel->setPosition(0,0);

            tgui::Label::Ptr lInfo = theme->load("label");
            lInfo->setTextSize(15);
            lInfo->setPosition(5,0);

            tgui::ListBox::Ptr imageFrame = theme->load("ListBox");
            imageFrame->setSize(100,100);
            imageFrame->setPosition(10,30);


            mainPanel->add(lInfo, "info");
            mainPanel->add(imageFrame, "imageFrame");

            childWindow->add(mainPanel, "mainPanel");
            gui.add(childWindow, selectedTileChildWindow);

            updateSelectedTileChildWindow(gui,json);
        }
    }
    catch (const tgui::Exception& e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}


void EditorChildWindows::updateSelectedTileChildWindow(tgui::Gui &gui, Settings &json) {

    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);
        tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("mainPanel");

        if(childWindow != nullptr && panel != nullptr){

            tgui::Label::Ptr lInfo = panel->get<tgui::Label>("info");
            tgui::ListBox::Ptr imageFrame = panel->get<tgui::ListBox>("imageFrame");

            if(json.editor["selected_type"] != json.editor["tile_type"]){
                esf::clearSpecialTileView(gui);
            }

            //Storing spesified tile ID
            json.editor["selected_tile"] = {};
            json.editor["selected_tile"] += json.editor["tile_x"];
            json.editor["selected_tile"] += json.editor["tile_y"];
            json.editor["selected_type"] = json.editor["tile_type"];

            EditorSetup editorSetup;
            editorSetup.drawImage(true,false,gui,json);

            esf::setMainPanelInfo(gui,json);
            esf::updatePanels(gui,json,json.editor["selected_type"]);

        }
        else{
            lError("Did not find childWindow or panel for updating selected tile");
        }
    } catch (const tgui::Exception &e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}

///############################################# PRIVATE ##########################################################\\\
///

void EditorChildWindows::RadioOptionShearedOrDivided(tgui::Gui& gui, int option, Settings &json){

    tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("pmChildMenu");
    tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("radio1");
    tgui::RadioButton::Ptr rButtonS = panel->get<tgui::RadioButton>("sheared");
    tgui::RadioButton::Ptr rButtonD = panel->get<tgui::RadioButton>("divided");
    if(rButtonS != nullptr && rButtonD != nullptr && option == 1){
        rButtonS->check();
        rButtonD->uncheck();
        json.map["divided"] = false;

        RadioOptionDividedTrueOrFalse(gui, json);
    }
    else if(rButtonS != nullptr && rButtonD != nullptr && option == 2){
        rButtonS->uncheck();
        rButtonD->check();
        json.map["divided"] = true;
        RadioOptionDividedTrueOrFalse(gui, json);
    }
}


void EditorChildWindows::RadioOptionDividedTrueOrFalse(tgui::Gui &gui, Settings &json) {

    tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("pmChildMenu");
    tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("radio3");
    tgui::RadioButton::Ptr rButtonS = panel->get<tgui::RadioButton>("sheared");
    tgui::RadioButton::Ptr rButtonD = panel->get<tgui::RadioButton>("divided");


    float transparent_value = 0.5f;
    if(childWindow != nullptr &&panel != nullptr) {

        tgui::RadioButton::Ptr r1 = panel->get<tgui::RadioButton>("tTwo");
        tgui::RadioButton::Ptr r2 = panel->get<tgui::RadioButton>("tThree");
        tgui::RadioButton::Ptr r3 = panel->get<tgui::RadioButton>("tFour");
        tgui::RadioButton::Ptr r4 = panel->get<tgui::RadioButton>("tFive");
        tgui::CheckBox::Ptr cb = childWindow->get<tgui::CheckBox>("teams");


        if (!json.map["team"] || !json.map["divided"]) {

            if (!json.map["divided"]) {
                cb->setOpacity(transparent_value);
                cb->disable();
            }
            else{
                cb->setOpacity(1);
                cb->enable();
            }

            r1->setOpacity(transparent_value);
            r2->setOpacity(transparent_value);
            r3->setOpacity(transparent_value);
            r4->setOpacity(transparent_value);
            r1->disable();
            r2->disable();
            r3->disable();
            r4->disable();
        }
        else {
            cb->setOpacity(1);
            cb->enable();
            r1->setOpacity(1);
            r2->setOpacity(1);
            r3->setOpacity(1);
            r4->setOpacity(1);
            r1->enable();
            r2->enable();
            r3->enable();
            r4->enable();
        }
        if(json.map["teams"] == 2){
            r1->check();
        }
        else if(json.map["teams"] == 3){
            r2->check();
        }
        else if(json.map["teams"] == 4){
            r3->check();
        }
        else if(json.map["teams"] == 5){
            r4->check();
        }
    }
}

void EditorChildWindows::RadioOptionFixedOrDefinedWaves(tgui::Gui &gui, Settings &json, int option) {

    tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("pmChildMenu");
    tgui::RadioButton::Ptr rButtonF = childWindow->get<tgui::RadioButton>("rbRandom");
    tgui::RadioButton::Ptr rButtonD = childWindow->get<tgui::RadioButton>("rbDefine");

    tgui::Slider::Ptr sWaves = childWindow->get<tgui::Slider>("sliderWaves");
    tgui::Label::Ptr label = childWindow->get<tgui::Label>("Waves");
    tgui::Button::Ptr waves = childWindow->get<tgui::Button>("bWave");

    float transparent_value = 0.5f;
    if(rButtonF != nullptr && rButtonD != nullptr && sWaves != nullptr && label != nullptr, waves != nullptr){


        if(option == 1){
            rButtonF->check();
            rButtonD->uncheck();

            waves->setOpacity(transparent_value);
            sWaves->setOpacity(transparent_value);
            label->setOpacity(transparent_value);
            waves->disable();
            sWaves->disable();
            label->disable();
        }
        else if(option == 2){
            rButtonD->check();
            rButtonF->uncheck();

            waves->setOpacity(transparent_value);
            sWaves->setOpacity(1);
            label->setOpacity(1);
            waves->disable();
            sWaves->enable();
            label->enable();
        }
    }
}


