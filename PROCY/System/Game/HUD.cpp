//
// Created by Masaya on 10/24/2017.
//

#include "HUD.h"
#include "TGUI/TGUI.hpp"




tgui::Label::Ptr gameTime;
int minutes = 0;
int seconds = 0;
std::string secondsString;
std::string minutesString;

void HUD::initializeHUD(std::string &towerSelected,std::vector<tgui::Panel::Ptr> &panels,tgui::Gui& gui, StateMachine &state, sf::RenderWindow &window, Settings &json, Sound& sound, sf::View &view){
    tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");

    // draw under here
    /*tgui::Panel::Ptr mainPanel = theme->load("Panel");
    mainPanel->getRenderer()->setBackgroundColor({0,0,0,230});
    mainPanel->setSize(tgui::Layout2d(window.getSize().x,window.getSize().y/3));
    mainPanel->setPosition(tgui::Layout2d(0,(window.getSize().y/3)*2));*/

    tgui::Picture::Ptr panel1 = tgui::Picture::create("Texture/Texture/system/panel.jpg");
    tgui::Picture::Ptr panel2 = tgui::Picture::create("Texture/Texture/system/panel.jpg");
    tgui::Picture::Ptr panel3 = tgui::Picture::create("Texture/Texture/system/panel.jpg");
    tgui::Picture::Ptr panel4 = tgui::Picture::create("Texture/Texture/system/panel.jpg");
    tgui::Picture::Ptr panel5 = tgui::Picture::create("Texture/Texture/system/panel.jpg");
    tgui::Picture::Ptr panel6 = tgui::Picture::create("Texture/Texture/system/panel.jpg");
    tgui::Picture::Ptr panel7 = tgui::Picture::create("Texture/Texture/system/panel.jpg");
    tgui::Picture::Ptr panel8 = tgui::Picture::create("Texture/Texture/system/panel.jpg");

    // Defining the 4 main panels
    tgui::Panel::Ptr leftPanel = theme->load("Panel");
    leftPanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    leftPanel->setSize(tgui::Layout2d(window.getSize().x / 4, (window.getSize().x/4)/1.3333));
    leftPanel->setPosition(0, (window.getSize().y) - (window.getSize().x/4)/1.3333);
    panel1->setSize(leftPanel->getSize().x, leftPanel->getSize().y);
    leftPanel->add(panel1, "leftPanelTexture");

    tgui::Panel::Ptr miniMapFramePanel = theme->load("Panel");
    miniMapFramePanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    miniMapFramePanel->setSize(tgui::Layout2d(100,100));
    miniMapFramePanel->setPosition(tgui::Layout2d(0,0));
    leftPanel->add(miniMapFramePanel, "miniMapFramePanel");
    miniMapFramePanel->hide();

    tgui::Panel::Ptr middlePanel = theme->load("Panel");
    middlePanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    middlePanel->setSize(tgui::Layout2d((window.getSize().x / 4)*2, (window.getSize().x/4)/1.6));
    middlePanel->setPosition((window.getSize().x / 4), (window.getSize().y) - (window.getSize().x/4)/1.6);
    //panel2->setSize(middlePanel->getSize());
    //middlePanel->add(panel2, "middlePanelTexture");

    // Elements for middlePanel
    tgui::Panel::Ptr selectionPanel = theme->load("Panel");
    selectionPanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    selectionPanel->setSize((middlePanel->getSize().x/4)*3,middlePanel->getSize().y);
    selectionPanel->setPosition(0,0);
    middlePanel->add(selectionPanel,"selectionPanel");

    tgui::Panel::Ptr selectionPicturePanel = theme->load("Panel");
    selectionPicturePanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    selectionPicturePanel->setSize(selectionPanel->getSize().x * 0.3f,selectionPanel->getSize().y);
    selectionPicturePanel->setPosition(0,0);
    selectionPanel->add(selectionPicturePanel,"selectionPicturePanel");
    panel5->setSize(selectionPicturePanel->getSize());
    panel5->setPosition(0,0);
    middlePanel->add(panel5);

    healthBarRect.setTexture(&json.texture["progressBar"],false);
    healthBarRect.setPosition(sf::Vector2f(selectionPicturePanel->getAbsolutePosition().x+selectionPicturePanel->getSize().x*0.1f, selectionPicturePanel->getAbsolutePosition().y+selectionPicturePanel->getSize().x*0.8f+selectionPicturePanel->getSize().x*0.1f));
    healthBarRect.setSize(sf::Vector2f(selectionPicturePanel->getSize().x*0.8f,(selectionPicturePanel->getSize().y-selectionPicturePanel->getSize().x*0.8f-selectionPicturePanel->getSize().x*0.2f)/2));
    healthBarRect.setScale(1,1);


    if (!font.loadFromFile("Texture/Texture/system/sansation.ttf")){};


    healthText.setFont(font);
    healthText.setCharacterSize((unsigned int)healthBarRect.getSize().y/2);
    healthText.setString("100/100");
    sf::FloatRect textRect = healthText.getLocalBounds();
    healthText.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    healthText.setPosition(healthBarRect.getPosition().x+(healthBarRect.getSize().x*0.5f),healthBarRect.getPosition().y+(healthBarRect.getSize().y*0.5f));
    healthText.setFillColor(sf::Color::White);

    healthFrame.setTexture(json.texture["miniMapFrame"]);
    healthFrame.setPosition(healthBarRect.getPosition());
    healthFrame.setScale(healthBarRect.getSize().x/healthFrame.getTexture()->getSize().x,healthBarRect.getSize().y/healthFrame.getTexture()->getSize().y);

    manaBarRect.setTexture(&json.texture["manaBar"],false);
    manaBarRect.setPosition(sf::Vector2f(selectionPicturePanel->getAbsolutePosition().x+selectionPicturePanel->getSize().x*0.1f, selectionPicturePanel->getAbsolutePosition().y+selectionPicturePanel->getSize().x*0.8f+selectionPicturePanel->getSize().x*0.1f+healthBarRect.getSize().y));
    manaBarRect.setSize(sf::Vector2f(selectionPicturePanel->getSize().x*0.8f,(selectionPicturePanel->getSize().y-selectionPicturePanel->getSize().x*0.8f-selectionPicturePanel->getSize().x*0.2f)/2));
    manaBarRect.setScale(1,1);


    manaText.setFont(font);
    manaText.setCharacterSize((unsigned int)healthBarRect.getSize().y/2);
    manaText.setString("100/100");
    sf::FloatRect textRect2 = manaText.getLocalBounds();
    manaText.setOrigin(textRect2.left + textRect2.width/2.0f,
                         textRect2.top  + textRect2.height/2.0f);
    manaText.setPosition(healthBarRect.getPosition().x+(healthBarRect.getSize().x*0.5f),manaBarRect.getPosition().y+(manaBarRect.getSize().y*0.5f));
    manaText.setFillColor(sf::Color::White);

    manaFrame.setTexture(json.texture["miniMapFrame"]);
    manaFrame.setPosition(manaBarRect.getPosition());
    manaFrame.setScale(manaBarRect.getSize().x/manaFrame.getTexture()->getSize().x,manaBarRect.getSize().y/manaFrame.getTexture()->getSize().y);

    tgui::Panel::Ptr selectionInfoPanel = theme->load("Panel");
    selectionInfoPanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    selectionInfoPanel->setSize(selectionPanel->getSize().x * 0.7f,selectionPanel->getSize().y);
    selectionInfoPanel->setPosition(selectionPicturePanel->getSize().x,0);
    selectionPanel->add(selectionInfoPanel,"selectionInfoPanel");
    panel6->setSize(selectionInfoPanel->getSize());
    panel6->setPosition(panel5->getSize().x,0);
    middlePanel->add(panel6);

    tgui::Panel::Ptr inventoryPanel = theme->load("Panel");
    inventoryPanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    inventoryPanel->setSize((middlePanel->getSize().x/4),middlePanel->getSize().y);
    inventoryPanel->setPosition((middlePanel->getSize().x/4)*3,0);
    middlePanel->add(inventoryPanel,"inventoryPanel");
    panel7->setSize(inventoryPanel->getSize());
    panel7->setPosition(panel5->getSize().x + panel6->getSize().x,0);
    middlePanel->add(panel7);

    selectionPanel->moveToFront();

    tgui::Panel::Ptr rightPanel = theme->load("Panel");
    rightPanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    rightPanel->setSize(tgui::Layout2d(window.getSize().x / 4, (window.getSize().x/4)/1.3333));
    rightPanel->setPosition(
            tgui::Layout2d((window.getSize().x / 4) * 3, (window.getSize().y) - (window.getSize().x/4)/1.3333));
    panel3->setSize(rightPanel->getSize());
    rightPanel->add(panel3, "rightPanelTexture");

    tgui::Panel::Ptr infoPanel = theme->load("Panel");
    infoPanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    infoPanel->setSize(rightPanel->getSize().x, 200);
    infoPanel->setPosition(
            tgui::Layout2d(rightPanel->getPosition().x,rightPanel->getPosition().y-infoPanel->getSize().y));
    infoPanel->hide();
    gui.add(infoPanel,"infoPanel");

    tgui::Panel::Ptr topPanel = theme->load("Panel");
    topPanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    topPanel->setSize(tgui::Layout2d(window.getSize().x+100, window.getSize().y * 0.05f + 40));
    topPanel->setPosition(tgui::Layout2d(-50,-30));
    panel4->setSize(topPanel->getSize());
    topPanel->add(panel4, "topPanelTexture");

/*
    tgui::Button::Ptr menuTop = theme->load("Button");
    menuTop->setSize(125,30);
    menuTop->setText("Menu");
    menuTop->setPosition(window.getSize().x/5,40);
*/

    gold = theme->load("label");
    //tgui::EditBox::Ptr currency = theme->load("EditBox");
    gold->setSize(150,25);
    gold->setPosition((window.getSize().x/5)*4,40);
    gold->setTextSize(18);
    tgui::Picture::Ptr goldPic = tgui::Picture::create(json.texture["bitCoin"],false);
    goldPic->setSize(tgui::bindHeight(gold),tgui::bindHeight(gold));
    goldPic->setPosition(tgui::bindLeft(gold) - tgui::bindHeight(goldPic),tgui::bindTop(gold));


    /*tgui::Picture::Ptr curIcon = tgui::Picture::create("Texture/Texture/icon.png");
    curIcon->setSize(20,20);
    curIcon->setPosition((window.getSize().x/5)*4+2,42);*/

    gameTime = theme->load("label");
    gameTime->setText("00:00");
    gameTime->setTextSize(30);
    gameTime->setPosition((window.getSize().x/2), 40);
    topPanel->add(gameTime, "topGameTime");
    //topPanel->add(menuTop, "topMenuButton");
    topPanel->add(gold, "topCurrency");
    topPanel->add(goldPic, "goldPicture");
    //topPanel->add(curIcon, "topCurrencyIcon");

    tgui::Grid::Ptr grid = tgui::Grid::create();
    grid->setSize(rightPanel->getSize().x * 0.8f, rightPanel->getSize().y * 0.8f);
    grid->setPosition(rightPanel->getSize().x*0.1f, rightPanel->getSize().y*0.1f);
    rightPanel->add(grid,"rightPanelGrid");

    // Add all the towers to the grid
    unsigned int gridRow = 0;
    unsigned int gridColumn = 0;
    for(unsigned int i = 1;i < json.towerSprites.size()+1;i++){
        std::string towerString = "tower_"+std::to_string(i);
        std::string towerName = json.towerSprites[towerString].towerName;
        tgui::Panel::Ptr panel = theme->load("Panel");
        panel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
        panel->setSize(grid->getSize().x*0.25f,grid->getSize().y*0.3333f);
        tgui::Picture::Ptr tower = tgui::Picture::create(json.texture[towerString],true);
        tgui::Picture::Ptr frame = tgui::Picture::create(json.texture["miniMapFrame"],false);
        tower->setPosition(0,0);
        tower->setSize(grid->getSize().x*0.25f,grid->getSize().y*0.3333f);
        frame->setPosition(0,0);
        frame->setSize(grid->getSize().x*0.25f,grid->getSize().y*0.3333f);

        // Get some tower data to include in the lambda'
        std::string towerType = json.towerSprites[towerString].towerType;
        std::string towerRange = std::to_string(json.towerSprites[towerString].range);
        std::string towerCost = std::to_string(json.towerSprites[towerString].buildingCost);
        std::string towerDescription = json.towerSprites[towerString].towerDescription;

        tower->connect("clicked",[&,towerString](){
            lDebug("Picture "+towerString+" clicked"),
            sound.SoundClick(),
            towerSelected = towerString;

        });
        tower->connect("MouseEntered",[&,infoPanel,panel8,theme,towerName,towerDescription,towerCost](){

            infoPanel->add(panel8);

            // Add the tower name
            tgui::Label::Ptr label = theme->load("Label"), label2;
            label->setText(towerName);
            label->setTextSize(18);
            label->setPosition(tgui::bindWidth(infoPanel)*0.5f - tgui::bindWidth(label)*0.5f,tgui::bindTop(infoPanel)*0.1f);
            infoPanel->add(label);

            tgui::Label::Ptr costLabel = theme->load("Label");
            costLabel->setText("Cost: "+towerCost);
            costLabel->setAutoSize(true);
            costLabel->setTextColor(sf::Color::Yellow);
            costLabel->setSize(tgui::Layout2d(tgui::bindWidth(infoPanel)*0.8f,tgui::bindHeight(label)));

            // Add the tower range
            label2 = theme->load("Label");
            label2->setText(towerDescription);
            label2->setTextSize(18);
            label2->setAutoSize(true);
            label2->setTextColor(sf::Color::Green);
            label2->setSize(tgui::Layout2d(tgui::bindWidth(infoPanel)*0.8f,tgui::bindHeight(infoPanel)*0.8f-tgui::bindHeight(label)-tgui::bindHeight(costLabel)));
            label2->setPosition(tgui::bindWidth(infoPanel)*0.1f,tgui::bindTop(infoPanel)*0.1f+tgui::bindHeight(label));
            infoPanel->add(label2);

            costLabel->setPosition(tgui::bindWidth(infoPanel)*0.1f,tgui::bindTop(infoPanel)*0.1f+tgui::bindHeight(label)+tgui::bindHeight(label2));
            infoPanel->add(costLabel);

            panel8->setPosition(0,0);
            panel8->setSize(infoPanel->getSize());
            infoPanel->show();
        });
        tower->connect("MouseLeft",[&,infoPanel](){
            infoPanel->removeAllWidgets();
            infoPanel->hide();
        });
        if(gridColumn == 4){
            gridRow++;
            gridColumn = 0;
        }
        panel->add(frame);
        panel->add(tower, towerString);
        grid->addWidget(panel,gridRow,gridColumn);
        towerGrid[towerString] = std::make_pair(json.towerSprites[towerString].buildingCost,tower);
        gridColumn++;
    }
    tgui::Picture::Ptr frame = tgui::Picture::create(json.texture["miniMapFrame"],false);
    frame->setPosition(0,0);
    frame->setSize(grid->getSize().x*0.25f,grid->getSize().y*0.3333f);


    tgui::Grid::Ptr inventoryGrid = tgui::Grid::create();
    inventoryGrid->setSize(inventoryPanel->getSize().x * 0.8f, inventoryPanel->getSize().y * 0.8f);
    inventoryGrid->setPosition(inventoryPanel->getSize().x*0.1f, inventoryPanel->getSize().y*0.1f);
    inventoryPanel->add(inventoryGrid,"inventoryGrid");

    gridRow = 0;
    gridColumn = 0;
    for(unsigned int i = 1;i < 7;i++) {
        tgui::Panel::Ptr panel = theme->load("Panel");
        panel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
        panel->setSize(inventoryGrid->getSize().x * 0.5f, inventoryGrid->getSize().y * 0.3333f);
        tgui::Picture::Ptr bagIcon = tgui::Picture::create(json.texture["bagIcon"], true);
        tgui::Picture::Ptr frame2 = tgui::Picture::create(json.texture["miniMapFrame"], false);
        frame2->setOpacity(0.5);
        bagIcon->setPosition(inventoryGrid->getSize().x * 0.05f,inventoryGrid->getSize().y * 0.01665);
        bagIcon->setSize(inventoryGrid->getSize().x * 0.4f, inventoryGrid->getSize().y * 0.3f);
        frame2->setPosition(0, 0);
        frame2->setSize(inventoryGrid->getSize().x * 0.5f, inventoryGrid->getSize().y * 0.3333f);

        if(gridColumn == 2){
            gridRow++;
            gridColumn = 0;
        }
        panel->add(frame2);
        panel->add(bagIcon);
        inventoryGrid->addWidget(panel,gridRow,gridColumn);
        gridColumn++;
    }
    inventoryPanel->moveToFront();

    panels.push_back(middlePanel);
    panels.push_back(leftPanel);
    panels.push_back(rightPanel);
    panels.push_back(topPanel);

    gui.add(middlePanel, "middlePanel");
    gui.add(leftPanel, "leftPanel");
    gui.add(rightPanel, "rightPanel");
    gui.add(topPanel, "topPanel");
}

void HUD::hudHandler(std::string &towerSelected,Timer &gameTimer,bool &hudLoaded,std::vector<tgui::Panel::Ptr> &panels,tgui::Gui& gui, StateMachine &state, sf::RenderWindow &window, Settings &json, Sound& sound, sf::View &view) {

    if(state.getState() == List_State::Game || state.getState() == List_State::Pause) {
        //view.setViewport(sf::FloatRect(0,0,1,1));
        window.setView(view);

        if(hudLoaded) {
            updateGameTimer(gameTimer);
            if(state.getState() == List_State::Game) {
                gui.draw();
            }

                window.setView(json.view["fixed"]);
                window.draw(healthBarRect);
                window.draw(manaBarRect);
                window.draw(healthText);
                window.draw(manaText);
                window.draw(healthFrame);
                window.draw(manaFrame);

            if(state.getState() == List_State::Pause) {
                gui.draw();
            }
        }

        if(!hudLoaded){
            initializeHUD(towerSelected,panels,gui,state,window, json, sound, view);
            hudLoaded = true;
            gameTimer.Reset();
        }
    }else{
        hudLoaded = false;
    }
}

void HUD::handleHealthBar(tgui::Gui &gui, Settings &json){
    if(towerSelected != nullptr) {
        healthText.setString(std::to_string(towerSelected->health) + "/" + std::to_string(towerSelected->maxHealth));
        healthBarRect.setScale(1*((float)towerSelected->health/(float)towerSelected->maxHealth),1);
    }else if(playerSelected != nullptr){
        healthText.setString(std::to_string(playerSelected->getHealth()) + "/" + std::to_string(playerSelected->getMaxHealth()));
        healthBarRect.setScale(1*((float)playerSelected->getHealth()/(float)playerSelected->getMaxHealth()),1);
    }else if(monsterSelected != nullptr){
        healthText.setString(std::to_string(monsterSelected->health) + "/" + std::to_string(monsterSelected->maxHealth));
        healthBarRect.setScale(1*((float)monsterSelected->health/(float)monsterSelected->maxHealth),1);
    }
    sf::FloatRect textRect = healthText.getLocalBounds();
    healthText.setOrigin(textRect.left + textRect.width/2.0f,
                         textRect.top  + textRect.height/2.0f);
    healthText.setPosition(healthBarRect.getPosition().x+(healthBarRect.getSize().x*0.5f),healthBarRect.getPosition().y+(healthBarRect.getSize().y*0.5f));
    sf::FloatRect textRect2 = manaText.getLocalBounds();
    manaText.setOrigin(textRect2.left + textRect2.width/2.0f,
                       textRect2.top  + textRect2.height/2.0f);
    manaText.setPosition(healthBarRect.getPosition().x+(healthBarRect.getSize().x*0.5f),manaBarRect.getPosition().y+(manaBarRect.getSize().y*0.5f));
}

void HUD::setTowerSelected(Tower* tower){
    towerSelected = tower;
}

void HUD::setPlayerSelected(Player* player){
    playerSelected = player;
}
void HUD::setMonsterSelected(Monster* monster){
    monsterSelected = monster;
}

void HUD::handleSelection(std::string &towerSelected,Player* player,tgui::Gui &gui, Settings &json){
    if(towerSelected.empty() && !player->checkIsSelected()) {
        tgui::Theme::Ptr theme = tgui::Theme::create("Texture/widgets/Black.txt");
        tgui::Panel::Ptr selectionPicturePanel = gui.get<tgui::Panel>("selectionPicturePanel", true);
        tgui::Panel::Ptr selectionInfoPanel = gui.get<tgui::Panel>("selectionInfoPanel", true);
        selectionPicturePanel->removeAllWidgets();
        selectionInfoPanel->removeAllWidgets();

        tgui::Picture::Ptr frame = tgui::Picture::create(json.texture["miniMapFrame"], false);

        tgui::Texture tex(json.texture["player"], sf::IntRect(32, 0, 32, 32), sf::IntRect());

        tgui::Picture::Ptr towerPic = tgui::Picture::create(tex, false);
        // std::cout << towersPlaced[i].towerType << std::endl;
        towerPic->setSize(selectionPicturePanel->getSize().x * 0.8f, selectionPicturePanel->getSize().x * 0.8f);
        towerPic->setPosition(selectionPicturePanel->getSize().x * 0.1f, selectionPicturePanel->getSize().x * 0.1f);
        towerPic->moveToFront();
        frame->setSize(towerPic->getSize());
        frame->setPosition(towerPic->getPosition());

        selectionPicturePanel->add(towerPic);
        selectionPicturePanel->add(frame);

        tgui::Label::Ptr label = theme->load("Label");
        label->setText(player->getPlayerClass().getClassName());
        label->setTextSize(24);
        label->setPosition(tgui::bindWidth(selectionInfoPanel)*0.5f - tgui::bindWidth(label)*0.5f,tgui::bindHeight(selectionInfoPanel)*0.1f);
        selectionInfoPanel->add(label);
        label->moveToFront();

        player->setSelected(true);
    }
}

void HUD::updateGameTimer(Timer &gameTimer){
    float time;
    time = gameTimer.GetElapsedSeconds();

    seconds = (int)time;
    minutes = seconds / 60;

    if((seconds%60) < 10){
        secondsString = "0" + std::to_string(seconds%60);
    }else{
        secondsString = std::to_string(seconds%60);
    }
    if(minutes < 10){
        minutesString = "0" + std::to_string(minutes%60);
    }else{
        minutesString = std::to_string(minutes%60);
    }
    gameTime->setText(sf::String::fromUtf8(minutesString.begin(),minutesString.end()) + ":" + sf::String::fromUtf8(secondsString.begin(),secondsString.end()));
}

void HUD::updatePlayerGold(int playerGold){
    gold->setText(std::to_string(playerGold));
}

void HUD::checkTowerAvailable(int playerGold){
    std::map<std::string,std::pair<int,tgui::Picture::Ptr>> it;
    for(auto const& x : towerGrid){
        std::pair<int, tgui::Picture::Ptr> val = x.second;
        if(playerGold < val.first){
            val.second->setOpacity(0.5);
            val.second->disable(true);
        }else if(playerGold >= val.first){
            val.second->setOpacity(1);
            val.second->enable();
        }
    }
}

void HUD::checkWidget(int &x, int &y){
    /*for (auto &element : elements) {
        if(x >= element->getAbsolutePosition().x &&
                x <= element->getAbsolutePosition().x + element->getSize().x &&
                y >= element->getAbsolutePosition().y &&
                y <= element->getAbsolutePosition().y + element->getSize().y){


        }
    }*/
}




