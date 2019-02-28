//
// Created by Chrim14 on 06.11.2017.
//
#include <TGUI/Gui.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/CheckBox.hpp>
#include <TGUI/Widgets/ChildWindow.hpp>
#include "EditorStaticGuiFunctions.h"
#include "../../System/MapEditor/MapEditorStaticFunctions.h"
#include "EditorChildWindows.h"

#define Transparency 0.5f
#define selectedTileChildWindow "selectedTileChildWindow"
#define color_green sf::Color(20,120,50)
#define color_purple sf::Color(100, 25, 200)

void esf::getWeightTguiChange(bool already_checked, std::string string, tgui::Gui &gui, Settings &json) {

    tgui::Slider::Ptr slider = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("weight")->get<tgui::Slider>(string);
    tgui::Label::Ptr label = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("weight")->get<tgui::Label>("l"+string);
    tgui::CheckBox::Ptr direction = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("direction")->get<tgui::CheckBox>(string);

    if(slider != nullptr && direction != nullptr && label != nullptr) {
        if ((direction->isChecked() && already_checked) || (!already_checked && !direction->isChecked())) {
            slider->enable();
            slider->setOpacity(1.0f);
            label->setOpacity(1.0f);
        }
        else {

            int value = -1;
            if(string == "north") value = 0;
            else if(string == "east") value = 1;
            else if(string == "south") value = 2;
            else if(string == "west") value = 3;

            if(value == 0 || value == 3){
                slider->setValue(100);
                esf::setWeightChangeLabel(string,gui);
            }
            else if(value == 1 || value == 2){
                slider->setValue(0);
                esf::setWeightChangeLabel(string,gui);
            }

            slider->disable();
            slider->setOpacity(Transparency);
            label->setOpacity(Transparency);
        }
    } else{
        lError("esf::getWeightTguiChange did not find all widgets");
    }
}

void esf::setWeightChangeLabel(std::string string, tgui::Gui &gui) {

    tgui::Slider::Ptr slider = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("weight")->get<tgui::Slider>(string);
    tgui::Label::Ptr label = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("weight")->get<tgui::Label>("l"+string);

    if(slider != nullptr && label != nullptr) {

        int value = slider->getValue();
        if(string == "north" || string == "west"){
            value = 100-slider->getValue();
        }
        label->setText(std::to_string(value)+"%");

    }
    else{
        lError("esf::setWeightChangeLabel did not find all widgets");
    }
}

void esf::setWeightSliderChanges(std::string direction, std::string panel, tgui::Gui &gui) {

    std::vector<std::string> string = {"north", "east", "west", "south"};
    if(panel == "speed") string = {"east", "south"};
    tgui::Slider::Ptr main;

    int total_sliders = 0;

    for(const auto& temp : string){
        if(gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>(panel)->get<tgui::Slider>(temp)->isEnabled()){
            if(direction != temp){
                total_sliders++;
            }
            else if(direction == temp){
                main = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>(panel)->get<tgui::Slider>(temp);
            }
        }
    }
    int value = main->getValue();
    if(direction == "north" || direction == "west")
        value = 100-value;

    tgui::Slider::Ptr north = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>(panel)->get<tgui::Slider>("north");
    tgui::Slider::Ptr east = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>(panel)->get<tgui::Slider>("east");
    tgui::Slider::Ptr south = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>(panel)->get<tgui::Slider>("south");
    tgui::Slider::Ptr west = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>(panel)->get<tgui::Slider>("west");

    int total = 100;

    if(north != nullptr && main != north && north->isEnabled()){
        total -= 100-north->getValue();
    }
    if(south != nullptr && main != south && south->isEnabled()){
        total -= south->getValue();
    }
    if(west != nullptr && main != west && west->isEnabled()){
        total -= 100-west->getValue();
    }
    if(east != nullptr && main != east && east->isEnabled()){
        total -= east->getValue();
    }
    total -= value;

    if(total_sliders == 3) total -= 2;
    else if(total_sliders == 2) total -= 1;

    if(total < 0){
        if(north != nullptr && main != north && north->isEnabled()){
            north->setValue(north->getValue()-total/total_sliders);
        }
        if(south != nullptr && main != south && south->isEnabled()){
            south->setValue(south->getValue()+total/total_sliders);
        }
        if(west != nullptr && main != west && west->isEnabled()){
            west->setValue(west->getValue()-total/total_sliders);
        }
        if(east != nullptr && main != east && east->isEnabled()){
            east->setValue(east->getValue()+total/total_sliders);
        }
    }
}

void esf::getPanelCreateSplitter(tgui::Gui &gui, Settings &json) {

    tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);
    tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("create_splitter");
    tgui::Panel::Ptr main = childWindow->get<tgui::Panel>("mainPanel");

    if(panel == nullptr && childWindow != nullptr) {

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        panel = theme->load("panel");
        panel->setSize(105,childWindow->getSize().y);
        panel->setPosition(main->getSize().x+main->getPosition().x,main->getPosition().y);
        panel->setBackgroundColor(color_green);

        tgui::Label::Ptr label = theme->load("label");
        label->setPosition(5, 5);
        label->setTextSize(15);
        label->setText("Set function:");

        tgui::RadioButton::Ptr none = theme->load("RadioButton");
        none->setSize(20,20);
        none->setPosition(5,30);
        none->setText("None");

        tgui::RadioButton::Ptr divider = tgui::RadioButton::copy(none);
        divider->setPosition(none->getPosition().x, none->getPosition().y+none->getSize().y*1.5);
        divider->setText("Divider");

        tgui::RadioButton::Ptr speed = tgui::RadioButton::copy(none);
        speed->setPosition(divider->getPosition().x, divider->getPosition().y+divider->getSize().y*1.5);
        speed->setText("Speed");

        if(json.editor["selected_type"] == "divider")  divider->check();
        else if(json.editor["selected_type"] == "speed")  speed->check();
        else none->check();

        panel->add(label,"label");
        panel->add(none,"none");
        panel->add(divider,"divider");
        panel->add(speed,"speed");

        none->connect("clicked", [&](){
            esf::setRoadTileOption(1, gui, json);
        });
        divider->connect("clicked", [&](){
            esf::setRoadTileOption(2, gui, json);
        });
        speed->connect("clicked", [&](){
            esf::setRoadTileOption(3, gui, json);
        });

        childWindow->add(panel, "create_splitter");
    }
    else if(panel != nullptr){}
    else{
        lError("esf::getPanelCreateSplitter did not find all widgets");
    }
}

void esf::setRoadTileOption(int check_box, tgui::Gui &gui, Settings &json) {

    tgui::Panel::Ptr panel = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("create_splitter");
    tgui::RadioButton::Ptr none = panel->get<tgui::RadioButton>("none");
    tgui::RadioButton::Ptr divider = panel->get<tgui::RadioButton>("divider");
    tgui::RadioButton::Ptr speed = panel->get<tgui::RadioButton>("speed");

    if(none != nullptr && divider != nullptr && speed != nullptr){

        unsigned int x = json.editor["selected_tile"][0], y = json.editor["selected_tile"][1];
        sf::Vector2f temp = sf::Vector2f(x*Tile_Size, y*Tile_Size);

        if(check_box == 1 && !none->isChecked()){

            if(speed->isChecked()){
                mef::removeSpecialTile(temp, json, "speed");
            }
            else if(divider->isChecked()){
                mef::removeSpecialTile(temp, json, "divider");
            }
            json.editor["selected_type"] = "road";
        }

        else if(check_box == 2 && !divider->isChecked()){
            mef::setValueDirection(json);

            if(speed->isChecked()){
                mef::removeSpecialTile(temp, json, "speed");
            }
            json.editor["selected_type"] = "divider";
        }

        else if(check_box == 3 && !speed->isChecked()){
            mef::setValueSpeed(json);

            if(divider->isChecked()){
                mef::removeSpecialTile(temp, json, "divider");
            }
            json.editor["selected_type"] = "speed";
        }
        esf::clearSpecialTileView(gui);
        esf::setMainPanelInfo(gui,json);
        esf::updatePanels(gui,json,json.editor["selected_type"]);
    }
}

void esf::clearSpecialTileView(tgui::Gui &gui) {

    tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);

    std::vector<std::string> panels = {"direction", "weight", "create_splitter", "teleport", "speed","destination","players"};
    for(const auto& temp : panels){
        tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>(temp);
        childWindow->remove(panel);
    }
}

void esf::updatePanels(tgui::Gui &gui, Settings &json, std::string Tile_Type) {


    if(json.editor["selected_type"] == "spawn") {
        esf::getPanelSelectPlayers(gui,json,Tile_Type);
        esf::getPanelDirection(gui, json, Tile_Type);
        esf::getPanelWeight(gui, json, Tile_Type);
    }
    else if(json.editor["selected_type"] == "divider"){
        esf::getPanelCreateSplitter(gui,json);
        esf::getPanelDirection(gui, json, Tile_Type);
        esf::getPanelWeight(gui, json, Tile_Type);
    }
    else if(json.editor["selected_type"] == "speed"){
        esf::getPanelCreateSplitter(gui,json);
        esf::getPanelSpeed(gui,json,Tile_Type);
    }
    else if(json.editor["selected_type"] == "road"){
        esf::getPanelCreateSplitter(gui,json);
    }
    else if(json.editor["selected_type"] == "teleport"){
        esf::getPanelTeleport(gui,json, Tile_Type);
        esf::getPanelDirection(gui, json, Tile_Type);
        esf::getPanelWeight(gui, json, Tile_Type);
    }
    else if(json.editor["selected_type"] == "destination"){
        esf::getPanelDestination(gui,json, Tile_Type);
    }
}

void esf::getPanelDirection(tgui::Gui &gui, Settings &json, std::string &Tile_Type) {

    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr mainPanel = childWindow->get<tgui::Panel>("mainPanel");
        tgui::Panel::Ptr splitterPanel = childWindow->get<tgui::Panel>("create_splitter");
        tgui::Panel::Ptr teleportPanel = childWindow->get<tgui::Panel>("teleport");
        tgui::Panel::Ptr playerPanel = childWindow->get<tgui::Panel>("players");

        if(splitterPanel != nullptr) mainPanel = splitterPanel;
        else if(teleportPanel != nullptr) mainPanel = teleportPanel;
        else if(playerPanel != nullptr) mainPanel = playerPanel;

        tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("direction");

        std::vector<int> temp = mef::getTileDirection(sf::Vector2i(json.editor["selected_tile"][0],json.editor["selected_tile"][1]),json, Tile_Type);


        if(panel == nullptr && mainPanel != nullptr && temp.size() == 4) {

            panel = theme->load("panel");
            panel->setSize(150, childWindow->getSize().y);
            panel->setBackgroundColor(color_purple);
            panel->setPosition(mainPanel->getSize().x+mainPanel->getPosition().x, 0);
            childWindow->add(panel, "direction");

            tgui::Label::Ptr label;
            label = theme->load("label");
            label->setText("Direction");
            label->setPosition(5, 5);
            label->setTextSize(15);
            panel->add(label, "direction_label");

            tgui::CheckBox::Ptr north, west, south, east;

            north = theme->load("CheckBox");
            north->setSize(35, 35);
            north->setPosition(50, (label->getTextSize() + label->getPosition().y+5));

            east = tgui::CheckBox::copy(north);
            east->setPosition(north->getPosition().x + north->getSize().x,
                              north->getPosition().y + north->getSize().y);

            south = tgui::CheckBox::copy(north);
            south->setPosition(north->getPosition().x, north->getPosition().y + (north->getSize().y * 2));

            west = tgui::CheckBox::copy(north);
            west->setPosition(north->getPosition().x - north->getSize().x,
                              north->getPosition().y + north->getSize().y);

            panel->add(north, "north");
            panel->add(west, "west");
            panel->add(south, "south");
            panel->add(east, "east");

            north->connect("clicked", [&](){
                mef::setTileDirection(0,json);
                esf::getWeightTguiChange(false,"north",gui,json);
            });
            east->connect("clicked", [&](){
                mef::setTileDirection(1,json);
                esf::getWeightTguiChange(false,"east",gui,json);
            });
            south->connect("clicked", [&](){
                mef::setTileDirection(2,json);
                esf::getWeightTguiChange(false,"south",gui,json);
            });
            west->connect("clicked", [&](){
                mef::setTileDirection(3,json);
                esf::getWeightTguiChange(false,"west",gui,json);
            });
        }

        if(panel != nullptr && mainPanel != nullptr && temp.size() == 4) {

            tgui::CheckBox::Ptr north = panel->get<tgui::CheckBox>("north");
            tgui::CheckBox::Ptr west = panel->get<tgui::CheckBox>("west");
            tgui::CheckBox::Ptr south = panel->get<tgui::CheckBox>("south");
            tgui::CheckBox::Ptr east = panel->get<tgui::CheckBox>("east");

            if (north != nullptr && west != nullptr && south != nullptr && east != nullptr) {

                if (temp[0] == 1)
                    north->check();
                else
                    north->uncheck();

                if (temp[1] == 1)
                    east->check();
                else
                    east->uncheck();

                if (temp[2] == 1)
                    south->check();
                else
                    south->uncheck();

                if (temp[3] == 1)
                    west->check();
                else
                    west->uncheck();
            }
        }

    } catch (const tgui::Exception &e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}

void esf::getPanelWeight(tgui::Gui &gui, Settings &json, std::string &Tile_Type) {

    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr mainPanel = childWindow->get<tgui::Panel>("mainPanel");
        tgui::Panel::Ptr directionPanel = childWindow->get<tgui::Panel>("direction");
        tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("weight");

        std::vector<int> active = mef::getTileDirection(sf::Vector2i(json.editor["selected_tile"][0],json.editor["selected_tile"][1]),json, Tile_Type);
        std::vector<int> temp = mef::getTileWeights(sf::Vector2i(json.editor["selected_tile"][0],json.editor["selected_tile"][1]),json, Tile_Type);

        if(panel == nullptr && mainPanel != nullptr && directionPanel != nullptr) {

            panel = theme->load("panel");
            panel->setSize(200, childWindow->getSize().y);
            panel->setBackgroundColor(color_purple);
            panel->setPosition(directionPanel->getSize().x + directionPanel->getPosition().x, 0);
            childWindow->add(panel, "weight");


            tgui::Label::Ptr label;
            label = theme->load("label");
            label->setText("Weights");
            label->setPosition(5, 5);
            label->setTextSize(15);
            panel->add(label, "direction_label");
            panel->add(label);

            //Creating all the sliders for weight panel
            float distance = 3; //Distance in center

            tgui::Slider::Ptr north;
            north = theme->load("slider");
            north->setPosition(100, 5);
            north->setSize(12, 60);
            north->setMaximum(100);
            north->setMinimum(0);
            tgui::Slider::Ptr east = tgui::Slider::copy(north);
            east->setSize(north->getSize().y, north->getSize().x);
            east->setPosition(north->getPosition().x + north->getSize().x + distance,
                              north->getPosition().y + north->getSize().y + (distance / 2.0f));

            tgui::Slider::Ptr south = tgui::Slider::copy(north);
            south->setPosition(north->getPosition().x, east->getPosition().y + east->getSize().y + distance);

            tgui::Slider::Ptr west = tgui::Slider::copy(east);
            west->setPosition(north->getPosition().x - north->getSize().y - distance,
                              north->getPosition().y + north->getSize().y + (distance / 2.0f));

            north->setValue(100-temp[0]);
            east->setValue(temp[1]);
            south->setValue(temp[2]);
            west->setValue(100-temp[3]);

            //Creating labels for weight panel
            unsigned int textSize = 15;
            tgui::Label::Ptr lNorth = theme->load("label");
            lNorth->setTextSize(textSize);
            lNorth->setPosition(north->getPosition().x + north->getSize().x + 5, north->getPosition().y);

            tgui::Label::Ptr lEast = tgui::Label::copy(lNorth);
            lEast->setPosition(east->getPosition().x + east->getSize().x - 25, east->getPosition().y - (signed)textSize);

            tgui::Label::Ptr lSouth = tgui::Label::copy(lNorth);
            lSouth->setPosition(south->getPosition().x + south->getSize().x + 5, south->getPosition().y + south->getSize().y - (signed)textSize);

            tgui::Label::Ptr lWest = tgui::Label::copy(lNorth);
            lWest->setPosition(west->getPosition().x, west->getPosition().y - (signed)textSize);

            panel->add(north, "north");
            panel->add(west, "west");
            panel->add(south, "south");
            panel->add(east, "east");

            panel->add(lNorth, "lnorth");
            panel->add(lEast, "least");
            panel->add(lSouth, "lsouth");
            panel->add(lWest, "lwest");

            north->connect("ValueChanged", [&]() {
                tgui::Slider::Ptr slider = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("weight")->get<tgui::Slider>("north");
                if(slider != nullptr){
                    esf::setWeightSliderChanges("north","weight",gui);
                    esf::setWeightChangeLabel("north",gui);
                    mef::setTileWeights(0,100-slider->getValue(),json);
                }
            });
            east->connect("ValueChanged", [&]() {
                tgui::Slider::Ptr slider = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("weight")->get<tgui::Slider>("east");
                if(slider != nullptr){
                    esf::setWeightSliderChanges("east","weight",gui);
                    esf::setWeightChangeLabel("east",gui);
                    mef::setTileWeights(1,slider->getValue(),json);
                }
            });
            south->connect("ValueChanged", [&]() {
                tgui::Slider::Ptr slider = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("weight")->get<tgui::Slider>("south");
                if(slider != nullptr){
                    esf::setWeightSliderChanges("south","weight",gui);
                    esf::setWeightChangeLabel("south",gui);
                    mef::setTileWeights(2,slider->getValue(),json);
                }
            });
            west->connect("ValueChanged", [&]() {
                tgui::Slider::Ptr slider = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("weight")->get<tgui::Slider>("west");
                if(slider != nullptr){
                    esf::setWeightSliderChanges("west","weight",gui);
                    esf::setWeightChangeLabel("west",gui);
                    mef::setTileWeights(3,100-slider->getValue(),json);
                }
            });
        }

        if (panel != nullptr && mainPanel != nullptr) {

            esf::getWeightTguiChange(true,"north",gui,json);
            esf::getWeightTguiChange(true,"east",gui,json);
            esf::getWeightTguiChange(true,"west",gui,json);
            esf::getWeightTguiChange(true,"south",gui,json);

            esf::setWeightChangeLabel("north",gui);
            esf::setWeightChangeLabel("east",gui);
            esf::setWeightChangeLabel("west",gui);
            esf::setWeightChangeLabel("south",gui);
        }
    } catch (const tgui::Exception &e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}

void esf::setMainPanelInfo(tgui::Gui &gui, Settings &json) {

    tgui::Label::Ptr label = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
            ->get<tgui::Panel>("mainPanel")->get<tgui::Label>("info");

    if(label != nullptr) {

        int x = json.editor["selected_tile"][0], y = json.editor["selected_tile"][1];

        std::string sTileType = json.editor["selected_type"];
        std::string sTileX = std::to_string(x);
        std::string sTileY = std::to_string(y);

        label->setText("[" + sTileType + "], [" + sTileX + ", " + sTileY + "]");
    }
}

void esf::getPanelTeleport(tgui::Gui &gui, Settings &json, std::string &Tile_Type) {

    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr mainPanel = childWindow->get<tgui::Panel>("mainPanel");
        tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("direction");

        if(panel == nullptr && mainPanel != nullptr){

            panel = theme->load("panel");
            panel->setSize(105,mainPanel->getSize().y);
            panel->setPosition(mainPanel->getSize().x+mainPanel->getPosition().x,mainPanel->getPosition().y);
            panel->setBackgroundColor(color_green);

            tgui::Label::Ptr label = theme->load("label");
            label->setPosition(5,5);
            label->setTextSize(15);
            label->setText("Destination");


            tgui::ListBox::Ptr list = theme->load("ListBox");
            list->setPosition(label->getPosition().x,label->getPosition().y+18);
            list->setSize(panel->getSize().x-10,80);

            tgui::EditBox::Ptr time = theme->load("EditBox");
            time->setPosition(list->getPosition().x,list->getPosition().y+list->getSize().y+5);
            time->setDefaultText("Travel time");
            time->setTextSize(15);
            time->setSize(95,30);
            time->setInputValidator("^[0-9]{0,5}$");

            panel->add(time, "time");
            panel->add(label, "label");
            panel->add(list, "list");
            childWindow->add(panel,"teleport");

            list->connect("ItemSelected", [&](){
                mef::setTileTeleportNext(gui,json);
            });

            time->connect("TextChanged", [&](){
                tgui::EditBox::Ptr temp = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("teleport")->get<tgui::EditBox>("time");

                if( temp != nullptr){
                    std::string text = temp->getText();
                    try {
                        int value = std::stoi(text);
                        mef::setTileValueSpecified(value,13,json);
                    }catch (...){}
                }
            });
        }

        //Updating the list with teleport tiles
        getTeleportList(gui,json, Tile_Type);

        }catch (const tgui::Exception &e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}

void esf::getTeleportList(tgui::Gui &gui, Settings &json, std::string &Tile_Type) {

    tgui::Panel::Ptr panel = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("teleport");
    tgui::ListBox::Ptr list = panel->get<tgui::ListBox>("list");
    tgui::EditBox::Ptr time = panel->get<tgui::EditBox>("time");

    std::vector<int> selection = mef::getAllSpecialTileInfo(sf::Vector2i(json.editor["selected_tile"][0],json.editor["selected_tile"][1]),json,Tile_Type);

    if(list != nullptr){

        std::vector<int> temp = mef::getTeleportTilesPositions(sf::Vector2i(json.editor["selected_tile"][0],json.editor["selected_tile"][1]), json, Tile_Type);

        list->removeAllItems();

        for (int i = 0; i < temp.size(); i += 2) {
            std::string id = std::to_string(temp[i]) +"!"+ std::to_string(temp[i+1]);
            std::string x = "["+std::to_string(temp[i])+", "+std::to_string(temp[i+1])+"]";
            list->addItem(x,id);
            if(selection.size() == 14 && temp[i] == selection[11] && temp[i+1] == selection[12]){
                list->setSelectedItem(x);
            }
        }
    }
    if(time != nullptr && selection.size() == 14){
        std::string text = std::to_string(selection[13]);
        time->setText(text);
    }
}

void esf::getPanelSpeed(tgui::Gui &gui, Settings &json, std::string &Tile_Type) {

    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr mainPanel = childWindow->get<tgui::Panel>("create_splitter");
        tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("speed");

        if(panel == nullptr && mainPanel != nullptr) {

            panel = theme->load("panel");
            panel->setSize(400, mainPanel->getSize().y);
            panel->setPosition(mainPanel->getSize().x + mainPanel->getPosition().x, mainPanel->getPosition().y);
            panel->setBackgroundColor(sf::Color(100, 25, 200));
            childWindow->add(panel, "speed");

            tgui::Label::Ptr lSpeed = theme->load("label");
            lSpeed->setPosition(5,5);
            lSpeed->setText("Speed Buff");
            lSpeed->setTextSize(15);
            panel->add(lSpeed);

            tgui::CheckBox::Ptr boxSpeed = theme->load("CheckBox");
            boxSpeed->setPosition(lSpeed->getPosition().x, lSpeed->getPosition().y + lSpeed->getTextSize() + 8);
            boxSpeed->setSize(25,25);
            panel->add(boxSpeed, "cspeed");

            tgui::Label::Ptr lSlow = tgui::Label::copy(lSpeed);
            lSlow->setPosition(boxSpeed->getPosition().x,boxSpeed->getPosition().y + boxSpeed->getSize().y + 10);
            lSlow->setText("Slow Buff");
            panel->add(lSlow);

            tgui::CheckBox::Ptr boxSlow = tgui::CheckBox::copy(boxSpeed);
            boxSlow->setPosition(lSlow->getPosition().x, lSlow->getPosition().y + lSlow->getTextSize() + 8);
            panel->add(boxSlow, "cslow");


            tgui::EditBox::Ptr eSpeed = theme->load("EditBox");
            eSpeed->setSize(90, boxSpeed->getSize().y);
            eSpeed->setPosition(boxSpeed->getPosition().x + boxSpeed->getSize().x + 15, boxSpeed->getPosition().y);
            eSpeed->setDefaultText("Speed in %");
            eSpeed->setInputValidator("^[0-9]{0,3}$");
            panel->add(eSpeed,"espeed");

            tgui::EditBox::Ptr eSlow = tgui::EditBox::copy(eSpeed);
            eSlow->setPosition(eSpeed->getPosition().x, boxSlow->getPosition().y);
            eSlow->setDefaultText("Slow in %");
            panel->add(eSlow,"eslow");

            tgui::EditBox::Ptr duration = tgui::EditBox::copy(eSpeed);
            duration->setPosition(lSlow->getPosition().x, eSlow->getPosition().y + eSlow->getSize().y + 10);
            duration->setSize(eSlow->getSize().x + (eSlow->getPosition().x - duration->getPosition().x), eSlow->getSize().y);
            duration->setDefaultText("Duration in ms");
            duration->setInputValidator("^[0-9]{0,5}$");
            panel->add(duration,"duration");

            tgui::Slider::Ptr slider_Speed = theme->load("slider");
            slider_Speed->setSize(100,10);
            slider_Speed->setPosition(eSpeed->getSize().x + eSpeed->getPosition().x + 8, eSpeed->getPosition().y +(eSpeed->getSize().y/2.0f) - (slider_Speed->getSize().y/2.0f));
            slider_Speed->setMaximum(100);
            slider_Speed->setMinimum(0);
            panel->add(slider_Speed,"east");

            tgui::Label::Ptr lSlider_speed = theme->load("label");
            lSlider_speed->setTextSize(12);
            lSlider_speed->setPosition(slider_Speed->getPosition().x+slider_Speed->getSize().x-20,slider_Speed->getPosition().y - lSlider_speed->getTextSize() - 3);
            lSlider_speed->setText("100%");
            panel->add(lSlider_speed, "lspeed");

            tgui::Slider::Ptr slider_Slow = tgui::Slider::copy(slider_Speed);
            slider_Slow->setPosition(slider_Speed->getPosition().x, eSlow->getPosition().y +(eSlow->getSize().y/2.0f) - (slider_Slow->getSize().y/2.0f));
            panel->add(slider_Slow,"south");

            tgui::Label::Ptr lSlider_slow = tgui::Label::copy(lSlider_speed);
            lSlider_slow->setPosition(lSlider_speed->getPosition().x,slider_Slow->getPosition().y - lSlider_slow->getTextSize() - 3);
            panel->add(lSlider_slow,"lslow");


            boxSlow->connect("Checked", [&](){
                mef::setTileValueSpecified(1,4,json);
                std::string temp = "speed";
                esf::updatePanels(gui,json,"speed");
            });
            boxSlow->connect("Unchecked", [&](){
                mef::setTileValueSpecified(0,4,json);
                std::string temp = "speed";
                esf::updatePanels(gui,json,"speed");
            });
            boxSpeed->connect("Checked", [&](){
                mef::setTileValueSpecified(1,3,json);
                std::string temp = "speed";
                esf::updatePanels(gui,json,"speed");
            });
            boxSpeed->connect("Unchecked", [&](){
                mef::setTileValueSpecified(0,3,json);
                std::string temp = "speed";
                esf::updatePanels(gui,json,"speed");
            });
            eSlow->connect("TextChanged", [&](){
                tgui::EditBox::Ptr temp = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                        ->get<tgui::Panel>("speed")->get<tgui::EditBox>("eslow");
                std::string s = temp->getText();
                try {
                    int i = std::stoi(s);
                    mef::setTileValueSpecified(i, 6, json);
                } catch (...){}
            });
            eSpeed->connect("TextChanged", [&](){
                tgui::EditBox::Ptr temp = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                        ->get<tgui::Panel>("speed")->get<tgui::EditBox>("espeed");
                std::string s = temp->getText();
                try {
                    int i = std::stoi(s);
                    mef::setTileValueSpecified(i, 5, json);
                } catch (...){}
            });
            duration->connect("TextChanged", [&](){
                tgui::EditBox::Ptr temp = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                        ->get<tgui::Panel>("speed")->get<tgui::EditBox>("duration");
                std::string s = temp->getText();
                try {
                    int i = std::stoi(s);
                    mef::setTileValueSpecified(i, 9, json);
                } catch (...){}
            });

            slider_Speed->connect("ValueChanged", [&]() {
                tgui::Slider::Ptr temp = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                        ->get<tgui::Panel>("speed")->get<tgui::Slider>("east");
                if(temp != nullptr){
                    esf::setWeightSliderChanges("east", "speed", gui);
                    mef::setTileValueSpecified(temp->getValue(), 7, json);

                    tgui::Label::Ptr label = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                            ->get<tgui::Panel>("speed")->get<tgui::Label>("lspeed");
                    if(label != nullptr) label->setText(std::to_string(temp->getValue())+"%");
                }
            });
            slider_Slow->connect("ValueChanged", [&]() {
                tgui::Slider::Ptr temp = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                        ->get<tgui::Panel>("speed")->get<tgui::Slider>("south");
                if(temp != nullptr){
                    esf::setWeightSliderChanges("south", "speed", gui);
                    mef::setTileValueSpecified(temp->getValue(), 8, json);

                    tgui::Label::Ptr label = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                            ->get<tgui::Panel>("speed")->get<tgui::Label>("lslow");
                    if(label != nullptr) label->setText(std::to_string(temp->getValue())+"%");
                }
            });
        }

        if(panel != nullptr){

            tgui::EditBox::Ptr eSlow = panel->get<tgui::EditBox>("eslow");
            tgui::EditBox::Ptr eSpeed = panel->get<tgui::EditBox>("espeed");
            tgui::EditBox::Ptr time = panel->get<tgui::EditBox>("duration");

            tgui::CheckBox::Ptr cSlow = panel->get<tgui::CheckBox>("cslow");
            tgui::CheckBox::Ptr cSpeed = panel->get<tgui::CheckBox>("cspeed");

            tgui::Slider::Ptr sSlow = panel->get<tgui::Slider>("south");
            tgui::Slider::Ptr sSpeed = panel->get<tgui::Slider>("east");

            tgui::Label::Ptr lSlow = panel->get<tgui::Label>("lslow");
            tgui::Label::Ptr lSpeed = panel->get<tgui::Label>("lspeed");

        if(sSlow != nullptr && eSpeed != nullptr && time != nullptr && cSlow != nullptr && cSpeed != nullptr) {

            std::vector<int> vector = mef::getAllSpecialTileInfo(sf::Vector2i(json.editor["selected_tile"][0],json.editor["selected_tile"][1]), json, Tile_Type);

            if(vector.empty() || vector[2] != vector.size()) return;

            if (vector[3] == 1) {
                cSpeed->check();
                eSpeed->enable();
                eSpeed->setOpacity(1);
                sSpeed->setOpacity(1);
                sSpeed->enable();
                sSpeed->setValue(vector[7]);
                if(vector[5] != 0) eSpeed->setText(std::to_string(vector[5]));
                lSpeed->setOpacity(1);
                lSpeed->setText(std::to_string(vector[7]) + "%");

            } else {
                cSpeed->uncheck();
                eSpeed->disable();
                eSpeed->setOpacity(Transparency);
                sSpeed->setOpacity(Transparency);
                sSpeed->disable();
                sSpeed->setValue(vector[7]);
                lSpeed->setOpacity(Transparency);
                lSpeed->setText(std::to_string(vector[7]) + "%");
                if(vector[5] != 0) eSpeed->setText(std::to_string(vector[5]));
            }
            if (vector[4] == 1) {
                cSlow->check();
                eSlow->enable();
                eSlow->setOpacity(1);
                sSlow->setOpacity(1);
                sSlow->enable();
                if(vector[6] != 0) eSlow->setText(std::to_string(vector[6]));
                sSlow->setValue(vector[8]);
                lSlow->setOpacity(1);
                lSlow->setText(std::to_string(vector[8]) + "%");
            } else {
                cSlow->uncheck();
                eSlow->disable();
                eSlow->setOpacity(Transparency);
                sSlow->setOpacity(Transparency);
                sSlow->disable();
                if(vector[6] != 0) eSlow->setText(std::to_string(vector[6]));
                sSlow->setValue(vector[8]);
                lSlow->setOpacity(Transparency);
                lSlow->setText(std::to_string(vector[8]) + "%");
            }
            if (vector[9] != 0) {
                time->setText(std::to_string(vector[9]));
            }
        }
        }
    }catch (const tgui::Exception &e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}

void esf::getPanelDestination(tgui::Gui &gui, Settings &json, std::string &Tile_Type) {
    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr mainPanel = childWindow->get<tgui::Panel>("mainPanel");
        tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("destination");

        if (panel == nullptr && mainPanel != nullptr) {

            panel = theme->load("panel");
            panel->setSize(900, mainPanel->getSize().y);
            panel->setPosition(mainPanel->getSize().x + mainPanel->getPosition().x, mainPanel->getPosition().y);
            panel->setBackgroundColor(sf::Color(100, 25, 200));
            childWindow->add(panel, "destination");

            tgui::Label::Ptr lSpeed = theme->load("label");
            lSpeed->setPosition(5, 5);
            lSpeed->setText("A 2nd chance");
            lSpeed->setTextSize(15);
            panel->add(lSpeed);

            tgui::CheckBox::Ptr box1 = theme->load("CheckBox");
            box1->setPosition(lSpeed->getPosition().x, lSpeed->getPosition().y + lSpeed->getTextSize() + 8);
            box1->setSize(25, 25);
            panel->add(box1, "c1");

            tgui::Label::Ptr lSlow = tgui::Label::copy(lSpeed);
            lSlow->setPosition(box1->getPosition().x, box1->getPosition().y + box1->getSize().y + 10);
            lSlow->setText("Respawn chance");
            panel->add(lSlow);

            tgui::CheckBox::Ptr box2 = tgui::CheckBox::copy(box1);
            box2->setPosition(lSlow->getPosition().x, lSlow->getPosition().y + lSlow->getTextSize() + 8);
            panel->add(box2, "c2");

            tgui::Slider::Ptr slider1 = theme->load("slider");
            slider1->setSize(100, 10);
            slider1->setPosition(box1->getSize().x + box1->
                    getPosition().x + 8, box1->getPosition().y + (box1->getSize().y / 2.0f) - (slider1->getSize().y / 2.0f));
            slider1->setMaximum(100);
            slider1->setMinimum(0);
            panel->add(slider1, "slider1");

            tgui::Label::Ptr label_slider1 = theme->load("label");
            label_slider1->setTextSize(12);
            label_slider1->setPosition(slider1->getPosition().x + slider1->getSize().x - 20,
                                       slider1->getPosition().y - label_slider1->getTextSize() - 3);
            panel->add(label_slider1, "l1");

            tgui::Slider::Ptr slider2 = tgui::Slider::copy(slider1);
            slider2->setPosition(slider1->getPosition().x,
                                     box2->getPosition().y + (box2->getSize().y / 2.0f) -
                                     (slider2->getSize().y / 2.0f));
            panel->add(slider2, "slider2");

            tgui::Label::Ptr label_slider2 = tgui::Label::copy(label_slider1);
            label_slider2->setPosition(label_slider1->getPosition().x,
                                      slider2->getPosition().y - label_slider2->getTextSize() - 3);
            panel->add(label_slider2, "l2");

            tgui::Label::Ptr god_mode = theme->load("label");
            god_mode->setPosition(slider1->getPosition().x + slider1->getSize().x + 10, slider1->getPosition().y -
                                                                                        (god_mode->getTextSize() / 2.0f));
            god_mode->setTextSize(25);
            god_mode->setTextColor(sf::Color(241,196,15));
            god_mode->setText("Weakness detected");
            panel->add(god_mode, "god_mode");

            box2->connect("Checked", [&]() {
                mef::setTileValueSpecified(1, 4, json);
                esf::updatePanels(gui, json, "destination");
            });
            box2->connect("Unchecked", [&]() {
                mef::setTileValueSpecified(0, 4, json);
                esf::updatePanels(gui, json, "destination");
            });
            box1->connect("Checked", [&]() {
                mef::setTileValueSpecified(1, 3, json);
                esf::updatePanels(gui, json, "destination");
            });
            box1->connect("Unchecked", [&]() {
                mef::setTileValueSpecified(0, 3, json);
                esf::updatePanels(gui, json, "destination");
            });
            slider1->connect("ValueChanged", [&]() {
                tgui::Slider::Ptr temp = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                        ->get<tgui::Panel>("destination")->get<tgui::Slider>("slider1");
                if (temp != nullptr) {
                    mef::setTileValueSpecified(temp->getValue(), 5, json);
                    tgui::Label::Ptr label = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                            ->get<tgui::Panel>("destination")->get<tgui::Label>("l1");
                    if (label != nullptr) label->setText(std::to_string(temp->getValue()) + "%");
                    tgui::Label::Ptr label2 = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                            ->get<tgui::Panel>("destination")->get<tgui::Label>("god_mode");
                    if(label2 != nullptr){
                        if(temp->getValue() >= 50) label2->setOpacity(1);
                        else label2->setOpacity(0);
                    }
                }
            });
            slider2->connect("ValueChanged", [&]() {
                tgui::Slider::Ptr temp = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                        ->get<tgui::Panel>("destination")->get<tgui::Slider>("slider2");
                if (temp != nullptr) {
                    mef::setTileValueSpecified(temp->getValue(), 6, json);

                    tgui::Label::Ptr label = gui.get<tgui::ChildWindow>(selectedTileChildWindow)
                            ->get<tgui::Panel>("destination")->get<tgui::Label>("l2");
                    if (label != nullptr) label->setText(std::to_string(temp->getValue()) + "%");
                }
            });
        }
            if(panel != nullptr){

                tgui::CheckBox::Ptr box2 = panel->get<tgui::CheckBox>("c2");
                tgui::CheckBox::Ptr box1 = panel->get<tgui::CheckBox>("c1");

                tgui::Slider::Ptr slider2 = panel->get<tgui::Slider>("slider2");
                tgui::Slider::Ptr slider1 = panel->get<tgui::Slider>("slider1");

                tgui::Label::Ptr label2 = panel->get<tgui::Label>("l2");
                tgui::Label::Ptr label1 = panel->get<tgui::Label>("l1");
                tgui::Label::Ptr god_label = panel->get<tgui::Label>("god_mode");

                if(box2 != nullptr && time != nullptr && box1 != nullptr && slider2 != nullptr && slider1 != nullptr) {

                    std::vector<int> vector = mef::getAllSpecialTileInfo(sf::Vector2i(json.editor["selected_tile"][0],json.editor["selected_tile"][1]), json, Tile_Type);

                    if(vector.empty() || vector[2] != vector.size()) return;

                    if (vector[3] == 1) {
                        box1->check();
                        slider1->setOpacity(1);
                        slider1->enable();
                        slider1->setValue(vector[5]);
                        label1->setOpacity(1);
                        label1->setText(std::to_string(vector[5]) + "%");
                        if(vector[5] >= 50) god_label->setOpacity(1);

                    } else {
                        box1->uncheck();
                        slider1->setOpacity(Transparency);
                        slider1->disable();
                        slider1->setValue(vector[5]);
                        label1->setOpacity(Transparency);
                        label1->setText(std::to_string(vector[5]) + "%");
                        god_label->setOpacity(0);
                    }
                    if (vector[4] == 1) {
                        box2->check();
                        slider2->setOpacity(1);
                        slider2->enable();
                        slider2->setValue(vector[6]);
                        label2->setOpacity(1);
                        label2->setText(std::to_string(vector[6]) + "%");
                    } else {
                        box2->uncheck();
                        slider2->setOpacity(Transparency);
                        slider2->disable();
                        slider2->setValue(vector[6]);
                        label2->setOpacity(Transparency);
                        label2->setText(std::to_string(vector[6]) + "%");
                    }
                }
            }
    } catch (...){

    }
}

void esf::getPanelSelectPlayers(tgui::Gui &gui, Settings &json, std::string &Tile_Type) {

    try {
        tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>(selectedTileChildWindow);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr mainPanel = childWindow->get<tgui::Panel>("mainPanel");
        tgui::Panel::Ptr panel = childWindow->get<tgui::Panel>("players");

        if (panel == nullptr && mainPanel != nullptr) {

            panel = theme->load("panel");
            panel->setSize(105, mainPanel->getSize().y);
            panel->setPosition(mainPanel->getSize().x + mainPanel->getPosition().x, mainPanel->getPosition().y);
            panel->setBackgroundColor(color_green);
            childWindow->add(panel, "players");

        }
        if (panel != nullptr) {
            panel->removeAllWidgets();

            if (!json.map["divided"]) {
                tgui::Label::Ptr label = theme->load("label");
                label->setPosition(5, 20);
                label->setTextSize(10);
                label->setText("Players are\nshearing spawns\n\nTools->\nPlayers/Monster");
                panel->add(label,"2");
            }
            else {

                tgui::Label::Ptr label = theme->load("label");
                label->setPosition(1,2);
                label->setTextSize(15);
                label->setText("Owned by");
                panel->add(label,"info");

                std::vector<bool> list = mef::getPlayersSelected(sf::Vector2i(json.editor["selected_tile"][0],json.editor["selected_tile"][1]), json,Tile_Type, json.map["team"]);

                int posX = 5;
                int posY = 20;
                if(!json.map["team"]) {
                    for (int i = 1; i <= MAX_PLAYERS; ++i) {
                        tgui::CheckBox::Ptr temp = theme->load("CheckBox");
                        temp->setSize(20, 20);
                        temp->setPosition(posX, posY);
                        temp->setText(std::to_string(i));

                        if(list.size() >= i && list[i-1]) temp->check();

                        if(i > json.map["players"]){
                            temp->disable();
                            temp->setOpacity(0.5f);
                        }

                        temp->connect("checked", &mef::setTileValuePlayers, std::ref(gui), std::ref(json));
                        temp->connect("unchecked", &mef::setTileValuePlayers, std::ref(gui), std::ref(json));

                        panel->add(temp,std::to_string(i));

                        posX += 40;
                        if (i % 2 == 0 && i > 0) {
                            posX = 5;
                            posY += 25;
                        }
                    }
                }
                else{
                    for (int i = 1; i <= 5; ++i) {
                        tgui::CheckBox::Ptr temp = theme->load("CheckBox");
                        temp->setSize(20, 20);
                        temp->setPosition(posX, posY);
                        temp->setText("Team " + std::to_string(i));

                        if(list.size() >= i && list[i-1]) temp->check();

                        if(i > json.map["teams"]){
                            temp->disable();
                            temp->setOpacity(0.5f);
                        }

                        temp->connect("checked", &mef::setTileValuePlayers, std::ref(gui), std::ref(json));
                        temp->connect("unchecked", &mef::setTileValuePlayers, std::ref(gui), std::ref(json));

                        panel->add(temp,std::to_string(i));
                        posY += 25;
                    }
                }
            }
        }

    }catch (const tgui::Exception &e) {

        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI Tile view creation crashed");
    }
}








