//
// Created by Chrim14 on 10.10.2017.
//

#include "MapEditorStaticFunctions.h"
#include "../Map/Map.h"
#include "../Map/MapStaticFunctions.h"
#define selectedTileChildWindow "selectedTileChildWindow"

void mef::setTileClickInfo(sf::Vector2f &Mouse_pointer, Settings &json) {

    if(mf::isMousePointerInsideMap(Mouse_pointer,json))
    {
        sf::Vector2i temp = mf::getMapTilesCoordinates(Mouse_pointer, json);
        unsigned int value = mf::getBitTileFocusedValue(Mouse_pointer, json);

        if (value != Layer_Two_Size) {

            json.editor["tile_x"] = temp.x;
            json.editor["tile_y"] = temp.y;

            json.editor["tile_type"] = mf::getBitNameFromValue(value);
            json.editor["tile_id"] = mf::getTileValue(temp, json);

        }
    }
}


///Warning: bit value change mf::getBitValueFromType, mf::getBitNameFromValue, mef::setSpecialTile
void mef::setSpecialTile(unsigned int &bitValue, sf::Vector2f &Mouse_pointer , Settings &json) {

    unsigned int bit_Focused_value = mf::getBitTileFocusedValue(Mouse_pointer,json);

    if(bit_Focused_value != bitValue) {
        if (bit_Focused_value != 0 && bit_Focused_value != 8 && bit_Focused_value != 1) {

            removeSpecialTile(Mouse_pointer, json, mf::getBitNameFromValue(bit_Focused_value));

        }
        switch (bitValue) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                setValueSpawn(json);
                break;
            case 4:
                setValueDestination(json);
                break;
            case 5:
                setValueTeleport(json);
                break;
            default:
                break;
        }
    }
}


void mef::removeSpecialTile(sf::Vector2f &Mouse_pointer, Settings &json,const std::string type) {

    sf::Vector2i temp = mf::getMapTilesCoordinates(Mouse_pointer, json);
    if(!json.map[type].empty()) {

        int length = json.map[type][2];

        for (int i = 0; i < json.map[type].size(); i += length) {

            if (json.map[type][i] == temp.x && json.map[type][i + 1] == temp.y) {

                json.map[type].erase(json.map[type].begin() + i, json.map[type].begin() + i + length);

                std::cout << "Size left: " << json.map[type].size() << std::endl;

                break;
            }
        }
    }
}


void mef::setValueDestination(Settings &json) {

    json.map["destination"] += json.editor["tile_x"];
    json.map["destination"] += json.editor["tile_y"];

    json.map["destination"] += 7;

    json.map["destination"] += 0;
    json.map["destination"] += 0;
    json.map["destination"] += 0;
    json.map["destination"] += 0;
}


std::vector<sf::Vector2i> mef::getAllSelectedTileType(Settings &json, std::string &type) {

    std::vector<sf::Vector2i> temp;
    try {
        if (!json.map.at(type).empty()) {

            int length = json.map[type][2];

            for (int i = 0; i < json.map[type].size(); i += length) {
                temp.emplace_back(json.map[type][i],json.map[type][i+1]);
            }
            return temp;
        }
    }catch (...){
        lError("mef::getAllSelectedTileType, Could not get info");
        std::cerr << "failed " << __LINE__ << " " << __FILE__ << "\n";
    }
    return temp;
}


std::vector<int> mef::getTileDirection(sf::Vector2i position, Settings &json, std::string &type) {

    try {
        if (!json.map[type].empty()) {

            int length = json.map[type][2];

            for (int i = 0; i < json.map[type].size(); i += length) {

                if (json.map[type][i] == position.x && json.map[type][i + 1] == position.y) {

                    return std::vector<int> {json.map[type][i + 3], json.map[type][i + 4], json.map[type][i + 5],
                                             json.map[type][i + 6]};
                }
            }
        }
    }catch (...){
        lError("Could not get direction of "+type+" tile");
    }
    return std::vector<int> {};
}


std::vector<int> mef::getTileWeights(sf::Vector2i position, Settings &json, std::string &type) {

    try {
        if (!json.map[type].empty()) {

            int length = json.map[type][2];

            for (int i = 0; i < json.map[type].size(); i += length) {

                if (json.map[type][i] == position.x && json.map[type][i + 1] == position.y) {
                    return std::vector<int> {json.map[type][i + 7], json.map[type][i + 8], json.map[type][i + 9],
                                             json.map[type][i + 10]};
                }
            }
        }
    }catch (...){
        lError("Could not get direction of "+type+" tile");
    }
    return std::vector<int>{};
}


std::vector<int> mef::getTeleportTilesPositions(sf::Vector2i position, Settings &json, std::string &type) {

    try {
        if (!json.map.at(type).empty()) {

            std::vector<int> temp;

            int length = json.map[type][2];

            for (int i = 0; i < json.map[type].size(); i += length) {

            if(json.map[type][i] != position.x || json.map[type][i+1] != position.y){
                    temp.push_back(json.map[type][i]);
                    temp.push_back(json.map[type][i+1]);
                }
            }
            return temp;
        }
    }catch (...){
        lError("mef::getTeleportTilesPositions, Could not get teleport list");
    }
    return std::vector<int>{};
}


std::vector<int> mef::getAllSpecialTileInfo(sf::Vector2i position, Settings &json, std::string &type) {

    try {

        if (!json.map[type].empty()) {

            std::vector<int> temp;

            int length = json.map[type][2];

            for (int i = 0; i < json.map[type].size(); i += length) {

                if(json.map[type][i] == position.x && json.map[type][i+1] == position.y){

                    for (int j = i; j < length+i; ++j) {
                        temp.push_back(json.map[type][j]);
                    }
                    return temp;
                }
            }
        }
    }catch (...){
        lError("mef::getTeleportTilesPositions, Could not get teleport list");
    }
    return std::vector<int>{};
}


std::vector<bool> mef::getPlayersSelected(sf::Vector2i position, Settings &json, std::string &type, bool teams) {


    if (!json.map[type].empty()) {

        int length = json.map[type][2];

        std::vector<bool> list;

        for (int i = 0; i < json.map[type].size(); i += length) {

            if (json.map[type][i] == position.x && json.map[type][i + 1] == position.y) {

                //Getting out the value, value to large to store only in int
                long long int data = json.map[type][i + 11 + teams];
                //Changing the data type to string, for iterating reasons
                std::string value = std::to_string(data);

                //Starting at 1 since first element is 2
                for (int j = 1; j <= value.length(); ++j) {
                    list.push_back(value[j] == 49); //49 == 1 in ASCII
                }
                return list;
            }
        }
    }
    return std::vector<bool>{};
}


void mef::setTileDirection(int direction, Settings &json) {

    std::string selected_tile = json.editor["selected_type"];

    try {
        if (!json.map[selected_tile].empty()) {

            int length = json.map[selected_tile][2];

            for (int i = 0; i < json.map[selected_tile].size(); i += length) {

                if (json.map[selected_tile][i] == json.editor["selected_tile"][0] && json.map[selected_tile][i + 1] == json.editor["selected_tile"][1]) {
                    if(json.map[selected_tile][i+3+direction] == 0)
                        json.map[selected_tile][i+3+direction] = 1;
                    else
                        json.map[selected_tile][i+3+direction] = 0;
                    return;
                }
            }
        }
    }catch (...){
        lError("Could not get direction of "+selected_tile+" tile");
    }
}


void mef::setTileWeights(int direction, int value, Settings &json) {

    std::string selected_tile = json.editor["selected_type"];

    try {
        if (!json.map[selected_tile].empty()) {

            int length = json.map[selected_tile][2];

            for (int i = 0; i < json.map[selected_tile].size(); i += length) {

                if (json.map[selected_tile][i] == json.editor["selected_tile"][0] && json.map[selected_tile][i + 1] == json.editor["selected_tile"][1]) {
                    json.map[selected_tile][i+7+direction] = value;
                    return;
                }
            }
        }
    }catch (...){
        lError("Could not get weights of "+selected_tile+" tile");
    }
}


void mef::setTileTeleportNext(tgui::Gui &gui, Settings &json) {

    std::string selected_tile = json.editor["selected_type"];

    tgui::Panel::Ptr panel = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("teleport");
    tgui::ListBox::Ptr list = panel->get<tgui::ListBox>("list");

    std::string text = list->getSelectedItemId();

    if(text.empty()) return;

    int X_Position = -1;
    int Y_Position = -1;
    std::string position;

    try {
        for (const auto &temp : text) {
            if (temp != 33) {
                position += temp;
            }
            else{
                X_Position = std::stoi(position);
                position.clear();
            }
        }
        Y_Position = std::stoi(position);
    } catch (...){
        lError("mef::setTileTeleportNext, some value failed: "+text);
        return;
    }

    if (!json.map[selected_tile].empty()) {

        int length = json.map[selected_tile][2];

        for (int i = 0; i < json.map[selected_tile].size(); i += length) {

            if (json.map[selected_tile][i] == json.editor["selected_tile"][0] && json.map[selected_tile][i + 1] == json.editor["selected_tile"][1]) {

                json.map[selected_tile][i+11] = X_Position;
                json.map[selected_tile][i+12] = Y_Position;
                return;
            }
        }
    }
}


void mef::setTileValueSpecified(int value, int position, Settings &json) {

    std::string selected_tile = json.editor["selected_type"];

    try {
        if (!json.map[selected_tile].empty()) {

            int length = json.map[selected_tile][2];

            for (int i = 0; i < json.map[selected_tile].size(); i += length) {

                if (json.map[selected_tile][i] == json.editor["selected_tile"][0] && json.map[selected_tile][i + 1] == json.editor["selected_tile"][1]) {
                    json.map[selected_tile][i+position] = value;
                    return;
                }
            }
        }
    }catch (...){
        lError("Could not get weights of "+selected_tile+" tile");
    }
}


void mef::setTileValuePlayers(tgui::Gui &gui, Settings &json) {

    std::string selected_tile = json.editor["selected_type"];

    tgui::Panel::Ptr panel = gui.get<tgui::ChildWindow>(selectedTileChildWindow)->get<tgui::Panel>("players");

    std::vector<bool> checked;

    for (int j = 1; j <= MAX_PLAYERS; ++j) {
        tgui::CheckBox::Ptr temp = panel->get<tgui::CheckBox>(std::to_string(j));
        checked.push_back(temp != nullptr && temp->isChecked());
    }

    int string_position = 11;
    if(json.map["team"]) string_position = 12;

    //extra data on first element to not lose data if the first players are not selected.
    std::string data_string = "2";

    if (!json.map[selected_tile].empty()) {

        int length = json.map[selected_tile][2];

        for (int i = 0; i < json.map[selected_tile].size(); i += length) {

            if (json.map[selected_tile][i] == json.editor["selected_tile"][0] && json.map[selected_tile][i + 1] == json.editor["selected_tile"][1]) {

                //Filling in rest of the true elements
                for (int j = 0; j < checked.size(); ++j) {
                    data_string += std::to_string(checked[j]);
                }
                json.map[selected_tile][i+string_position] = std::stoll(data_string);
                return;
            }
        }
    }
}


void mef::setValueDirection(Settings &json) {

    json.map["divider"] += json.editor["tile_x"];
    json.map["divider"] += json.editor["tile_y"];

    json.map["divider"] += 11;

    json.map["divider"] += 1;
    json.map["divider"] += 0;
    json.map["divider"] += 0;
    json.map["divider"] += 0;

    json.map["divider"] += 100;
    json.map["divider"] += 0;
    json.map["divider"] += 0;
    json.map["divider"] += 0;

    unsigned int x = json.editor["tile_x"];
    unsigned int y = json.editor["tile_y"];

    for (int i = 0; i < Bits_To_Tiles; ++i) {
        for (int j = 0; j < Bits_To_Tiles; ++j) {
            json.bitTileValue[x*Bits_To_Tiles+j][y*Bits_To_Tiles+i] = 6;
        }
    }
}


void mef::setValueSpeed(Settings &json) {

    json.map["speed"] += json.editor["tile_x"];
    json.map["speed"] += json.editor["tile_y"];

    json.map["speed"] += 10;

    json.map["speed"] += 0;
    json.map["speed"] += 0;
    json.map["speed"] += 0;
    json.map["speed"] += 0;
    json.map["speed"] += 0;
    json.map["speed"] += 0;
    json.map["speed"] += 0;


    unsigned int x = json.editor["tile_x"];
    unsigned int y = json.editor["tile_y"];

    for (int i = 0; i < Bits_To_Tiles; ++i) {
        for (int j = 0; j < Bits_To_Tiles; ++j) {
            json.bitTileValue[x*Bits_To_Tiles+j][y*Bits_To_Tiles+i] = 7;
        }
    }
}


void mef::setValueTeleport(Settings &json) {

    json.map["teleport"] += json.editor["tile_x"];

    json.map["teleport"] += json.editor["tile_y"];

    json.map["teleport"] += 14;

    json.map["teleport"] += 0;
    json.map["teleport"] += 0;
    json.map["teleport"] += 0;
    json.map["teleport"] += 0;

    json.map["teleport"] += 0;
    json.map["teleport"] += 0;
    json.map["teleport"] += 0;
    json.map["teleport"] += 0;

    json.map["teleport"] += 0; //To X position
    json.map["teleport"] += 0; //To Y position

    json.map["teleport"] += 0; //travel time
}


void mef::setValueSpawn(Settings &json) {

    json.map["spawn"] += json.editor["tile_x"];
    json.map["spawn"] += json.editor["tile_y"];

    json.map["spawn"] += 13;

    json.map["spawn"] += 0;
    json.map["spawn"] += 1;
    json.map["spawn"] += 0;
    json.map["spawn"] += 0;

    json.map["spawn"] += 0;
    json.map["spawn"] += 100;
    json.map["spawn"] += 0;
    json.map["spawn"] += 0;

    json.map["spawn"] += 0;
    json.map["spawn"] += 0;
}
