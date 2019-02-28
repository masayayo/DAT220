//
// Created by Chrim14 on 08.10.2017.
//

#include "SettingButtons.h"


void SettingButtons::applySettings(bool reset, sf::RenderWindow &window, tgui::Gui &gui, Settings &json, Sound &sound) {

    Settings jsonControl;

    if(reset){
        json.standardSettings();
        json.saveSettings();
    }

    std::string title = json.language["title"];
    std::string version = json.setting["version"];
    title = title +" "+version;

    sf::ContextSettings settings;
    settings.antialiasingLevel = json.setting["anti"];

        //if fullscreen mode and going to windowed
    if(!json.setting["wFullScreen"] && jsonControl.setting["wFullScreen"] || json.setting["anti"] != jsonControl.setting["anti"] && !json.setting["wFullScreen"]) {
        window.create({json.setting["wWidth"], json.setting["wHeight"]},  sf::String::fromUtf8(title.begin(),title.end()), sf::Style::Close, settings);
        window.setIcon(512,512,json.image["icon"].getPixelsPtr());
    }
        //If resolution is changed
    else if(json.setting["wWidth"] != jsonControl.setting["wWidth"]){
        window.setSize(sf::Vector2u(json.setting["wWidth"], json.setting["wHeight"]));

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

        if(window.getPosition().x + window.getSize().x > desktop.width){
            window.setPosition(sf::Vector2i(window.getPosition().x - ((window.getPosition().x + window.getSize().x) - desktop.width),window.getPosition().y - ((window.getPosition().y + window.getSize().y) - desktop.height)));
        }
    }
    if(json.setting["wFullScreen"] && (json.setting["wWidth"] != jsonControl.setting["wWidth"] || !jsonControl.setting["wFullScreen"] || (json.setting["anti"] != jsonControl.setting["anti"]))){
        window.create({json.setting["wWidth"], json.setting["wHeight"]},  sf::String::fromUtf8(title.begin(),title.end()), sf::Style::Fullscreen, settings);
        window.setIcon(512,512,json.image["icon"].getPixelsPtr());
    }


    json.view["fixed"].reset(sf::FloatRect(0,0, json.setting["wWidth"],json.setting["wHeight"]));
    gui.setView(json.view["fixed"]);

    if(reset) json.setting["language"] = jsonControl.setting["language"];

    window.setMouseCursorVisible(false); // Hide cursor

    window.setFramerateLimit(json.setting["fps"]);
    window.setVerticalSyncEnabled(json.setting["sync"]);

    if(json.setting["texture"] != jsonControl.setting["texture"]){
        json.texture["tiles"].setSmooth(json.setting["texture"]);
        json.texture["pointer"].setSmooth(json.setting["texture"]);
        json.texture["paladin"].setSmooth(json.setting["texture"]);
        json.texture["player"].setSmooth(json.setting["texture"]);
        json.texture["miniMapFrame"].setSmooth(json.setting["texture"]);
        json.texture["progressBar"].setSmooth(json.setting["texture"]);
        json.texture["bullet"].setSmooth(json.setting["texture"]);
        json.texture["tower_1"].setSmooth(json.setting["texture"]);
        json.texture["tower_2"].setSmooth(json.setting["texture"]);
        json.texture["tower_3"].setSmooth(json.setting["texture"]);
        json.texture["tower_4"].setSmooth(json.setting["texture"]);
        json.texture["tower_5"].setSmooth(json.setting["texture"]);
        json.texture["tower_6"].setSmooth(json.setting["texture"]);
        json.texture["tower_7"].setSmooth(json.setting["texture"]);
    }
    json.saveSettings();
}

void SettingButtons::applySelectedLanguage(Settings &json, tgui::Gui &gui) {

    std::string choice = gui.get<tgui::ListBox>("list")->getSelectedItem();

    json.setting["language"] = choice;
    Language::getLanguage(json.language, json.setting);
    json.saveSettings();
}

void SettingButtons::getResolution(tgui::Gui &gui, Settings &json) {

    try {

        tgui::ComboBox::Ptr box = gui.get<tgui::Panel>("panel")->get<tgui::Panel>("panel")->get<tgui::ComboBox>("resolution");

        if(box != nullptr) {

            for (int i = 0; i < json.system["x_list"].size(); i+=2) {
                int v = json.system["x_list"].at(i);
                int k = json.system["x_list"].at(i+1);
                std::string bResolutionString = std::to_string(v) + " X " + std::to_string(k);
                box->addItem(bResolutionString);
                if(json.setting["wWidth"] == json.system["x_list"].at(i)){
                    box->setSelectedItem(bResolutionString);
                }
             }
        }
    }catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

void SettingButtons::setSettings(sf::RenderWindow &window, tgui::Gui &gui, Settings &json, Sound &sound) {

    std::string title = json.language["title"];
    std::string version = json.setting["version"];
    title = title +" "+version;

    sf::ContextSettings settings;
    settings.antialiasingLevel = json.setting["anti"];

    if(json.setting["wFullScreen"]){
        window.create({json.setting["wWidth"], json.setting["wHeight"]},  sf::String::fromUtf8(title.begin(),title.end()), sf::Style::Fullscreen, settings);
    }
    else{
        window.create({json.setting["wWidth"], json.setting["wHeight"]},  sf::String::fromUtf8(title.begin(),title.end()), sf::Style::Close, settings);
    }
    window.setIcon(512,512,json.image["icon"].getPixelsPtr());

    json.view["fixed"].reset(sf::FloatRect(0,0, json.setting["wWidth"],json.setting["wHeight"]));
    gui.setView(json.view["fixed"]);

    window.setMouseCursorVisible(false); // Hide cursor
    window.setFramerateLimit(json.setting["fps"]);
    window.setVerticalSyncEnabled(json.setting["sync"]);

    try {
        json.texture["tiles"].setSmooth(json.setting["texture"]);
        json.texture["pointer"].setSmooth(json.setting["texture"]);
        json.texture["paladin"].setSmooth(json.setting["texture"]);
        json.texture["player"].setSmooth(json.setting["texture"]);
        json.texture["miniMapFrame"].setSmooth(json.setting["texture"]);
        json.texture["progressBar"].setSmooth(json.setting["texture"]);
        json.texture["bullet"].setSmooth(json.setting["texture"]);
        json.texture["tower_1"].setSmooth(json.setting["texture"]);
        json.texture["tower_2"].setSmooth(json.setting["texture"]);
        json.texture["tower_3"].setSmooth(json.setting["texture"]);
        json.texture["tower_4"].setSmooth(json.setting["texture"]);
        json.texture["tower_5"].setSmooth(json.setting["texture"]);
        json.texture["tower_6"].setSmooth(json.setting["texture"]);
        json.texture["tower_7"].setSmooth(json.setting["texture"]);
    }catch (...){
        std::cerr << "TEXTURE crash " << __FILE__ << std::endl;
    }

    sound.setSound(json.setting["mute"], json.setting["music"], json.setting["sound"], json.setting["system"]);
}
