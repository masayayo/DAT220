//
// Created by Chrim14 on 09.11.2017.
//

#include "Language.h"

///From: Settings::getLanguagePacket
///Function: create standar language pack for english settings
void Language::setLanguage(json &language) {

    language["singleplayer"] = "Singleplayer";
    language["multiplayer"] = "Multiplayer";
    language["options"] = "Options";
    language["exit"] = "Exit";
    language["back"] = "Back";
    language["settings"] = "Settings";
    language["mapeditor"] = "Mapeditor";

    //Settings
    language["resolution"] = "Resolution";
    language["fullscreen"] = "Full Screen";
    language["language"] = "Language";
    language["keybinding"] = "Key Bindings";
    language["music"] = "Music";
    language["sound"] = "Sound";
    language["volum"] = "Volum";
    language["restore"] = "Restore";
    language["apply"] = "Apply";
    //language["yes"] = "yes";
   // language["no"] = "no";
    language["video"] = "Video";
    language["game"] = "Game";
    language["antialiasing"] = "Anti Aliasing";
    language["none"] = "None";
    language["fps"] = "Fps";
    language["unlimited"] = "Unlimited";
    language["Vsync"] = "V-Sync";
    language["smooth-texture"] = "Smooth Texture";
    language["draw-bullets"] = "Draw bullets";
    language["mute"] = "Mute";
    language["system"] = "System";
    language["view-speed"] = "View Speed";
    language["zoom-speed"] = "Zoom Speed";
    language["start-view"] = "Start View";
    language["player-name"] = "Player name";
    //language[""] = "";

    language["host"] = "Host";
    language["join"] = "Join";
    language["game"] = "Game";
    language["new"] = "New";
    language["load"] = "Load";
    language["save"] = "Save";
    language["file"] = "File";
    language["start"] = "Start";
    language["continue"] = "Continue";

    language["title"] = "Tower Defence";
    language["packet"] = "Language packets";

    //Map editor
    language["create"] = "Create";
    language["loadmap"] = "Load file";
    language["newmap"] = "New map";
    language["height"] = "Height";
    language["length"] = "Length";
    language["starttile"] = "Start tile";

    language["findFile"] = "Find file";
    language["saveFile"] = "Save file";
    language["editText"] = "example: Best map ever";
    language["menu"] = "Menu";

}

///From: Settings::Settings, SettingButtons::applySelectedLanguage
///Function: get language pack from file and call controller, if failed creating new packet
void Language::getLanguage(json &language, json &setting) {

    std::string temp = setting["language"];
    std::string filePathLanguage = "Texture/Language/"+temp+".json";

    try {
        if (std::ifstream(filePathLanguage)) {
            lInfo("Getting Language file information");
            std::ifstream file(filePathLanguage);
            file >> language;

            Language::controllLanguageFile(language, setting);

            return;
        }
    }
    catch (...){

        if(temp != "English"){
            lWarning("Language pack "+temp+" corrupt, turning back to english");

            //TODO: Simen, gi en beskjed at språkpakken ikke stemmer og at det er blitt byttet over til engelsk

            setting["language"] = "English";
            Language::getLanguage(language,setting);
        }
        else{
            if( std::remove("Texture/Language/English.json") != 0){
                lFatal("English language pack corrupt, could not deleted it");
            }
            else{
                lWarning("English language pack corrupt, deleted it");
                //TODO: Simen, gi en beskjed at språkpakken ikke stemmer, derfor slettes den
            }
        }
    }
    Language::setLanguage(language);
    Language::saveLanguageToFile(language,setting);
}

///Usage: Settings::getLanguagePacket
///Function: control if language pack have all element needed, if not replace missing objects
void Language::controllLanguageFile(json &language, json &setting) {

    json fileLanguage = language;
    Language::setLanguage(language);

    bool noError = true;


    for (json::iterator it = language.begin(); it != language.end();it++) {

        for (json::iterator it2 = fileLanguage.begin(); it2 != fileLanguage.end();it2++) {

            if(it.key() == it2.key()){
                if(it.value().type_name() != it2.value().type_name()) {
                    lWarning("Language object '"+it2.key()+"' was data type "+ it2.value().type_name()+" wanted "+it.value().type_name());
                    fileLanguage.erase(it2);
                }
                break;
            }
        }
    }

    std::vector<std::string> original;

    //Adding all language objects from file in a std::vector
    for (json::iterator it = fileLanguage.begin(); it != fileLanguage.end();it++) {
        original.push_back(it.key());
    }

    //comparing standard language objects with the original language objects
    for (json::iterator it = language.begin(); it != language.end();it++) {

        if(original.empty()){
            noError = false;
            lWarning("Language object was missing: " + it.key());
            fileLanguage[it.key()] = it.value();
        }

        for (auto it2 = original.begin(); it2 != original.end(); it2++){

            if(it.key() == it2->data()){
                original.erase(it2);
                break;
            }

            else if(std::next(it2) == original.end()){
                noError = false;
                lWarning("Language object was missing: " + it.key());
                fileLanguage[it.key()] = it.value();
            }
        }
    }

    language = fileLanguage;

    if(!noError)
        Language::saveLanguageToFile(language, setting);
}

///From: Settings::getLanguagePacket && Settings::controlLanguagePacket
///Function: saving language to .json file.
void Language::saveLanguageToFile(json &language, json &setting) {
    std::string temp = setting["language"];
    std::ofstream file("Texture/Language/"+temp+".json");

    if(!file){
        lWarning("File settings.json could not be created");
        return;
    }

    file << std::setw(4) << language << std::endl;
}
