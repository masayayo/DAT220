//
// Created by Chrim14 on 01.12.2017.
//


#include <chrono>
#include "MenuPanels.h"
#include "SettingButtons.h"
#include "Menu.h"
#include "../../System/Map/FileHandler.h"
#include "../../Engine/Div/KeyBinds.h"

#define background sf::Color(0,0,0,230)

void menuPanel::getSettings(int panelChosen, Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    try {
        menuPanel::removePanel(gui);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");


        std::string sBack = json.language["back"];
        std::string sApply = json.language["apply"];
        std::string sKeys = json.language["keybinding"];
        std::string sLanguage = json.language["language"];
        std::string sGame = json.language["game"];
        std::string sRestore = json.language["restore"];

        tgui::Panel::Ptr panel = theme->load("panel");
        panel->setSize(windowWidth, windowHeight);
        panel->setPosition(0, 0);
        if(state.getState() != List_State::Settings)
            panel->setBackgroundColor(background);
        else if(state.getState() == List_State::Settings)
            panel->setBackgroundColor(sf::Color(0,0,0,0));
        gui.add(panel, "panel");

        tgui::Button::Ptr bGame = theme->load("button");
        bGame->setSize(windowWidth * 0.23f, windowHeight * 0.065f);
        bGame->setPosition(panel->getSize().x * 0.01f, panel->getSize().y * 0.03f);
        bGame->setText(sf::String::fromUtf8(sGame.begin(),sGame.end()));
        bGame->connect("clicked", [&](){
            lDebug("Button game clicked");
            json.system["setting"] = 0;
            KeyBinds::getKeys(json.keys);
            menuPanel::getSettings(json.system["setting"], gameTimer, gui, window, state, json, sound, waveManager);
            sound.SoundClick();
            json.system["focused"] = false;
        });
        panel->add(bGame);

        tgui::Button::Ptr bLanguage = theme->load("button");
        bLanguage->setSize(bGame->getSize().x, bGame->getSize().y);
        bLanguage->setPosition(bGame->getPosition().x, bGame->getPosition().y + bGame->getSize().y * 1.2f);
        bLanguage->setText(sf::String::fromUtf8(sLanguage.begin(),sLanguage.end()));
        bLanguage->connect("clicked", [&](){
            lDebug("Button Language clicked");
            json.system["setting"] = 1;
            KeyBinds::getKeys(json.keys);
            json.getSettings();
            sound.setSound(json.setting["mute"], json.setting["music"], json.setting["sound"], json.setting["system"]);
            menuPanel::getSettings(json.system["setting"], gameTimer, gui, window, state, json, sound, waveManager);
            sound.SoundClick();
            json.system["focused"] = false;
        });
        panel->add(bLanguage);

        tgui::Button::Ptr bKeys = theme->load("button");
        bKeys->setSize(bGame->getSize().x, bGame->getSize().y);
        bKeys->setPosition(bGame->getPosition().x, bLanguage->getPosition().y + bLanguage->getSize().y * 1.2f);
        bKeys->setText(sf::String::fromUtf8(sKeys.begin(),sKeys.end()));
        bKeys->connect("clicked", [&](){
            lDebug("Button game clicked");
            json.system["setting"] = 2;
            json.getSettings();
            sound.setSound(json.setting["mute"], json.setting["music"], json.setting["sound"], json.setting["system"]);
            menuPanel::getSettings(json.system["setting"], gameTimer, gui, window, state, json, sound, waveManager);
            sound.SoundClick();
            json.system["focused"] = false;
        });
        panel->add(bKeys);

        tgui::Button::Ptr bBack = theme->load("button");
        bBack->setSize(bGame->getSize().x, bGame->getSize().y);
        bBack->setPosition(bGame->getPosition().x, panel->getSize().y - bBack->getSize().y*1.2f);
        bBack->setText(sf::String::fromUtf8(sBack.begin(),sBack.end()));
        bBack->connect("clicked", [&]() {
            lDebug("Button back clicked");
            sound.SoundClickBack();
            json.getSettings();
            json.system["focused"] = false;
            sound.setSound(json.setting["mute"], json.setting["music"], json.setting["sound"], json.setting["system"]);
            if (state.getState() == List_State::Settings) {
                state.NextState(List_State::Zero);
                state.updateInterface(gameTimer, gui, window, state, json, sound, waveManager);
            }
            else {
                menuPanel::removePanel(gui);
                menuPanel::getPause(gameTimer, gui, window, state, json, sound, waveManager);
            }
        });
        panel->add(bBack);

        tgui::ListBox::Ptr lPanel = theme->load("ListBox");
        lPanel->setPosition(bGame->getPosition().x + bGame->getSize().x * 1.05f, bGame->getPosition().y);
        lPanel->setSize(panel->getSize().x - lPanel->getPosition().x * 1.05f,
                        panel->getSize().y - (panel->getSize().y - bBack->getPosition().y)*1.1f - lPanel->getPosition().y);
        lPanel->setOpacity(0.8f);
        panel->add(lPanel,"box");

        tgui::Panel::Ptr panel2 = theme->load("panel");
        panel2->setSize(lPanel->getSize().x,lPanel->getSize().y);
        panel2->setPosition(lPanel->getPosition().x,lPanel->getPosition().y);
        panel2->setBackgroundColor(sf::Color(0,0,0,0));
        panel->add(panel2,"panel");

        tgui::Button::Ptr bApply = theme->load("button");
        bApply->setSize(windowWidth * 0.15f, bGame->getSize().y);
        bApply->setPosition(lPanel->getPosition().x + lPanel->getSize().x - bApply->getSize().x, bBack->getPosition().y);
        bApply->setText(sf::String::fromUtf8(sApply.begin(),sApply.end()));
        bApply->connect("clicked", [&,panelChosen]() {
            lDebug("Button Apply clicked");
            sound.SoundClick();
            json.system["focused"] = false;
            if(panelChosen == 1){
                Language::getLanguage(json.language, json.setting);
            }
            else if(panelChosen == 0) {
                SettingButtons sb;
                sb.applySettings(false, window, gui, json, sound);
            }
            else if(panelChosen == 2) {
                KeyBinds::saveKeysToFile(json.keys);
            }
            state.updateInterface(gameTimer, gui, window, state, json, sound, waveManager);
        });
        panel->add(bApply);

        tgui::Button::Ptr bRestore = theme->load("button");
        bRestore->setSize(bApply->getSize().x, bApply->getSize().y);
        bRestore->setPosition(bApply->getPosition().x - bRestore->getSize().x * 1.05f, bBack->getPosition().y);
        bRestore->setText(sf::String::fromUtf8(sRestore.begin(),sRestore.end()));
        bRestore->connect("clicked", [&,panelChosen]() {
            lDebug("Button Restore clicked");
            sound.SoundClick();
            if(panelChosen == 0){
                SettingButtons sb;
                sb.applySettings(true, window, gui, json, sound);
            }
            else if(panelChosen == 1){
                json.setting["language"] = "English";
                Language::getLanguage(json.language, json.setting);
            }
            else if(panelChosen == 2){
                KeyBinds::setKeys(json.keys);
                KeyBinds::saveKeysToFile(json.keys);
            }

            state.updateInterface(gameTimer, gui, window, state, json, sound, waveManager);
        });
        panel->add(bRestore);

        if(panelChosen == 0){
            bLanguage->setOpacity(0.8f);
            bKeys->setOpacity(0.8f);
            getGame(gui,window,state,json,sound);
        }
        else if(panelChosen == 1){
            bGame->setOpacity(0.8f);
            bKeys->setOpacity(0.8f);
            getLanguage(gui,json,sound);
        }
        else if(panelChosen == 2){
            bLanguage->setOpacity(0.8f);
            bGame->setOpacity(0.8f);
            getKeys(gui,json,sound,window);
        }

    }catch (const tgui::Exception& e) {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void menuPanel::getPause(Timer &gameTimer, tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    try{
        menuPanel::removePanel(gui);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        tgui::Button::Ptr bExit, bContinue, bLoad, bSave, bOptions;

        std::string continueString = json.language["continue"];
        std::string loadString = json.language["load"];
        std::string saveString = json.language["save"];
        std::string optionString = json.language["options"];
        std::string exitString = json.language["exit"];

        tgui::Panel::Ptr panel = theme->load("Panel");
        panel->setBackgroundColor(background);
        panel->setSize(windowWidth,windowHeight);
        panel->setPosition(0,0);
        gui.add(panel, "panel");

        bContinue = theme->load("Button");
        bContinue->setSize(windowWidth*bLength, windowHeight*bHeight);
        bContinue->setPosition(windowWidth*bWidthStart, windowHeight*0.10f);
        bContinue->setText(sf::String::fromUtf8(continueString.begin(),continueString.end()));
        panel->add(bContinue, "continue");

        bSave = theme->load("Button");
        bSave->setSize(windowWidth*bLength*0.49f, windowHeight*bHeight);
        bSave->setPosition(windowWidth*bWidthStart, windowHeight*0.30f);
        bSave->setText(sf::String::fromUtf8(saveString.begin(),saveString.end()));
        bSave->connect("clicked", [&](){
            lDebug("Button Save progress clicked");
            sound.SoundClick();
            getSavePanel(gameTimer,gui,window,state,json,sound,waveManager);
        });
        panel->add(bSave, "save");

        bLoad = theme->load("Button");
        bLoad->setSize(windowWidth*bLength*0.49f, windowHeight*bHeight);
        bLoad->setPosition(windowWidth*0.50f, windowHeight*0.30f);
        bLoad->setText(sf::String::fromUtf8(loadString.begin(),loadString.end()));
        bLoad->connect("clicked", [&](){
            lDebug("Button Load game clicked");
            getLoadPanel(gameTimer,gui,window,state,json,sound,waveManager);
            sound.SoundClick();
        });
        panel->add(bLoad, "load");

        bOptions = tgui::Button::copy(bContinue);
        bOptions->setPosition(windowWidth*bWidthStart, windowHeight*0.50f);
        bOptions->setText(sf::String::fromUtf8(optionString.begin(),optionString.end()));
        bOptions->connect("clicked", [&](){
            lDebug("Button Options clicked");
            sound.SoundClick();
            menuPanel::getSettings(json.system["setting"], gameTimer, gui, window, state, json, sound, waveManager);
        });
        panel->add(bOptions, "options");

        bExit = tgui::Button::copy(bContinue);
        bExit->setPosition(windowWidth*bWidthStart, windowHeight*0.7f);
        bExit->setText(sf::String::fromUtf8(exitString.begin(),exitString.end()));
        bExit->connect("clicked", [&](){
            lDebug("Button Exit game clicked"),
                    sound.SoundClick(),
                    state.NextState(List_State::Zero),
                    state.updateInterface(gameTimer,gui,window,state,json,sound, waveManager),
                    sound.StartMenuMusic();
        });
        panel->add(bExit, "exit");

        bContinue->connect("clicked", [&]() {
            lDebug("Button Continue game clicked"),
                    sound.SoundClickBack();
                    state.NextState(List_State::Game);
                    sound.restoreLastMusic();
                    menuPanel::removePanel(gui);
                    gameTimer.Start();
        });
    } catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}


void menuPanel::getGame(tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound) {

    try {
        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr main = gui.get<tgui::Panel>("panel");
        tgui::Panel::Ptr panel = main->get<tgui::Panel>("panel");

        if (panel != nullptr) {

            //Getting json strings
            std::string sFull = json.language["fullscreen"];
            std::string sResolution = json.language["resolution"];
            std::string sVolum = json.language["volum"];
            std::string sMusic = json.language["music"];
            std::string sSound = json.language["sound"];
            std::string sVideo = json.language["video"];
            std::string sGame = json.language["game"];
            std::string sAnti = json.language["antialiasing"];
            std::string sNone = json.language["none"];
            std::string sFps = json.language["fps"];
            std::string sUnlimited = json.language["unlimited"];
            std::string sVsync = json.language["Vsync"];
            std::string sSmooth = json.language["smooth-texture"];
            std::string sDraw = json.language["draw-bullets"];
            std::string sMute = json.language["mute"];
            std::string sSystem = json.language["system"];
            std::string sView = json.language["view-speed"];
            std::string sZoom = json.language["zoom-speed"];
            std::string sStart = json.language["start-view"];
            std::string sPlayer = json.language["player-name"];

            unsigned int textSize = panel->getSize().y*0.03f;

            tgui::Label::Ptr label_large_volum = theme->load("label");
            label_large_volum->setPosition(panel->getSize().x*0.05f,panel->getSize().y*0.04f);
            label_large_volum->setTextColor(sf::Color(204,204,0));
            label_large_volum->setText(sf::String::fromUtf8(sVolum.begin(),sVolum.end()));
            label_large_volum->setTextSize(textSize*2);
            panel->add(label_large_volum);

            tgui::Label::Ptr label_large_video = tgui::Label::copy(label_large_volum);
            label_large_video->setPosition(panel->getSize().x*0.55f,label_large_volum->getPosition().y);
            label_large_video->setText(sf::String::fromUtf8(sVideo.begin(),sVideo.end()));
            panel->add(label_large_video);

            tgui::Label::Ptr label = theme->load("label");
            label->setPosition(label_large_video->getPosition().x ,label_large_video->getPosition().y + label_large_video->getTextSize()*1.5f);
            label->setText(sf::String::fromUtf8(sResolution.begin(),sResolution.end()));
            label->setTextSize(textSize);
            panel->add(label);

            tgui::ComboBox::Ptr resolution = theme->load("combobox");
            resolution->setSize(panel->getSize().x*0.2f,panel->getSize().y*0.05f);
            resolution->setPosition(label->getPosition().x,label->getPosition().y+label->getTextSize()*1.1f);
            panel->add(resolution,"resolution");
            SettingButtons::getResolution(gui,json);
            resolution->connect("ItemSelected", [&,resolution](){
                std::string temp_string = resolution->getSelectedItem();
                std::string temp;
                for (int i = 0; i < temp_string.size(); ++i) {
                    if(temp_string[i] == 'x' || temp_string[i] == 'X'){
                        int v = std::stoi(temp);
                        json.setting["wWidth"] = v;
                        temp = "";
                    }
                    else{
                        temp += temp_string[i];
                    }
                }
                int v = std::stoi(temp);
                json.setting["wHeight"] = v;
            });

            tgui::Label::Ptr label_anti = theme->load("label");
            label_anti->setPosition(label_large_video->getPosition().x ,resolution->getPosition().y + resolution->getSize().y*2);
            label_anti->setTextSize(label->getTextSize());
            label_anti->setText(sf::String::fromUtf8(sAnti.begin(),sAnti.end()));
            panel->add(label_anti);

            tgui::ComboBox::Ptr antialiasing = theme->load("combobox");
            antialiasing->setSize(panel->getSize().x*0.2f,panel->getSize().y*0.05f);
            antialiasing->setPosition(label_anti->getPosition().x,label_anti->getPosition().y+label_anti->getTextSize()*1.1f);
            antialiasing->addItem(sf::String::fromUtf8(sNone.begin(),sNone.end()),"0");
            antialiasing->addItem("2x","2");
            antialiasing->addItem("4x","4");
            antialiasing->addItem("8x","8");
            antialiasing->addItem("16x","16");
            int anti = json.setting["anti"];
            antialiasing->setSelectedItemById(std::string(std::to_string(anti)));
            antialiasing->connect("ItemSelected", [&,antialiasing](){
                std::string temp = antialiasing->getSelectedItemId();
                json.setting["anti"] = std::stoi(temp);
            });
            panel->add(antialiasing,"anti");

            tgui::Label::Ptr label_fps = theme->load("label");
            label_fps->setPosition(label_large_video->getPosition().x ,antialiasing->getPosition().y + antialiasing->getSize().y*2);
            label_fps->setTextSize(label->getTextSize());
            label_fps->setText(sf::String::fromUtf8(sFps.begin(),sFps.end()));
            panel->add(label_fps);

            tgui::EditBox::Ptr fps = theme->load("editbox");
            fps->setSize(panel->getSize().x*0.2f,panel->getSize().y*0.05f);
            fps->setPosition(label_fps->getPosition().x,label_fps->getPosition().y+label_fps->getTextSize()*1.1f);
            fps->setDefaultText(sf::String::fromUtf8(sUnlimited.begin(),sUnlimited.end()));

            if(json.setting["fps"] != 0){
                 int v = json.setting["fps"];
                 std::string string1 = std::to_string(v);
                 fps->setText(string1);
            }

            fps->setInputValidator("^[0-9]{0,4}$");
            fps->connect("TextChanged",[&,sUnlimited,fps](){
                if(fps != nullptr && !fps->getText().isEmpty()) {
                    int v = std::stoi(std::string(fps->getText()));
                    json.setting["fps"] = v;
                }
                else if(fps->getText().isEmpty()){
                    json.setting["fps"] = 0;
                }
            });
            panel->add(fps,"fps");


            tgui::Label::Ptr label_music = theme->load("label");
            int temp = json.setting["music"];
            std::string string1 = std::to_string(temp);
            std::string string2 = sf::String::fromUtf8(sMusic.begin(),sMusic.end());
            label_music->setText(string2 + " " + string1 + "%");
            label_music->setPosition(label_large_volum->getPosition().x, label_large_volum->getPosition().y + label_large_volum->getTextSize()*1.5f);
            label_music->setTextSize(label->getTextSize());
            panel->add(label_music);

            tgui::Slider::Ptr sliderMusic = theme->load("slider");
            sliderMusic ->setPosition(label_music->getPosition().x, label_music->getPosition().y + label_music->getTextSize()*1.2f);
            sliderMusic ->setSize(panel->getSize().x*0.35f,panel->getSize().y*0.02f);
            sliderMusic ->setMaximum(100);
            sliderMusic ->setMinimum(0);
            sliderMusic ->setValue(json.setting["music"]);
            sliderMusic->connect("ValueChanged", [&,label_music,sMusic,sliderMusic](){
                int value = sliderMusic->getValue();
                std::string t1 = std::to_string(value);
                std::string t2 = sf::String::fromUtf8(sMusic.begin(),sMusic.end());
                label_music->setText(t1 = t2 + " " + t1 + "%");
                sound.setMusicVolum(value);
                json.setting["music"] = value;
            });
            panel->add(sliderMusic, "music");

            tgui::Label::Ptr label_sound = theme->load("label");
            temp = json.setting["sound"];
            string1 = std::to_string(temp);
            string2 = sf::String::fromUtf8(sSound.begin(),sSound.end());
            label_sound->setText(string2 + " " + string1 + "%");
            label_sound->setPosition(label_large_volum->getPosition().x, sliderMusic->getPosition().y + sliderMusic->getSize().y*2);
            label_sound->setTextSize(label->getTextSize());
            panel->add(label_sound);

            tgui::Slider::Ptr sliderSound = theme->load("slider");
            sliderSound ->setPosition(label_sound->getPosition().x, label_sound->getPosition().y + label_sound->getTextSize()*1.3f);
            sliderSound ->setSize(sliderMusic->getSize().x,sliderMusic->getSize().y);
            sliderSound ->setMaximum(100);
            sliderSound ->setMinimum(0);
            sliderSound ->setValue(json.setting["sound"]);
            sliderSound->connect("ValueChanged", [&,label_sound,sSound,sliderSound](){
                int value = sliderSound->getValue();
                std::string t1 = std::to_string(value);
                std::string t2 = sf::String::fromUtf8(sSound.begin(),sSound.end());
                label_sound->setText(t2 + " " + t1 + "%");
                sound.setSoundVolum(sliderSound->getValue());
                std::string soundName = "sfx16";
                sound.towerShoot(soundName);
                json.setting["sound"] = value;
            });
            panel->add(sliderSound, "sound");

            tgui::Label::Ptr label_system = theme->load("label");
            temp = json.setting["system"];
            string1 = std::to_string(temp);
            string2 = sf::String::fromUtf8(sSystem.begin(),sSystem.end());
            label_system->setText(string2 + " " + string1 + "%");
            label_system->setPosition(label_large_volum->getPosition().x, sliderSound->getPosition().y + sliderSound->getSize().y*2);
            label_system->setTextSize(label->getTextSize());
            panel->add(label_system);

            tgui::Slider::Ptr sliderSystem = theme->load("slider");
            sliderSystem ->setPosition(label_system->getPosition().x, label_system->getPosition().y + label_system->getTextSize()*1.3f);
            sliderSystem ->setSize(sliderMusic->getSize().x,sliderMusic->getSize().y);
            sliderSystem ->setMaximum(100);
            sliderSystem ->setMinimum(0);
            sliderSystem ->setValue(json.setting["system"]);
            sliderSystem ->connect("ValueChanged", [&,label_system,sSystem,sliderSystem](){
                std::string t1 = std::to_string(sliderSystem->getValue());
                std::string t2 = sf::String::fromUtf8(sSystem.begin(),sSystem.end());
                label_system->setText(t2 + " " + t1 + "%");
                sound.setSoundVolum(sliderSystem->getValue());
                sound.SoundClick();
                json.setting["system"] = sliderSystem->getValue();
        });
            panel->add(sliderSystem, "system");


            tgui::CheckBox::Ptr mute = theme->load("checkbox");
            mute->setSize(panel->getSize().x*0.03f,panel->getSize().x*0.03f);
            mute->setPosition(sliderSystem->getPosition().x, sliderSystem->getPosition().y + sliderSystem->getSize().y*2.0f);
            if(json.setting["mute"]){
                mute->check();
                sliderSystem->setOpacity(0.5f);
                sliderMusic->setOpacity(0.5f);
                sliderSound->setOpacity(0.5f);
                label_music->setOpacity(0.5f);
                label_sound->setOpacity(0.5f);
                label_system->setOpacity(0.5f);
                sliderSystem->disable();
                sliderMusic->disable();
                sliderSound->disable();
            }
            mute->connect("checked", [&,sliderSystem,sliderSound,sliderMusic,label_music,label_sound,label_system](){
                json.setting["mute"] = true;
                sound.setSound(json.setting["mute"], json.setting["music"], json.setting["sound"], json.setting["system"]);
                sliderSystem->setOpacity(0.5f);
                sliderMusic->setOpacity(0.5f);
                sliderSound->setOpacity(0.5f);
                label_music->setOpacity(0.5f);
                label_sound->setOpacity(0.5f);
                label_system->setOpacity(0.5f);
                sliderSystem->disable();
                sliderMusic->disable();
                sliderSound->disable();
            });
            mute->connect("unchecked", [&,sliderSystem,sliderSound,sliderMusic,label_music,label_sound,label_system](){
                json.setting["mute"] = false;
                sound.setSound(json.setting["mute"], json.setting["music"], json.setting["sound"], json.setting["system"]);
                sliderSystem->setOpacity(1);
                sliderMusic->setOpacity(1);
                sliderSound->setOpacity(1);
                label_music->setOpacity(1);
                label_sound->setOpacity(1);
                label_system->setOpacity(1);
                sliderSystem->enable();
                sliderMusic->enable();
                sliderSound->enable();
            });
            panel->add(mute,"mute");

            tgui::Label::Ptr label_mute = theme->load("label");
            label_mute->setTextSize(label->getTextSize());
            label_mute->setPosition(mute->getPosition().x + mute->getSize().x*1.2f, mute->getPosition().y + mute->getSize().y/2.0f - label_mute->getTextSize()/2.0f);
            label_mute->setText(sf::String::fromUtf8(sMute.begin(),sMute.end()));
            panel->add(label_mute);

            tgui::CheckBox::Ptr fullScreen = theme->load("checkbox");
            fullScreen->setSize(panel->getSize().x*0.03f,panel->getSize().x*0.03f);
            fullScreen->setPosition(fps->getPosition().x, fps->getPosition().y + fps->getSize().y*2.5f);
            if(json.setting["wFullScreen"])
                fullScreen->check();
            fullScreen->connect("checked unchecked", [&,fullScreen](){
                json.setting["wFullScreen"] = fullScreen->isChecked();
            });
            panel->add(fullScreen,"fScreen");

            tgui::Label::Ptr label_fullScreen = theme->load("label");
            label_fullScreen->setTextSize(label->getTextSize());
            label_fullScreen->setPosition(fullScreen->getPosition().x + fullScreen->getSize().x*1.2f, fullScreen->getPosition().y + fullScreen->getSize().y/2.0f - label_fullScreen->getTextSize()/2.0f);
            label_fullScreen->setText(sf::String::fromUtf8(sFull.begin(),sFull.end()));
            panel->add(label_fullScreen);


            tgui::CheckBox::Ptr VerticalSync = theme->load("checkbox");
            VerticalSync->setSize(fullScreen->getSize().x,fullScreen->getSize().y);
            VerticalSync->setPosition(fullScreen->getPosition().x,fullScreen->getPosition().y + fullScreen->getSize().y*1.5f);
            if(json.setting["sync"])
                VerticalSync->check();
            VerticalSync->connect("checked unchecked", [&,VerticalSync](){
                json.setting["sync"] = VerticalSync->isChecked();
            });
            panel->add(VerticalSync,"vsync");

            tgui::Label::Ptr label_vSync = theme->load("label");
            label_vSync->setTextSize(label->getTextSize());
            label_vSync->setPosition(VerticalSync->getPosition().x + VerticalSync->getSize().x*1.2f, VerticalSync->getPosition().y + VerticalSync->getSize().y/2.0f - label_vSync->getTextSize()/2.0f);
            label_vSync->setText(sf::String::fromUtf8(sVsync.begin(),sVsync.end()));
            panel->add(label_vSync);

            tgui::CheckBox::Ptr smoothTexture = theme->load("checkbox");
            smoothTexture->setSize(fullScreen->getSize().x,fullScreen->getSize().y);
            smoothTexture->setPosition(VerticalSync->getPosition().x,VerticalSync->getPosition().y + VerticalSync->getSize().y*1.5f);
            if(json.setting["texture"])
                smoothTexture->check();
            smoothTexture->connect("checked unchecked", [&,smoothTexture](){
                json.setting["texture"] = smoothTexture->isChecked();
            });
            panel->add(smoothTexture,"smooth");

            tgui::Label::Ptr label_smooth = theme->load("label");
            label_smooth->setTextSize(label->getTextSize());
            label_smooth->setPosition(smoothTexture->getPosition().x + smoothTexture->getSize().x*1.2f, smoothTexture->getPosition().y + smoothTexture->getSize().y/2.0f - label_smooth->getTextSize()/2.0f);
            label_smooth->setText(sf::String::fromUtf8(sSmooth.begin(),sSmooth.end()));
            panel->add(label_smooth);


            tgui::Label::Ptr label_large_game = tgui::Label::copy(label_large_volum);
            label_large_game->setPosition(label_large_volum->getPosition().x,mute->getPosition().y + mute->getSize().y*2);
            label_large_game->setText(sf::String::fromUtf8(sGame.begin(),sGame.end()));
            panel->add(label_large_game);

            tgui::Label::Ptr label_zoom = theme->load("label");
            int zoom_value = json.setting["zoom"];
            string1 = std::to_string(zoom_value);
            string2 = sf::String::fromUtf8(sZoom.begin(), sZoom.end());
            label_zoom->setText(string2 + " " + string1 + "%");
            label_zoom->setPosition(label_large_game->getPosition().x, label_large_game->getPosition().y + label_large_game->getSize().y*1.5f);
            label_zoom->setTextSize(label->getTextSize());
            panel->add(label_zoom);

            tgui::Slider::Ptr sliderZoom = theme->load("slider");
            sliderZoom ->setPosition(label_zoom->getPosition().x, label_zoom->getPosition().y + label_zoom->getTextSize()*1.3f);
            sliderZoom ->setSize(sliderMusic->getSize().x,sliderMusic->getSize().y);
            sliderZoom ->setMaximum(30);
            sliderZoom ->setMinimum(1);
            sliderZoom ->setValue(json.setting["zoom"]);
            sliderZoom->connect("ValueChanged", [&,label_zoom,sZoom,sliderZoom](){
                int value = sliderZoom->getValue();
                std::string t1 = std::to_string(value);
                std::string t2 = sf::String::fromUtf8(sZoom.begin(),sZoom.end());
                label_zoom->setText(t2 + " " + t1 + "%");
                json.setting["zoom"] = value;
            });
            panel->add(sliderZoom, "zoom");

            tgui::Label::Ptr lable_speed = theme->load("label");
            temp = json.setting["viewSpeed"];
            string1 = std::to_string(temp);
            string2 = sf::String::fromUtf8(sView.begin(), sView.end());
            lable_speed->setText(string2 + " " + string1);
            lable_speed->setPosition(sliderZoom->getPosition().x, sliderZoom->getPosition().y + sliderZoom->getSize().y*2);
            lable_speed->setTextSize(label->getTextSize());
            panel->add(lable_speed);

            tgui::Slider::Ptr sliderSpeed = theme->load("slider");
            sliderSpeed ->setPosition(lable_speed->getPosition().x, lable_speed->getPosition().y + lable_speed->getTextSize()*1.3f);
            sliderSpeed ->setSize(sliderMusic->getSize().x,sliderMusic->getSize().y);
            sliderSpeed ->setMaximum(50);
            sliderSpeed ->setMinimum(1);
            sliderSpeed ->setValue(json.setting["viewSpeed"]);
            sliderSpeed->connect("ValueChanged", [&,lable_speed,sView,sliderSpeed](){
                int value = sliderSpeed->getValue();
                std::string t1 = std::to_string(value);
                std::string t2 = sf::String::fromUtf8(sView.begin(),sView.end());
                lable_speed->setText(t2 + " " + t1);
                json.setting["viewSpeed"] = value;
            });
            panel->add(sliderSpeed, "speed");

            tgui::Label::Ptr lable_startView = theme->load("label");
            temp = json.setting["startView"];
            string1 = std::to_string(temp);
            string2 = sf::String::fromUtf8(sStart.begin(), sStart.end());
            lable_startView->setText(string2 + " " + string1);
            lable_startView->setPosition(sliderSpeed->getPosition().x, sliderSpeed->getPosition().y + sliderSpeed->getSize().y*2);
            lable_startView->setTextSize(label->getTextSize());
            panel->add(lable_startView);

            tgui::Slider::Ptr sliderStartView = theme->load("slider");
            sliderStartView ->setPosition(lable_startView->getPosition().x, lable_startView->getPosition().y + lable_startView->getTextSize()*1.3f);
            sliderStartView ->setSize(sliderMusic->getSize().x,sliderMusic->getSize().y);
            sliderStartView ->setMaximum(Layer_One_Size);
            sliderStartView ->setMinimum(Layer_One_Size_Min);
            sliderStartView ->setValue(json.setting["startView"]);
            sliderStartView ->connect("ValueChanged", [&,lable_startView,sStart,sliderStartView](){
                int value = sliderStartView->getValue();
                std::string t1 = std::to_string(value);
                std::string t2 = sf::String::fromUtf8(sStart.begin(),sStart.end());
                lable_startView->setText(t2 + " " + t1);
                json.setting["startView"] = value;
            });
            panel->add(sliderStartView, "view");

            tgui::CheckBox::Ptr drawBullets = theme->load("checkbox");
            drawBullets->setSize(fullScreen->getSize().x,fullScreen->getSize().y);
            drawBullets->setPosition(sliderStartView->getPosition().x,sliderStartView->getPosition().y + sliderStartView->getSize().y*2.0f);
            if(json.setting["bullets"])
                drawBullets->check();
            drawBullets->connect("checked unchecked", [&,drawBullets](){
                json.setting["bullets"] = drawBullets->isChecked();
            });

            panel->add(drawBullets,"draw");

            tgui::Label::Ptr label_drawBullets = theme->load("label");
            label_drawBullets->setTextSize(label->getTextSize());
            label_drawBullets->setPosition(drawBullets->getPosition().x + drawBullets->getSize().x*1.2f, drawBullets->getPosition().y + drawBullets->getSize().y/2.0f - label_drawBullets->getTextSize()/2.0f);
            label_drawBullets->setText(sf::String::fromUtf8(sDraw.begin(),sDraw.end()));
            panel->add(label_drawBullets);

            tgui::Label::Ptr label_player = theme->load("label");
            label_player->setTextSize(label->getTextSize());
            label_player->setPosition(drawBullets->getPosition().x,drawBullets->getPosition().y + drawBullets->getSize().y*2.0f);
            label_player->setText(sf::String::fromUtf8(sPlayer.begin(),sPlayer.end()));
            panel->add(label_player);

            tgui::EditBox::Ptr playerName = theme->load("editbox");
            playerName->setSize(fps->getSize());
            playerName->setPosition(drawBullets->getPosition().x,label_player->getPosition().y + label_player->getTextSize()*1.13f);
            sPlayer = json.setting.at("name");
            playerName->setInputValidator("^[^]{0,10}$");
            playerName->setText(sf::String::fromUtf8(sPlayer.begin(),sPlayer.end()));
            playerName->connect("TextChanged",[&,playerName](){
                json.setting.at("name") = playerName->getText();
            });
            panel->add(playerName);

        }
    }
    catch (const tgui::Exception& e){
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void menuPanel::getLanguage(tgui::Gui &gui, Settings &json, Sound &sound) {


    try {
        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr main = gui.get<tgui::Panel>("panel");
        tgui::Panel::Ptr panel = main->get<tgui::Panel>("panel");
        if (panel != nullptr) {

            unsigned int textSize = panel->getSize().y*0.03f;

            std::string labelString = json.language["packet"];
            tgui::Label::Ptr label;
            label = theme->load("label");
            label->setPosition(panel->getSize().x * 0.15f, panel->getSize().y * 0.02f);
            label->setTextSize(textSize*2);
            label->setText(sf::String::fromUtf8(labelString.begin(), labelString.end()));
            label->setTextColor(sf::Color(204,204,0));
            panel->add(label);

            tgui::ListBox::Ptr list = theme->load("ListBox");
            list->setSize(panel->getSize().x * 0.7f, panel->getSize().y * 0.8f);
            list->setPosition(label->getPosition().x,label->getPosition().y + label->getTextSize()*1.5f);

            list->setTextSize(textSize*1.5f);
            list->setItemHeight(textSize*1.6f);
            panel->add(list, "list");
            FileHandler fileHandler;
            std::string path = "Texture/Language";
            std::vector<std::string> vector = fileHandler.get_all_files_names_within_folder(path);

            for (auto& temp : vector){
                temp = temp.substr(0, temp.size() - 5);
                list->addItem(temp);
            }
            std::string selectedLanguage = json.setting["language"];
            list->setSelectedItem(selectedLanguage);

            list->connect("ItemSelected", [&,list](){
                if(!list->getSelectedItem().isEmpty())
                    json.setting["language"] = list->getSelectedItem();
        });
        }
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void menuPanel::removePanel(tgui::Gui &gui) {
    tgui::Panel::Ptr panel = gui.get<tgui::Panel>("panel");
    gui.remove(panel);
}

bool menuPanel::panelThere(tgui::Gui &gui) {
    tgui::Panel::Ptr panel = gui.get<tgui::Panel>("panel");
    return panel != nullptr;
}

void menuPanel::getKeys(tgui::Gui &gui, Settings &json, Sound &sound, sf::RenderWindow &window) {

    try {
        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr main = gui.get<tgui::Panel>("panel");
        tgui::Panel::Ptr panel = main->get<tgui::Panel>("panel");
        if (panel != nullptr) {

            unsigned int textSize = panel->getSize().y*0.03f;

            std::string labelString = json.language["keybinding"];
            tgui::Label::Ptr label = theme->load("label");
            label->setPosition(panel->getSize().x * 0.15f, panel->getSize().y * 0.02f);
            label->setTextSize(textSize*2);
            label->setText(sf::String::fromUtf8(labelString.begin(), labelString.end()));
            label->setTextColor(sf::Color(204,204,0));
            panel->add(label);

            std::vector<std::string> vector = KeyBinds::getJsonKeyNames();

            float positionX = label->getPosition().x;
            unsigned long long int counter = 0;

            for (int j = 0; j < 2; ++j) {

                float positionY = label->getPosition().y + label->getTextSize()*1.5f;

                for (int i = 0; i < vector.size()/2; ++i) {

                    tgui::EditBox::Ptr key_temp = theme->load("EditBox");
                    key_temp->setSize(panel->getSize().x*0.12f, panel->getSize().y*0.05f);
                    key_temp->setPosition(positionX, positionY);
                    key_temp->setDefaultText(KeyBinds::getKeyName(json.keys[vector.at(counter)]));
                    key_temp->setTextSize(textSize);


                    tgui::Label::Ptr key_label = theme->load("label");
                    key_label->setText(vector.at(counter));
                    key_label->setTextSize(textSize);
                    key_label->setPosition(key_temp->getPosition().x + key_temp->getSize().x*1.1f, key_temp->getPosition().y + (key_temp->getSize().y/2.0f) - (key_label->getTextSize()/2.0f));
                    panel->add(key_label);

                    panel->add(key_temp,vector.at(counter));

                    key_temp->connect("clicked",[&,key_temp,key_label](){
                        json.system["focused"] = true;
                        json.system["panel"] = key_label->getText();
                    });
                    key_temp->connect("TextChanged",[&,key_temp,key_label](){
                        key_temp->setText("");
                        json.system["focused"] = true;
                        json.system["panel"] = key_label->getText();
                        key_temp->unfocus();
                });

                    counter++;
                    positionY += key_temp->getSize().y*1.5f;
                }
                positionX = panel->getSize().x*0.5f;
            }
        }
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void menuPanel::setKey(tgui::Gui &gui, Settings &json) {

    tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
    tgui::Panel::Ptr main = gui.get<tgui::Panel>("panel");
    tgui::Panel::Ptr panel = main->get<tgui::Panel>("panel");
    try{
        if(panel != nullptr){
            std::string temp = json.system["panel"];
            tgui::EditBox::Ptr key_box = panel->get<tgui::EditBox>(temp);
            if(key_box != nullptr){

                std::vector<std::string> vector = KeyBinds::getJsonKeyNames();
                for (const auto& i : vector) { //Control if key already in use
                    if(json.keys[i] == json.event.key.code){
                        tgui::EditBox::Ptr key = panel->get<tgui::EditBox>(i);
                        if(key != nullptr){
                            json.keys[i] = -1;
                            key->setDefaultText(KeyBinds::getKeyName(-1));
                            break;
                        }
                    }
                }

                json.system["focused"] = false;
                 json.keys[temp] = json.event.key.code;

                key_box->setDefaultText(KeyBinds::getKeyName(json.event.key.code));
                key_box->unfocus();
            }

        }

    }catch (...){

    }
}

void menuPanel::getPlayers(Settings &json, tgui::Gui &gui) {

    tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
    tgui::Panel::Ptr pPlayers = gui.get<tgui::Panel>("players");
    if(pPlayers != nullptr) {

        float posY = pPlayers->getSize().y * 0.01f;
        float size_Y = pPlayers->getSize().y / MAX_PLAYERS - posY * 1.2f;
        float next = 0;
        for (int i = 0; i < MAX_PLAYERS; ++i) {
            tgui::Panel::Ptr temp_panel = theme->load("panel");
            temp_panel->setPosition(0, next);
            temp_panel->setSize(pPlayers->getSize().x, size_Y);
            next += size_Y + posY;

            pPlayers->add(temp_panel,std::to_string(i));

            tgui::ListBox::Ptr temp_list = theme->load("ListBox");
            temp_list->setSize(temp_panel->getSize());
            temp_list->disable(true);
            temp_panel->add(temp_list);

            tgui::ComboBox::Ptr temp_box_1 = theme->load("ComboBox");
            temp_box_1->setSize(temp_panel->getSize().x * 0.3f, temp_panel->getSize().y * 0.70f);
            temp_box_1->setPosition(temp_panel->getSize().x * 0.01f,
                                    temp_panel->getSize().y * 0.85f - temp_box_1->getSize().y);

            std::string name = json.setting.at("name");
            temp_box_1->addItem(name,"0");
            temp_box_1->addItem("Open","1");
            temp_box_1->addItem("Close","2");
            if (i == json.system["player_position"]) {
                temp_box_1->setSelectedItem(name);
                temp_box_1->disable();
            } else {
                temp_box_1->setSelectedItem("Open");
            }
            temp_panel->add(temp_box_1,std::to_string(i)+"b");

            temp_box_1->connect("ItemSelected", [&,temp_box_1,temp_panel,temp_list,pPlayers](){
                if(temp_box_1->getSelectedItemId() == "2"){
                    temp_panel->setBackgroundColor(sf::Color(128,0,0,180));
                    temp_panel->setOpacity(0.8f);
                }
                else if(temp_box_1->getSelectedItemId() == "1"){
                    temp_panel->setBackgroundColor(sf::Color::Transparent);
                    temp_list->setOpacity(1);
                }
                else if(temp_box_1->getSelectedItemId() == "0"){
                    for (int j = 0; j < MAX_PLAYERS; ++j) {
                        tgui::ComboBox::Ptr box_1 = pPlayers->get<tgui::Panel>(std::to_string(j))->get<tgui::ComboBox>(std::to_string(j)+"b");
                        if(box_1 != nullptr && box_1 != temp_box_1 && box_1->getSelectedItemId() == "0"){
                            box_1->setSelectedItemById("1");
                            box_1->enable();
                            temp_box_1->setSelectedItemById("0");
                            temp_box_1->disable();
                            json.system.at("player_position") = j;
                            break;
                        }
                    }
                }
            });


            tgui::ComboBox::Ptr temp_box_2 = theme->load("ComboBox");
            temp_box_2->setSize(temp_panel->getSize().x * 0.15f, temp_box_1->getSize().y);
            temp_box_2->setPosition(temp_box_1->getPosition().x + temp_box_1->getSize().x * 1.6f,
                                    temp_box_1->getPosition().y);
            // Add all playerclasses to the combobox
            std::map<std::string,PlayerClass> m = json.playerClasses;
            std::string defaultSelection = m.begin()->first;
            for (auto &it : m) {
                temp_box_2->addItem(it.first);
            }
            temp_box_2->setSelectedItem(defaultSelection);
            temp_box_2->connect("ItemSelected", [&,pPlayers](){
                int player_position = (int)json.system.at("player_position");
                std::string string_id = std::to_string(player_position);
                tgui::ComboBox::Ptr box = pPlayers->get<tgui::Panel>(string_id)->get<tgui::ComboBox>(string_id+"x");
                std::cerr << player_position << '\n';
                if(box != nullptr){
                    std::string itemString = box->getSelectedItem();
                    json.newGamePlayers[string_id] = itemString;
                    std::cerr << itemString << '\n';
                }
            });
            temp_panel->add(temp_box_2,std::to_string(i)+"x");

            if (i == json.system["player_position"]) {
                int player_position = i;
                std::string string_id = std::to_string(player_position);
                tgui::ComboBox::Ptr box = pPlayers->get<tgui::Panel>(string_id)->get<tgui::ComboBox>(string_id + "x");
                if (box != nullptr) {
                    std::string itemString = box->getSelectedItem();
                    json.newGamePlayers[string_id] = itemString;
                }
            }

            tgui::ComboBox::Ptr temp_box_3 = theme->load("ComboBox");
            temp_box_3->setSize(temp_panel->getSize().x * 0.15f, temp_box_1->getSize().y);
            temp_box_3->setPosition(temp_box_2->getPosition().x + temp_box_2->getSize().x * 1.1f,
                                    temp_box_1->getPosition().y);
            temp_panel->add(temp_box_3,std::to_string(i)+"a");

            tgui::Panel::Ptr temp_Color = theme->load("panel");
            temp_Color->setPosition(temp_box_3->getPosition().x + temp_box_3->getSize().x * 1.1f,
                                    temp_box_1->getPosition().y);
            temp_Color->setSize(temp_box_1->getSize().y * 2, temp_box_1->getSize().y);
            switch (i) {
                case 0:
                    temp_Color->setBackgroundColor(sf::Color::Yellow);
                    break;
                case 1:
                    temp_Color->setBackgroundColor(sf::Color::Green);
                    break;
                case 2:
                    temp_Color->setBackgroundColor(sf::Color::Red);
                    break;
                case 3:
                    temp_Color->setBackgroundColor(sf::Color::Blue);
                    break;
                case 4:
                    temp_Color->setBackgroundColor(sf::Color::Cyan);
                    break;
                case 5:
                    temp_Color->setBackgroundColor(sf::Color::Magenta);
                    break;
                case 6:
                    temp_Color->setBackgroundColor(sf::Color(255, 165, 0));
                    break;
                case 7:
                    temp_Color->setBackgroundColor(sf::Color(124, 124, 124));
                    break;
                case 8:
                    temp_Color->setBackgroundColor(sf::Color(222,184,135));
                    break;
                case 9:
                    temp_Color->setBackgroundColor(sf::Color(160,82,45));
                    break;
                default:
                    break;
            };
            temp_panel->add(temp_Color);

            tgui::ComboBox::Ptr temp_box_4 = theme->load("ComboBox");
            temp_box_4->setSize(temp_panel->getSize().x * 0.1f, temp_box_1->getSize().y);
            temp_box_4->setPosition(temp_Color->getPosition().x + temp_Color->getSize().x * 1.3f,
                                    temp_box_1->getPosition().y);
            temp_box_4->addItem("100%");
            temp_box_4->addItem("90%");
            temp_box_4->addItem("80%");
            temp_box_4->addItem("70%");
            temp_box_4->addItem("60%");
            temp_box_4->addItem("50%");
            temp_box_4->addItem("40%");
            temp_box_4->setSelectedItem("100%");
            temp_panel->add(temp_box_4);
        }
    }
}

void menuPanel::getMapSelected(Settings &json,tgui::Gui &gui, tgui::Label::Ptr label,
                               tgui::ListBox::Ptr lMaps, tgui::Label::Ptr lSize, tgui::Label::Ptr lMapName, tgui::Label::Ptr lPlayers,
                               tgui::Label::Ptr lSpawns, tgui::Label::Ptr story, tgui::Picture::Ptr image, tgui::Button::Ptr bLoad, tgui::Panel::Ptr pPlayers) {

    FileHandler fileHandler;

    json.mapPreview = false;
    json.mapSelected = false;
    json.mapImage = false;
    bLoad->setOpacity(1.0f);
    bLoad->enable();
    fileHandler.loadMap("list", "pGames", json, gui);
    std::string message = label->getText();
    try {
        if (label != nullptr && message.empty()) {
            fileHandler.refectorJsonInto2DArray(json);
            json.mapSelected = true;

            lMapName->setText(lMaps->getSelectedItem());
            int temp = json.map["players"];
            sf::String string = std::to_string(temp);
            lPlayers->setText("Players: " + string);

            temp = json.map["height"];
            string = std::to_string(temp);
            int temp2 = json.map["width"];
            sf::String string2 = std::to_string(temp2);
            lSize->setText("Size: " + string + ", " + string2);

            bool divided_spawns = json.map["divided"];
            if (divided_spawns) {
                lSpawns->setTextColor(sf::Color(255, 165, 0));
                lSpawns->setText("Spawns divided");
            } else {
                lSpawns->setTextColor(sf::Color::Green);
                lSpawns->setText("Spawns shared");
            }

            std::string text;
            try { text = json.map.at("description"); } catch (...) {}
            story->setText(text);

            try {
                text = json.map.at("image");
                string = "Texture/Maps/Image/" + text;
                if (std::ifstream(string)) {
                    image->setTexture(string, true);
                    image->show();
                    json.mapImage = true;
                }
            } catch (...) {
                image->hide();
            }

            for (int i = 0; i < MAX_PLAYERS; ++i) {
                tgui::Panel::Ptr panel_temp = pPlayers->get<tgui::Panel>(std::to_string(i));
                if(panel_temp != nullptr){

                    tgui::ComboBox::Ptr box_1 = panel_temp->get<tgui::ComboBox>(std::to_string(i)+"b");
                    if(json.map.at("players") > i){
                        if(box_1->getSelectedItemId() == "2"){
                            panel_temp->setOpacity(0.8f);
                        }else{
                            panel_temp->setOpacity(1);
                        }
                        panel_temp->enable();
                    }
                    else{
                        panel_temp->setOpacity(0.5f);
                        panel_temp->disable();
                    }
                    tgui::ComboBox::Ptr box_3 = panel_temp->get<tgui::ComboBox>(std::to_string(i)+"a");

                    if(box_3 != nullptr){
                        box_3->removeAllItems();
                        if(json.map.at("team")){
                            for (int j = 0; j < json.map.at("teams"); ++j) {
                                sf::String team_string = "Team "+std::to_string(j+1);
                                box_3->addItem(team_string);
                                if(j == 0) box_3->setSelectedItem(team_string);
                                box_3->enable();
                            }
                        }
                        else{
                            box_3->addItem("None");
                            box_3->setSelectedItem("None");
                            box_3->disable();
                        }
                    }
                }
            }
        }
    }catch (...){
        lWarning("Something failed in menuPanel::getMapSelected");
    }
}

void menuPanel::getSavePanel(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    try{
        menuPanel::removePanel(gui);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        std::string sBack = json.language["back"];
        std::string sSave = json.language["save"];

        tgui::Panel::Ptr panel = theme->load("panel");
        panel->setSize(windowWidth, windowHeight);
        panel->setPosition(0, 0);
        panel->setBackgroundColor(background);
        gui.add(panel, "panel");

        tgui::Panel::Ptr pSave = theme->load("panel");
        pSave->setSize(panel->getSize().x/2,panel->getSize().y/2);
        pSave->setPosition(panel->getSize().x/4.0f,panel->getSize().y/4.0f);
        pSave->setBackgroundColor(sf::Color::Transparent);
        panel->add(pSave);

        tgui::Label::Ptr lSave = theme->load("label");
        lSave->setTextSize(TextSize*2);
        lSave->setPosition(pSave->getPosition().x,pSave->getPosition().y - lSave->getTextSize()*1.5f);
        lSave->setText("Save Menu");
        lSave->setTextColor(sf::Color::Yellow);
        panel->add(lSave);

        tgui::TextBox::Ptr box = theme->load("textbox");
        box->setSize(pSave->getSize());
        box->disable(true);
        box->setOpacity(0.8f);
        pSave->add(box);

        tgui::Button::Ptr bBack = theme->load("button");
        bBack->setSize(windowWidth * 0.23f, windowHeight * 0.065f);
        bBack->setPosition(panel->getSize().x * 0.01f, panel->getSize().y - bBack->getSize().y*1.2f);
        bBack->setText(sf::String::fromUtf8(sBack.begin(),sBack.end()));
        bBack->connect("clicked", [&](){
            lDebug("Button back clicked");
            sound.SoundClickBack();
            getPause(gameTimer,gui,window,state,json,sound,waveManager);
        });
        panel->add(bBack);

        tgui::Button::Ptr bSave = theme->load("button");
        bSave->setSize(bBack->getSize());
        bSave->setPosition(panel->getSize().x*0.99f - bBack->getSize().x, bBack->getPosition().y);
        bSave->setText(sf::String::fromUtf8(sSave.begin(),sSave.end()));
        panel->add(bSave);

        tgui::EditBox::Ptr eSave = theme->load("editbox");
        eSave->setSize(pSave->getSize().x*0.8f,pSave->getSize().y/10.0f);
        eSave->setPosition(pSave->getSize().x/2.0f - eSave->getSize().x/2.0f,pSave->getSize().y*0.05f);
        eSave->setDefaultText("New save");
        eSave->setInputValidator("^[A-Za-z0-9 _-]{0,30}$");

        pSave->add(eSave);

        tgui::ListBox::Ptr saveList = theme->load("listbox");
        saveList->setPosition(eSave->getPosition().x, eSave->getPosition().y + eSave->getSize().y*1.5f);
        saveList->setSize(eSave->getSize().x, pSave->getSize().y*0.7f);
        saveList->setTextSize(TextSize);
        saveList->setItemHeight(TextSize*1.05f);
        pSave->add(saveList,"list");

        std::string filePath = "Texture/Saves/";
        std::vector<std::string> allFiles = FileHandler::get_all_files_names_within_folder(filePath);
        for(auto& temp : allFiles){
            temp = temp.substr(0, temp.size() - 5);
            temp = temp.replace(temp.find('.'),1,":");
            saveList->addItem(temp);
        }

        bSave->connect("clicked", [&,bSave,saveList,eSave,filePath]() {
            lDebug("Button Save progress clicked");
            sound.SoundClick();

            if(waveManager.saveState(json)) {
                std::string fileName;
                if (eSave->getText().isEmpty()) {
                    fileName = saveList->getSelectedItem();
                } else {
                    fileName = eSave->getText();
                }
                if(!fileName.empty()) {

                    using std::chrono::system_clock;
                    system_clock::time_point today = system_clock::now();
                    std::time_t tt = system_clock::to_time_t (today);
                    std::string clock = ctime(&tt);
                    clock = clock.substr(4, 12) + clock.substr(19, clock.size()-20);
                    clock = clock.replace(clock.find(':'),1,".");
                    fileName = filePath+clock+" - "+fileName+".json";

                    std::ofstream file(fileName);
                    if (!file) return;
                    file << std::setw(4) << json.save << std::endl;
                    lInfo("Save file "+fileName+" saved");

                    getSavePanel(gameTimer,gui,window,state,json,sound,waveManager);
                }
            }
        });

        eSave->connect("TextChanged",[&,saveList](){
                saveList->unfocus();
        });
        saveList->connect("ItemSelected",[&,eSave](){
            eSave->setText("");
            eSave->unfocus();
        });
    }
    catch (...){

    }
}

void menuPanel::getLoadPanel(Timer &gameTimer, tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    try{
        menuPanel::removePanel(gui);

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        std::string sBack = json.language["back"];
        std::string sLoad = json.language["load"];

        tgui::Panel::Ptr panel = theme->load("panel");
        panel->setSize(windowWidth, windowHeight);
        panel->setPosition(0, 0);
        gui.add(panel, "panel");

        if(state.getState() == List_State::Pause)
            panel->setBackgroundColor(background);
        else if(state.getState() == List_State::Load_Game)
            panel->setBackgroundColor(sf::Color(0,0,0,0));

        tgui::Panel::Ptr pLoad = theme->load("panel");
        pLoad->setSize(panel->getSize().x/2,panel->getSize().y/2);
        pLoad->setPosition(panel->getSize().x/4.0f,panel->getSize().y/4.0f);
        pLoad->setBackgroundColor(sf::Color::Transparent);
        panel->add(pLoad);

        tgui::Label::Ptr lLoad = theme->load("label");
        lLoad->setTextSize(TextSize*2);
        lLoad->setPosition(pLoad->getPosition().x,pLoad->getPosition().y - lLoad->getTextSize()*1.5f);
        lLoad->setText("Load Menu");
        lLoad->setTextColor(sf::Color::Yellow);
        panel->add(lLoad);

        tgui::TextBox::Ptr box = theme->load("textbox");
        box->setSize(pLoad->getSize());
        box->disable(true);
        box->setOpacity(0.8f);
        pLoad->add(box);

        tgui::Button::Ptr bBack = theme->load("button");
        bBack->setSize(windowWidth * 0.23f, windowHeight * 0.065f);
        bBack->setPosition(panel->getSize().x * 0.01f, panel->getSize().y - bBack->getSize().y*1.2f);
        bBack->setText(sf::String::fromUtf8(sBack.begin(),sBack.end()));
        bBack->connect("clicked", [&](){
            lDebug("Button back clicked");
            sound.SoundClickBack();
            if(state.getState() == List_State::Load_Game){
                state.NextState(List_State::Zero);
                state.updateInterface(gameTimer, gui, window, state, json, sound, waveManager);
            }
            else if(state.getState() == List_State::Pause){
                getPause(gameTimer,gui,window,state,json,sound,waveManager);
        }
        });
        panel->add(bBack);

        tgui::Button::Ptr bLoad = theme->load("button");
        bLoad->setSize(bBack->getSize());
        bLoad->setPosition(panel->getSize().x*0.99f - bBack->getSize().x, bBack->getPosition().y);
        bLoad->setText(sf::String::fromUtf8(sLoad.begin(),sLoad.end()));
        bLoad->setOpacity(0.6f);
        bLoad->disable();
        panel->add(bLoad);

        tgui::ListBox::Ptr loadList = theme->load("listbox");
        loadList->setSize(pLoad->getSize().x*0.8f,pLoad->getSize().y*0.9f);
        loadList->setPosition(pLoad->getSize().x/2.0f - loadList->getSize().x/2.0f,pLoad->getSize().y*0.05f);
        loadList->setTextSize(TextSize);
        loadList->setItemHeight(TextSize*1.05f);
        pLoad->add(loadList,"list");

        std::string filePath = "Texture/Saves/";
        std::vector<std::string> allFiles = FileHandler::get_all_files_names_within_folder(filePath);
        for(auto& temp : allFiles){
            temp = temp.substr(0, temp.size() - 5);
            temp = temp.replace(temp.find('.'),1,":");
            loadList->addItem(temp);
        }

        bLoad->connect("clicked", [&,bLoad,loadList,filePath]() {
            lDebug("Button Load progress clicked");
            sound.SoundClick();
            if(!loadList->getSelectedItem().isEmpty()) {
                std::string temp = loadList->getSelectedItem();
                temp = temp.replace(temp.find(':'),1,".");
                std::string file = filePath+temp+".json";

                if (waveManager.loadState(json,file)) {
                    lDebug("Button Continue game clicked");
                    sound.SoundClickBack();
                    state.NextState(List_State::Game);
                    sound.restoreLastMusic();
                    menuPanel::removePanel(gui);
                    gameTimer.Start();
                }else{
                    lWarning("Failed to load save file "+file);
                }
            }
        });
    }
    catch (...){

    }
}
