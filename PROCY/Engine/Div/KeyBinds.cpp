//
// Created by Chrim14 on 04.12.2017.
//

#include "KeyBinds.h"


std::vector<std::string> KeyBinds::getJsonKeyNames() {

    std::vector<std::string> vector {"Escape", "Up", "Down", "Left", "Right", "Multi-Build", "Info", "Build-Highlight", "Mute", "Stats","Panel_12", "Panel_1",
                                     "Panel_2","Panel_3","Panel_4","Panel_5","Panel_6","Panel_7","Panel_8",
                                     "Panel_9","Panel_10","Panel_11"};
    return vector;
}


void KeyBinds::setKeys(json &keys) {

    keys["Escape"] = sf::Keyboard::Escape;
    keys["Up"] = sf::Keyboard::W;
    keys["Down"] = sf::Keyboard::S;
    keys["Left"] = sf::Keyboard::A;
    keys["Right"] = sf::Keyboard::D;
    keys["Multi-Build"] = sf::Keyboard::LShift;

    keys["Panel_1"] = sf::Keyboard::Num1;
    keys["Panel_2"] = sf::Keyboard::Num2;
    keys["Panel_3"] = sf::Keyboard::Num3;
    keys["Panel_4"] = sf::Keyboard::Num4;
    keys["Panel_5"] = sf::Keyboard::Num5;
    keys["Panel_6"] = sf::Keyboard::Num6;
    keys["Panel_7"] = sf::Keyboard::Num7;
    keys["Panel_8"] = sf::Keyboard::Num8;
    keys["Panel_9"] = sf::Keyboard::Num9;
    keys["Panel_10"] = sf::Keyboard::Num0;
    keys["Panel_11"] = sf::Keyboard::Add;
    keys["Panel_12"] = sf::Keyboard::BackSlash;

    keys["Info"] = sf::Keyboard::F3;
    keys["Build-Highlight"] = sf::Keyboard::F4;
    keys["Mute"] = sf::Keyboard::M;
    keys["Stats"] = sf::Keyboard::Tab;

    //<<<<<77keys["zoom_up"] = sf::Event::
    //keys["zoom_down"] = sf::Keyboard::A;
}

void KeyBinds::getKeys(json &Keys) {

    std::string filePathLanguage = "Texture/KeyBinds.json";

    try {
        if (std::ifstream(filePathLanguage)) {
            lInfo("Getting KeyBind file information");
            std::ifstream file(filePathLanguage);
            file >> Keys;
            KeyBinds::controllKeyFile(Keys);

            return;
        }
    }
    catch (...){
    }
    KeyBinds::setKeys(Keys);
    KeyBinds::saveKeysToFile(Keys);
}

void KeyBinds::controllKeyFile(json &Keys) {

    json fileKeys = Keys;
    KeyBinds::setKeys(Keys);

    bool noError = true;

    for (json::iterator it = Keys.begin(); it != Keys.end();it++) {

        for (json::iterator it2 = fileKeys.begin(); it2 != fileKeys.end();it2++) {

            if(it.key() == it2.key()){
                if(it.value().type_name() != it2.value().type_name()) {
                    lWarning("Key object '"+it2.key()+"' was data type "+ it2.value().type_name()+" wanted "+it.value().type_name());
                    fileKeys.erase(it2);
                }
                break;
            }
        }
    }

    std::vector<std::string> original;

    //Adding all language objects from file in a std::vector
    for (json::iterator it = fileKeys.begin(); it != fileKeys.end();it++) {
        original.push_back(it.key());
    }

    //comparing standard language objects with the original language objects
    for (json::iterator it = Keys.begin(); it != Keys.end();it++) {

        if(original.empty()){
            noError = false;
            lWarning("Key object was missing: " + it.key());
            fileKeys[it.key()] = it.value();
        }

        for (auto it2 = original.begin(); it2 != original.end(); it2++){

            if(it.key() == it2->data()){
                original.erase(it2);
                break;
            }

            else if(std::next(it2) == original.end()){
                noError = false;
                lWarning("Key object was missing: " + it.key());
                fileKeys[it.key()] = it.value();
            }
        }
    }

    Keys = fileKeys;

    if(!noError)
        KeyBinds::saveKeysToFile(Keys);
}

void KeyBinds::saveKeysToFile(json &Keys) {

    std::ofstream file("Texture/KeyBinds.json");

    if(!file){
        lWarning("File KeyBinds.json could not be created");
        return;
    }

    file << std::setw(4) << Keys << std::endl;
}

std::string KeyBinds::getKeyName(int key_code) {

    std::vector<std::string> key_list = {
            "Unknown", "A", "B", "C", "D", "E", "F", "G", "H",
            "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
            "S", "T", "U", "V", "W", "X", "Y", "Z", "Num0",
            "Num1", "Num2", "Num3", "Num4", "Num5", "Num6",
            "Num7", "Num8", "Num9", "Escape", "LControl", "LShift",
            "LAlt", "LSystem", "RControl", "RShift", "RAlt",
            "RSystem", "Menu", "LBracket", "RBracket", "SemiColon",
            "Comma", "Period", "Quote", "Slash", "BackSlash",
            "Tilde", "Equal", "Dash", "Space", "Return", "BackSpace",
            "Tab", "PageUp", "PageDown", "End", "Home", "Insert",
            "Delete", "Add", "Subtract", "Multiply", "Divide", "Left",
            "Right", "Up", "Down", "Numpad0", "Numpad1", "Numpad2",
            "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7",
            "Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6",
            "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15",
            "Pause", "KeyCount"};

    if(key_code+1 >= key_list.size())
        return key_list.at(0);

    return key_list.at(static_cast<unsigned long long int>(key_code + 1));
}
