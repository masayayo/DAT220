//
// Created by Chrim14 on 06.10.2017.
//

#include "Game.h"

Game::Game() {

    //Setting up logging
    plog::RollingFileAppender<plog::TxtFormatter> fileAppender("Debugger/dLog.log", 0, 0);
    plog::RollingFileAppender<plog::TxtFormatter> fileAppender2("Debugger/iLog.log", 0, 0);
    plog::init<1>(plog::debug, &fileAppender);
    plog::init<2>(plog::info, &fileAppender2);
    //Creating object needed
    StateMachine stateMachine;
    Settings json;
    Sound sound;
    MapEvents mapEvents;
    HUD hud;
    Paths paths;
    WaveManager waveManager(json, paths);

    bool hudLoaded = false;
    std::vector<tgui::Panel::Ptr> panels;
    Timer gameTimer;
    std::string towerSelected;
    bool placedTowerSelected = false;
    std::vector<Tower> towersPlaced;
    bool playersSpawned = false;

    srand (time(NULL)); //Setting up random value for path finding;

    stateMachine.StartStateStack();

    sf::RenderWindow window;
    tgui::Gui gui(window);
    SettingButtons::setSettings(window,gui,json,sound);

    stateMachine.NextState(List_State::Main_Menu);
    stateMachine.updateInterface(gameTimer,gui,window, stateMachine, json, sound, waveManager);

    sound.StartMenuMusic();

    lInfo("Window opened");

    sf::VertexArray mapTiles(sf::Quads, 0);
    sf::VertexArray miniMapSquare(sf::LineStrip, 5);
    sf::VertexArray bitTiles(sf::Quads, 0);

    //Creating views
    json.setViews(window);

    Player player1;

    // Shader test
    sf::Shader shader;
    if(!shader.loadFromFile("Texture/Shaders/main.vert","Texture/Shaders/main.frag")){
        std::cout << "Could not load shaders" << std::endl;
    }

    Updater updater;

    shader.setUniform("textureOffset", 1.0f / static_cast<float>(json.texture["tower_1"].getSize().x));
    shader.setUniform("color",sf::Glsl::Vec4(255,255,0.0,255));
    shader.setUniform("texture", sf::Shader::CurrentTexture);

    //Time stuff
    sf::Clock clock;
    sf::Clock fpsCounter;
    sf::Clock nextFrame;

    sf::Text fps;
    sf::Font font;
    if (!font.loadFromFile("Texture/Texture/system/sansation.ttf")){};
    fps.setFont(font);
    fps.setCharacterSize(30);
    fps.setPosition(50,50);
    fps.setFillColor(sf::Color::Yellow);

    double t = 0.0;
    const double dt = 0.01;
    float currentTime = clock.getElapsedTime().asSeconds();
    double accumulator = 0.0;
    float lastTime = 0;
    window.setFramerateLimit(0);
    window.setKeyRepeatEnabled(false);

    while (window.isOpen() && !stateMachine.isEmpty()){

        window.clear();

        //Time stuff
        float newTime = clock.getElapsedTime().asSeconds();
        float frameTime = newTime - currentTime;
        if ( frameTime > 0.25 ) frameTime = 0.25;
        currentTime = newTime;
        accumulator += frameTime;

        if(!playersSpawned && !json.newGamePlayers.empty()){
            for(auto &it : json.newGamePlayers){
                player1.postDefinePlayer(json.playerClasses[it.second],json);
                player1.spawnPlayer(200,200);
            }
            playersSpawned = true;
        }

        while ( accumulator >= dt) {

            t += dt;
            accumulator -= dt;

            mapEvents.clickEvent(player1,waveManager,hud,placedTowerSelected,towersPlaced,towerSelected,panels,mapTiles, bitTiles, json.event, stateMachine, json, window,gui);

            mapEvents.moveView(false, window, stateMachine, json, panels, gui);
            if(stateMachine.getState() == List_State::Game) {
                updater.updateMonsters(player1,gameTimer,shader,window,waveManager,stateMachine,json,paths,sound);
                updater.updateTowers(waveManager,player1,gameTimer,frameTime,towersPlaced,window,json,sound);
                updater.updatePlayers(player1,gameTimer,frameTime,towersPlaced,window,json,sound);
                if(hudLoaded){
                    hud.handleHealthBar(gui,json);
                }
            }

                while (window.pollEvent(json.event)) {
                    mapEvents.clickReleaseEvent(panels, mapTiles, bitTiles, json.event, stateMachine, json, window, gui);

                    gui.handleEvent(json.event);

                mapEvents.eventHandler(panels, gameTimer, window, json.event, stateMachine, json, gui, sound, waveManager);

                    if (json.event.type == sf::Event::Closed) {
                        window.close();
                    }
                }

            if(json.showFPS && nextFrame.getElapsedTime().asSeconds() > 0.7f) {
                float fpsTime = 1.f / (currentTime - lastTime);
                nextFrame.restart();
                fps.setString("FPS: " + std::to_string((int) fpsTime));
            }
        }


        mapEvents.mapHandler(shader,player1,gameTimer,towersPlaced,towerSelected,mapTiles,bitTiles,stateMachine,window,json, miniMapSquare,gui,sound, paths, waveManager);

        if(stateMachine.getState() == List_State::Game) {
            updater.drawMonsters(waveManager, window,shader);
            updater.drawTowers(gameTimer,shader,towerSelected,towersPlaced,player1,window,json);
            updater.drawPlayers(player1,shader,window);

            if(!placedTowerSelected && hudLoaded){
                hud.handleSelection(towerSelected,&player1,gui,json);
            }
        }

        hud.hudHandler(towerSelected,gameTimer,hudLoaded,panels,gui,stateMachine,window,json,sound,json.view["hudView"]);

        if(json.mapLoaded && stateMachine.getState() == List_State::Game){
            if(hudLoaded && json.mapLoaded) {
                hud.updatePlayerGold(player1.getGold());
                hud.checkTowerAvailable(player1.getGold());
            }
            mapEvents.getMiniMapView(gui,window,json,mapTiles,miniMapSquare);
        }

        window.setView(json.view["fixed"]);
        if(json.showFPS){
        lastTime = currentTime;
        window.draw(fps);};

        json.sprite["pointer"].setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        window.draw(json.sprite["pointer"]);


        window.setView(json.view["main"]);
        window.display();
    }
    lInfo("Window closed");
}