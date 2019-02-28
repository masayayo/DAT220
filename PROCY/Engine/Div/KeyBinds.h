//
// Created by Admin on 04.12.2017.
//

#ifndef PROCY_KEYBINDS_H
#define PROCY_KEYBINDS_H


#include "../Settings.h"


class KeyBinds {
public:
    static std::vector<std::string> getJsonKeyNames();

    static void setKeys(json &Keys);

    static void getKeys(json &Keys);

    static void controllKeyFile(json &Keys);

    static void saveKeysToFile(json &Keys);

    static std::string getKeyName(int key_code);
};


#endif //PROCY_KEYBINDS_H
