//
// Created by Chrim14 on 09.11.2017.
//

#ifndef PROCY_LANGUAGE_H
#define PROCY_LANGUAGE_H


#include "../Settings.h"

class Language {
public:
    static void setLanguage(json &Language);

    static void getLanguage(json &Language, json &setting);

    static void controllLanguageFile(json &Language, json &setting);

    static void saveLanguageToFile(json &language, json &setting);
};


#endif //PROCY_LANGUAGE_H
