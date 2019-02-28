//
// Created by Chrim14 on 05.10.2017.
//

#include "Menu.h"
#include "../../System/Map/FileHandler.h"
#include "MenuPanels.h"

void Menu::setBackground(tgui::Gui &gui) {


    tgui::Picture::Ptr background = tgui::Picture::create("Texture/Texture/system/background.jpg");
    background.get()->setSize(windowWidth, windowHeight);

    gui.add(background);
}

void Menu::Main(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    try {

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        Menu::setBackground(gui);

        tgui::Button::Ptr bFirst = tgui::Button::create();
        tgui::Button::Ptr bSecond = tgui::Button::create();

        bFirst = theme->load("Button");
        bFirst->setSize(windowWidth*bLength, windowHeight*bHeight);

        bSecond= theme->load("Button");
        bSecond->setSize(windowWidth*bLength, windowHeight*bHeight);
        bSecond->disable();
        bSecond->setOpacity(0.7f);
        
        tgui::Button::Ptr bThird  = tgui::Button::copy(bFirst);
        tgui::Button::Ptr bFourth = tgui::Button::copy(bFirst);

        bFirst->setPosition(windowWidth*bWidthStart, windowHeight*0.1f);
        bSecond->setPosition(windowWidth*bWidthStart, windowHeight*0.3f);
        bThird->setPosition(windowWidth*bWidthStart, windowHeight*0.5f);
        bFourth->setPosition(windowWidth*bWidthStart, windowHeight*0.7f);

        std::string spString = json.language["singleplayer"];
        std::string mpString = json.language["multiplayer"];
        std::string opString = json.language["options"];
        std::string exString = json.language["exit"];
        bFirst  ->setText(sf::String::fromUtf8(spString.begin(), spString.end()));
        bSecond ->setText(sf::String::fromUtf8(mpString.begin(), mpString.end()));
        bThird  ->setText(sf::String::fromUtf8(opString.begin(), opString.end()));
        bFourth ->setText(sf::String::fromUtf8(exString.begin(), exString.end()));

        bFirst->connect("clicked", [&]() {
            lDebug("Button Singleplayer clicked"), sound.SoundClick(), state.NextState(
                    List_State::Singleplayer_Menu), state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
        });
        
        bSecond->connect("clicked", [&]() {
                    lDebug("Button Multiplayer clicked"),
                    sound.SoundClick(),
                    state.NextState(List_State::Multiplayer_Menu),
                    state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
        });
        
        bThird->connect("clicked", [&]() {
                    lDebug("Button Options clicked"),
                    sound.SoundClick(),
                    state.NextState(List_State::Option_Menu),
                    state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
        });
        
        bFourth->connect("clicked", [&]() {
                    lDebug("Button Exit clicked"),
                    sound.SoundClickBack(),
                    state.NextState(List_State::Zero);
        });

        gui.add(bFirst);
        gui.add(bSecond);
        gui.add(bThird);
        gui.add(bFourth);
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void Menu::Option(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    try{

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        Menu::setBackground(gui);

        tgui::Button::Ptr bSettings, bMapEditor, bBack;

        bSettings = theme->load("Button");
        bSettings->setSize(windowWidth*bLength, windowHeight*bHeight);


        bMapEditor = tgui::Button::copy(bSettings);
        bBack = tgui::Button::copy(bSettings);

        bSettings->setPosition(windowWidth*bWidthStart, windowHeight*0.1f);
        bMapEditor->setPosition(windowWidth*bWidthStart, windowHeight*0.3f);
        bBack->setPosition(windowWidth*bWidthStart, windowHeight*0.5f);

        std::string setString = json.language["settings"];
        std::string mapString = json.language["mapeditor"];
        std::string backString = json.language["back"];

        bSettings  ->setText(sf::String::fromUtf8(setString.begin(), setString.end()));
        bMapEditor ->setText(sf::String::fromUtf8(mapString.begin(), mapString.end()));
        bBack      ->setText(sf::String::fromUtf8(backString.begin(), backString.end()));

        
        bSettings->connect("clicked", [&]() {
            lDebug("Button Settings clicked"),
                    sound.SoundClick(), state.NextState(List_State::Settings),
                    state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });
        
        bMapEditor->connect("clicked", [&]() {
                    lDebug("Button MapEditor clicked"),
                    sound.SoundClick(),
                    state.NextState(List_State::EditorSetup),
                    state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });
        
        bBack->connect("clicked", [&]() {
                lDebug("Button Back clicked"),
                sound.SoundClickBack(),
                state.NextState(List_State::Zero),
                state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });

        gui.add(bSettings);
        gui.add(bMapEditor);
        gui.add(bBack);

    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void Menu::SingelPlayer(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    try{

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        Menu::setBackground(gui);

        tgui::Button::Ptr bFirst = tgui::Button::create();

        bFirst = theme->load("Button");
        bFirst->setSize(windowWidth*bLength, windowHeight*bHeight);

        tgui::Button::Ptr bSecond = tgui::Button::copy(bFirst);
        tgui::Button::Ptr bThird  = tgui::Button::copy(bFirst);

        bFirst ->setPosition(windowWidth*bWidthStart, windowHeight*0.1f);
        bSecond->setPosition(windowWidth*bWidthStart, windowHeight*0.3f);
        bThird ->setPosition(windowWidth*bWidthStart, windowHeight*0.5f);

        std::string gameString = json.language["game"];
        std::string newString  = json.language["new"];
        std::string loadString = json.language["load"];
        std::string backString = json.language["back"];

        newString  = newString  + " " + gameString;
        loadString = loadString + " " + gameString;

        bFirst  ->setText(sf::String::fromUtf8(newString.begin(), newString.end()));
        bSecond ->setText(sf::String::fromUtf8(loadString.begin(), loadString.end()));
        bThird  ->setText(sf::String::fromUtf8(backString.begin(), backString.end()));

        
        bFirst ->connect("clicked", [&]() {
                    lDebug("Button New Game clicked"),
                    sound.SoundClick(),
                    state.NextState(List_State::New_Game),
                    state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });
        
        bSecond->connect("clicked", [&]() {
                    lDebug("Button Load Game clicked"),
                    sound.SoundClick(),
                    state.NextState(List_State::Load_Game),
                    state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });
        
        bThird ->connect("clicked", [&]() {
                    lDebug("Button Back clicked"),
                    sound.SoundClickBack(),
                    state.NextState(List_State::Zero),
                    state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });

        gui.add(bFirst);
        gui.add(bSecond);
        gui.add(bThird);
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void Menu::MultiPlayer(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    try{
        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

        Menu::setBackground(gui);

        tgui::Button::Ptr bFirst = tgui::Button::create();

        bFirst = theme->load("Button");
        bFirst->setSize(windowWidth*bLength, windowHeight*bHeight);

        tgui::Button::Ptr bSecond = tgui::Button::copy(bFirst);
        tgui::Button::Ptr bThird  = tgui::Button::copy(bFirst);

        bFirst->setPosition(windowWidth*bWidthStart, windowHeight*0.1f);
        bSecond->setPosition(windowWidth*bWidthStart, windowHeight*0.3f);
        bThird->setPosition(windowWidth*bWidthStart, windowHeight*0.5f);

        std::string gameString = json.language["game"];
        std::string hostString  = json.language["host"];
        std::string joinString = json.language["join"];
        std::string backString = json.language["back"];

        hostString = hostString + " " + gameString;
        joinString = joinString + " " + gameString;

        bFirst  ->setText(sf::String::fromUtf8(hostString.begin(), hostString.end()));
        bSecond ->setText(sf::String::fromUtf8(joinString.begin(), joinString.end()));
        bThird  ->setText(sf::String::fromUtf8(backString.begin(), backString.end()));

        bFirst->connect("clicked", [&]() {
                    lDebug("Button Host Game clicked"),
                    sound.SoundClick(),
                    state.NextState(List_State::Host_Game),
                    state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });
        
        bSecond->connect("clicked", [&]() {
                    lDebug("Button Join Game clicked"),
                    sound.SoundClick(),
                    state.NextState(List_State::Join_Game),
                    state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });
        
        bThird->connect("clicked", [&]() {
                    lDebug("Button Back clicked"),
                    sound.SoundClickBack(),
                    state.NextState(List_State::Zero),
                    state.updateInterface(gameTimer,gui,window,state, json, sound, waveManager);
        });

        gui.add(bFirst);
        gui.add(bSecond);
        gui.add(bThird);
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void Menu::LanguageSetting(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    SettingButtons sb;

    try{

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        Menu::setBackground(gui);

        tgui::Button::Ptr bBack, bApply;

        std::string backString = json.language["back"];
        std::string applyString = json.language["apply"];

        ///BUTTON: BACK
        bBack = theme->load("Button");
        bBack ->setSize(windowWidth*0.15f, windowHeight*0.07f);
        bBack ->setPosition(windowWidth*0.01f, windowHeight*0.92f);
        bBack ->setText(sf::String::fromUtf8(backString.begin(), backString.end()));
        gui.add(bBack);

        ///BUTTON: APPLY SETTINGS
        bApply = tgui::Button::copy(bBack);
        bApply ->setPosition(windowWidth*0.84f, windowHeight*0.92f);
        bApply ->setText(sf::String::fromUtf8(applyString.begin(), applyString.end()));
        bApply ->connect("clicked", [&]() {
            lDebug("Button Apply clicked"),
                    sound.SoundClick(),
                    sb.applySelectedLanguage(json, gui),
                    state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
        });
        gui.add(bApply);


        ///LISTBOX: LANGUAGE LIST
        tgui::ListBox::Ptr list;
        list = theme->load("ListBox");
        list->setSize(windowWidth*0.7f, windowHeight*0.8f);
        list->setPosition(windowWidth*0.15f, windowHeight*0.1f);

        std::string selectedLanguage = json.setting["language"];
        list->setSelectedItem(selectedLanguage);

        list->setTextSize(20);

        gui.add(list, "list");

        FileHandler fileHandler;

        fileHandler.getFiles("Texture/Language", "list","", gui);

        std::string labelString = json.language["packet"];
        tgui::Label::Ptr label;
        label = theme->load("label");
        label->setPosition(windowWidth*0.15f, windowHeight*0.02f);
        label->setTextSize(30);
        label->setText(sf::String::fromUtf8(labelString.begin(), labelString.end()));
        gui.add(label);


        bBack->connect("clicked", [&]() {
            lDebug("Button back clicked"),
                    sound.SoundClickBack(),
                    state.NextState(List_State::Zero),
                    state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
        });

    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void Menu::KeybindingSettings(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    SettingButtons sb;

    try{

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        Menu::setBackground(gui);

        tgui::Button::Ptr bExit, bBack, bApply;

        ///BUTTON: BACK
        bBack = theme->load("Button");
        bBack ->setSize(windowWidth*0.15f, windowHeight*0.07f);
        bBack ->setPosition(windowWidth*0.01f, windowHeight*0.92f);
        std::string backString = json.language["back"];
        bBack ->setText(sf::String::fromUtf8(backString.begin(), backString.end()));

        bBack->connect("clicked", [&]() {
            lDebug("Button Exit clicked"),
                    sound.SoundClickBack(),
                    state.NextState(List_State::Zero),
                    state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
        });
        gui.add(bBack);

        ///BUTTON: APPLY SETTINGS
        bApply = tgui::Button::copy(bBack);
        bApply ->setPosition(windowWidth*0.84f, windowHeight*0.92f);
        std::string applyString = json.language["apply"];
        bApply ->setText(sf::String::fromUtf8(applyString.begin(), applyString.end()));

        bApply ->connect("clicked", [&]() {
                    lDebug("Button Apply clicked"),
                    sound.SoundClick(),
                    sb.applySettings(false, window, gui, json, sound),
                    state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
        });
        gui.add(bApply);

        ///BUTTON: CHANGE EXIT KEY
        bExit = tgui::Button::copy(bBack);
        bExit->setPosition(windowWidth*bWidthStart, windowHeight*0.1f);
        std::string exitString = json.language["exit"];
        bExit->setText(sf::String::fromUtf8(exitString.begin(), exitString.end()));

        bExit->connect("clicked", [&](){
            lDebug("Button change exit key clicked"),
            sound.SoundClick();
        });
        gui.add(bExit);

    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}

void Menu::getNewGameMenu(Timer &gameTimer,tgui::Gui &gui, sf::RenderWindow &window, StateMachine &state, Settings &json, Sound &sound, WaveManager &waveManager) {

    FileHandler fileHandler;

    try{

        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        Menu::setBackground(gui);

        std::string backString = json.language["back"];
        std::string startString = json.language["start"];

        tgui::Button::Ptr bLoad = theme->load("Button");
        bLoad ->setSize(windowWidth*0.15f, windowHeight*0.07f);
        bLoad ->setPosition(windowWidth*0.84f, windowHeight*0.82f);
        bLoad ->setText(sf::String::fromUtf8(startString.begin(), startString.end()));
        bLoad ->setOpacity(0.3f);
        bLoad ->disable();
        bLoad->connect("clicked", [&](){
            lDebug("Button Start new game clicked");
            fileHandler.loadMap("list","pGames",json,gui);
            tgui::Label::Ptr errorLabel = gui.get<tgui::Label>("fileMessage");
            std::string message = gui.get<tgui::Label>("fileMessage")->getText();

            if(errorLabel != nullptr && message.empty()) {
                json.mapPreview = false;
                json.mapSelected = false;
                sound.getClickStart();
                fileHandler.refectorJsonInto2DArray(json);
                state.NextState(List_State::Game);
                state.updateInterface(gameTimer,gui, window, state, json, sound, waveManager);
                sound.StartGameMusic_1();
            }
        });
        gui.add(bLoad, "bLoad");

        tgui::Button::Ptr bBack = theme->load("Button");
        bBack ->setSize(bLoad->getSize());
        bBack ->setPosition(bLoad->getPosition().x, bLoad->getPosition().y + bLoad->getSize().y*1.25f);
        bBack ->setText(sf::String::fromUtf8(backString.begin(), backString.end()));
        bBack->connect("clicked", [&]() {
            lDebug("Button Back clicked");
            sound.SoundClickBack();
            state.NextState(List_State::Zero);
            state.updateInterface(gameTimer,gui,window,state,json,sound, waveManager);
        });
        gui.add(bBack);

        tgui::Label::Ptr label = theme->load("label");
        label->setPosition(50,50);
        label->setTextSize(20);
        gui.add(label, "fileMessage");



        tgui::ChatBox::Ptr chatBox = theme->load("ChatBox");
        chatBox->setPosition(windowWidth*0.02f,windowHeight*0.74f);
        chatBox->setSize(windowWidth*0.65f,windowHeight*0.18f);
        chatBox->setNewLinesBelowOthers(true);
        gui.add(chatBox);

        tgui::Button::Ptr bSend = theme->load("button");
        bSend->setSize(chatBox->getSize().x*0.2f,windowHeight*0.06f);
        bSend->setPosition(chatBox->getPosition().x + chatBox->getSize().x - bSend->getSize().x, chatBox->getPosition().y+chatBox->getSize().y*1.05f);
        bSend->setText("Send");
        gui.add(bSend);

        tgui::EditBox::Ptr chatText = theme->load("editbox");
        chatText->setPosition(chatBox->getPosition().x,bSend->getPosition().y);
        chatText->setSize(chatBox->getSize().x - bSend->getSize().x*1.1f, bSend->getSize().y);
        chatText->connect("ReturnKeyPressed", [&,chatText,bSend,chatBox](){
            std::string message = chatText->getText();
            if(!message.empty()){
                std::string name = json.setting.at("name");
                chatBox->addLine(name+": "+message, sf::Color::Yellow);
                chatText->setText("");
                chatText->focus();
            }
        });
        gui.add(chatText);

        bSend->connect("clicked", [&,chatText,bSend,chatBox](){
            std::string message = chatText->getText();
            if(!message.empty()){
                std::string name = json.setting.at("name");
                chatBox->addLine(name+": "+message, sf::Color::Yellow);
                chatText->setText("");
                chatText->focus();
            }
        });

        tgui::Panel::Ptr pInfo = theme->load("panel");
        pInfo->setSize(windowWidth*0.28f, windowHeight*0.74f);
        pInfo->setPosition(windowWidth*0.71,windowHeight*0.02f);
        pInfo->setBackgroundColor(sf::Color(0,0,0,0));
        gui.add(pInfo);

        tgui::TextBox::Ptr box = theme->load("textbox");
        box->setSize(pInfo->getSize());
        box->disable(true);
        pInfo->add(box);

        tgui::Label::Ptr lMapName = theme->load("label");
        lMapName->setTextSize(TextSize);
        lMapName->setTextColor(sf::Color::Yellow);
        lMapName->setPosition(pInfo->getSize().x*0.05f,lMapName->getTextSize()+pInfo->getSize().y*0.005f);
        pInfo->add(lMapName);

        tgui::Label::Ptr lPlayers = theme->load("label");
        lPlayers->setTextSize(TextSize);
        lPlayers->setTextColor(sf::Color::Yellow);
        lPlayers->setPosition(pInfo->getSize().x*0.05f,lMapName->getTextSize()+pInfo->getSize().y*0.55f);
     //   lPlayers->setText("Players: ");
        pInfo->add(lPlayers);

        tgui::Label::Ptr lSize = theme->load("label");
        lSize->setTextSize(TextSize);
        lSize->setTextColor(sf::Color::Yellow);
        lSize->setPosition(lPlayers->getPosition().x,lPlayers->getPosition().y + lPlayers->getTextSize()*1.5f);
        pInfo->add(lSize);

        tgui::Label::Ptr lSpawns = theme->load("label");
        lSpawns->setTextSize(TextSize);
        lSpawns->setPosition(pInfo->getSize().x*0.5f,lMapName->getTextSize()+pInfo->getSize().y*0.55f);
        pInfo->add(lSpawns);

        tgui::Label::Ptr story = theme->load("Label");
        story->setPosition(lSize->getPosition().x, lSize->getPosition().y + lSize->getTextSize()*1.8f);
        story->setSize(pInfo->getSize().x-story->getPosition().x*2,pInfo->getSize().y-story->getSize().y*1.01f);
        pInfo->add(story);
        story->setTextSize(TextSize*0.8f);
        story->setMaximumTextWidth(pInfo->getSize().x-story->getPosition().x*2);
        story->setTextColor(sf::Color(204,204,0));

        tgui::Picture::Ptr image = tgui::Picture::create("Texture/Texture/system/background.jpg",true);
        image->hide();
        image.get()->setPosition(pInfo->getSize().x *0.05f, pInfo->getSize().y * 0.1f);
        image.get()->setSize(pInfo->getSize().x * 0.9f, pInfo->getSize().y * 0.45f);
        image->connect("clicked", [&](){
            json.mapImage = !json.mapImage;
        });
        pInfo->add(image,"image");

        float sizeX = 1.0f/gui.getSize().x;
        float sizeY = 1.0f/gui.getSize().y;
        json.view["map"].setViewport(sf::FloatRect(sizeX*pInfo->getPosition().x+(sizeX*pInfo->getSize().x*0.05f), sizeY*pInfo->getPosition().y+(sizeY*pInfo->getSize().y*0.1f), sizeX*pInfo->getSize().x*0.90f, sizeY*pInfo->getSize().y*0.46f));

        tgui::Panel::Ptr pGame = theme->load("panel");
        pGame->setPosition(chatBox->getPosition().x, pInfo->getPosition().y);
        pGame->setSize(chatBox->getSize().x, window.getSize().y*0.2f);
        gui.add(pGame,"pGames");

        tgui::TextBox::Ptr box2 = theme->load("textbox");
        box2->setSize(pGame->getSize());
        box2->disable(true);
        pGame->add(box2);

        tgui::Label::Ptr label_maps = theme->load("label");
        label_maps->setPosition(pGame->getSize().x*0.01f,pGame->getSize().y*0.05f);
        label_maps->setTextSize(TextSize);
        label_maps->setTextColor(sf::Color::Yellow);
        label_maps->setText("Maps:");
        pGame->add(label_maps);

        tgui::ListBox::Ptr lMaps = theme->load("ListBox");
        lMaps ->setPosition(label_maps->getPosition().x + label_maps->getSize().x*1.5f,label_maps->getPosition().y);
        lMaps ->setSize(pGame->getSize().x*0.4f, pGame->getSize().y - label_maps->getPosition().y*2);
        lMaps ->setTextSize(TextSize);
        lMaps ->setItemHeight(TextSize*1.05f);

        pGame->add(lMaps,"list");
        fileHandler.getFiles("Texture/Maps", "list","pGames", gui);
        try { lMaps->setSelectedItemById("0"); } catch (...){}


        tgui::Label::Ptr lDifficulity = theme->load("label");
        lDifficulity->setPosition(lMaps->getPosition().x+lMaps->getSize().x*1.1f,pGame->getSize().y*0.05f);
        lDifficulity->setText("Difficulity");
        lDifficulity->setTextSize(TextSize);
        lDifficulity->setTextColor(sf::Color::Yellow);
        pGame->add(lDifficulity);

        tgui::ComboBox::Ptr boxDifficulity = theme->load("combobox");
        boxDifficulity->setPosition(lDifficulity->getPosition().x,lDifficulity->getPosition().y+lDifficulity->getTextSize()*1.1f);
        boxDifficulity->setSize(pGame->getSize().x*0.20f,pGame->getSize().y*0.2f);
        boxDifficulity->addItem("Easy");
        boxDifficulity->addItem("Medium");
        boxDifficulity->addItem("Hard");
        boxDifficulity->addItem("Death wish");
        boxDifficulity->setSelectedItem("Medium");
        pGame->add(boxDifficulity);


        tgui::Label::Ptr lMode = theme->load("label");
        lMode->setPosition(lDifficulity->getPosition().x,boxDifficulity->getPosition().y + boxDifficulity->getSize().y*1.4f);
        lMode->setText("Game Mode");
        lMode->setTextSize(TextSize);
        lMode->setTextColor(sf::Color::Yellow);
        pGame->add(lMode);

        tgui::ComboBox::Ptr boxGameMode = theme->load("combobox");
        boxGameMode->setPosition(lMode->getPosition().x,lMode->getPosition().y+lMode->getTextSize()*1.1f);
        boxGameMode->setSize(boxDifficulity->getSize());
        boxGameMode->addItem("Waves");
        boxGameMode->addItem("Survival");
        boxGameMode->setSelectedItem("Waves");
        pGame->add(boxGameMode);

        tgui::Panel::Ptr pPlayers = theme->load("panel");
        pPlayers->setPosition(chatBox->getPosition().x, (pGame->getSize().y+pGame->getPosition().y)*1.05f);
        pPlayers->setSize(chatBox->getSize().x, window.getSize().y - (pGame->getSize().y+pGame->getPosition().y) - (window.getSize().y-chatBox->getPosition().y));
        pPlayers->setBackgroundColor(sf::Color(0,0,0,0));
        gui.add(pPlayers,"players");


        lMaps->connect("ItemSelected", [&,label,lMaps,lMapName,lPlayers,lSize,story,pInfo,image,lSpawns,bLoad,pPlayers]() {
            menuPanel::getMapSelected(json,gui,label,lMaps,lSize,lMapName,lPlayers,lSpawns,story,image,bLoad,pPlayers);
        });

        menuPanel::getPlayers(json, gui);
        menuPanel::getMapSelected(json,gui,label,lMaps,lSize,lMapName,lPlayers,lSpawns,story,image,bLoad,pPlayers);

    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        lFatal("TGUI could not be created");
    }
}
