//
// Created by Masaya on 11/22/2017.
//

#include "Updater.h"
#include "../Map/MapStaticFunctions.h"


void Updater::updateTowers(WaveManager &waveManager,Player &player,Timer &gameTimer,float &frameTime, std::vector<Tower> &towersPlaced, sf::RenderWindow &window, Settings &json, Sound &sound){

    std::list<Monster*> activeMonsters = waveManager.getActiveMonsters();

    for (auto &Tower : towersPlaced) {
        bool isInRadius = false;

        for (auto &activeMonster : activeMonsters) {
            double currentPosition = sqrt(std::pow((double) (activeMonster->currentPosition.x - Tower.tex.getPosition().x), 2) +
                                          std::pow((double) (activeMonster->currentPosition.y - Tower.tex.getPosition().y), 2));

            if (currentPosition < Tower.range) {
                isInRadius = true;
                Tower.enemyTarget = activeMonster;
            }
        }

        if(Tower.enemyTarget != nullptr) {

            if (Tower.towerTimer.GetElapsedSeconds() > Tower.fireRate) {
                if (!gameTimer.bPaused) {
                    if (isInRadius) {

                        Bullet bullet = json.bullet[Tower.bulletType];
                        bullet.shoot(Tower.coordinates.getBounds().left + (Tower.coordinates.getBounds().width / 2),
                                     Tower.coordinates.getBounds().top + (Tower.coordinates.getBounds().width / 2),
                                     Tower.enemyTarget->currentPosition.x, Tower.enemyTarget->currentPosition.y);
                        Tower.bullets.push_back(bullet);
                        sound.towerShoot(Tower.soundName);
                        Tower.towerTimer.Reset();

                        double angle = (atan2((Tower.coordinates.getBounds().top + Tower.tex.getOrigin().y) -
                                              Tower.enemyTarget->currentPosition.y,
                                              (Tower.coordinates.getBounds().left + Tower.tex.getOrigin().x) -
                                              Tower.enemyTarget->currentPosition.x)) * 180 / M_PI;

                        Tower.tex.setRotation((float) angle + 270);
                    }
                }
            }

            for (int i = 0; i < Tower.bullets.size(); i++) {

                if (Tower.bullets[i].isInFlight()) {
                    if (!gameTimer.bPaused) {
                        double hitPos = sqrt(std::pow((double) (Tower.enemyTarget->currentPosition.x - Tower.bullets[i].getPosition().x), 2) +
                                             std::pow((double) (Tower.enemyTarget->currentPosition.y - Tower.bullets[i].getPosition().y), 2));

                        if (hitPos < 10) {
                            Tower.bullets.erase(Tower.bullets.begin() + i);

                            Tower.enemyTarget->hit(player,Tower.damage,waveManager.active_mosters, Tower.enemyTarget->unique_id);
                        }

                        Tower.bullets[i].update(frameTime, Tower.enemyTarget->currentPosition.x, Tower.enemyTarget->currentPosition.y);
                    }
                } else {
                    Tower.bullets.erase(Tower.bullets.begin() + i);
                }
            }
        }
    }
}
void Updater::updatePlayers(Player &player, Timer &gameTimer,float &frameTime, std::vector<Tower> &towersPlaced, sf::RenderWindow &window, Settings &json, Sound &sound){
    if(!gameTimer.bPaused) {
        player.checkBuildingQueue(towersPlaced,frameTime);
        player.updatePlayer();
    }
}
void Updater::updateMonsters(Player &player,Timer &gameTimer,sf::Shader &shader,sf::RenderWindow &window, WaveManager &waveManager, StateMachine &stateMachine, Settings& json, Paths& paths,Sound &sound){
    if(stateMachine.getState() == List_State::Game){
        waveManager.tick(player,gameTimer,shader,window, json, paths,sound);
    }
}
void Updater::drawPlayers(Player &player,sf::Shader &shader,sf::RenderWindow &window){
    sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
    sf::Vector2f gamePosition = window.mapPixelToCoords(pixelPosition);

    if(player.checkIsAlive()){
        if(isPointerOverSprite(gamePosition,player.getSprite())){
            shader.setUniform("color",sf::Glsl::Vec4(255,255,0.0,255));
            window.draw(player.getSprite(),&shader);
            window.draw(player.getProgressBar());
        }else{
            window.draw(player.getSprite());
            window.draw(player.getProgressBar());
        }

    }
}
void Updater::drawTowers(Timer &gameTimer,sf::Shader &shader,std::string &towerSelected, std::vector<Tower> &towersPlaced,Player &player, sf::RenderWindow &window, Settings &json){
    sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
    sf::Vector2f gamePosition = window.mapPixelToCoords(pixelPosition);

    if(!towerSelected.empty()){
        Tower towerPointer;
        sf::RectangleShape towerPointerOutline;
        float sizeX = json.towerSprites[towerSelected].w * (Tile_Size/Bits_To_Tiles);
        float sizeY = json.towerSprites[towerSelected].h * (Tile_Size/Bits_To_Tiles);
        sf::Vector2f bitPixelStartCoordinates = mf::getBitPixelStartCoordinates(gamePosition,json);
        sf::Vector2f position = bitPixelStartCoordinates;

        towerPointer = json.towerSprites[towerSelected];
        towerPointer.tex.setScale(sizeX/towerPointer.tex.getLocalBounds().width,sizeY/towerPointer.tex.getLocalBounds().height);
        towerPointer.tex.setPosition(position);
        towerPointer.tex.setColor(sf::Color(255,255,255,128));
        towerPointerOutline.setSize(sf::Vector2f(towerPointer.tex.getLocalBounds().width*towerPointer.tex.getScale().x,towerPointer.tex.getLocalBounds().height*towerPointer.tex.getScale().y));
        towerPointerOutline.setFillColor(sf::Color::Transparent);
        towerPointerOutline.setOutlineColor(sf::Color::Green);
        towerPointerOutline.setOutlineThickness(1);
        towerPointerOutline.setPosition(towerPointer.tex.getPosition());

        window.draw(towerPointer.tex);
        window.draw(towerPointerOutline);
    }

    if(!player.getBuildingQueue().empty()){
        std::queue<Tower> temp = player.getBuildingQueue();

        for(int i = 0; i < temp.size();i++){
            temp.front().tex.setColor(sf::Color(255,255,255,128));
            window.draw(temp.front().tex);
            temp.pop();
            i--;
        }
    }

    for (auto &Tower : towersPlaced) {

        if (Tower.towerTimer.GetElapsedSeconds() > 0.5) {
            if(!gameTimer.bPaused) {
                if(isPointerOverSprite(gamePosition,Tower.tex) && !Tower.isSelected){
                    shader.setUniform("color",sf::Glsl::Vec4(0.0,255,0.0,255));
                    window.draw(Tower.tex,&shader);
                }else if(Tower.isSelected || (isPointerOverSprite(gamePosition,Tower.tex) && Tower.isSelected)){
                    shader.setUniform("color",sf::Glsl::Vec4(0.0,255,0.0,255));
                    window.draw(Tower.towerRadius);
                    window.draw(Tower.tex,&shader);
                }else{
                    window.draw(Tower.tex);
                }

            }
        } else {
            if(isPointerOverSprite(gamePosition,Tower.tex) && !Tower.isSelected){
                shader.setUniform("color",sf::Glsl::Vec4(0.0,255,0.0,255));
                window.draw(Tower.tex,&shader);
            }else if(Tower.isSelected || (isPointerOverSprite(gamePosition,Tower.tex) && Tower.isSelected)){
                shader.setUniform("color",sf::Glsl::Vec4(0.0,255,0.0,255));
                window.draw(Tower.towerRadius);
                window.draw(Tower.tex,&shader);
            }else{
                window.draw(Tower.tex);
            }
        }
        if(json.setting["bullets"]) {
            for (int i = 0; i < Tower.bullets.size(); i++) {

                if (Tower.bullets[i].isInFlight()) {

                    window.draw(Tower.bullets[i].getSprite());
                }
            }
        }
    }
}
void Updater::drawMonsters(WaveManager &waveManager, sf::RenderWindow &window,sf::Shader &shader){
    sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
    sf::Vector2f gamePosition = window.mapPixelToCoords(pixelPosition);

    std::list<Monster*> activeMonsters = waveManager.getActiveMonsters();

    for (auto &activeMonster : activeMonsters) {
        if (activeMonster->visible && activeMonster->teleport_time <= 0) {

            /* if(isPointerOverSprite(gamePosition,sprite)){
                window.draw(sprite,&shader);
            }else{*/
            //window.draw(activeMonster->sprite);

            //}

            if(isPointerOverSprite(gamePosition,activeMonster->getSprite())){
                shader.setUniform("color",sf::Glsl::Vec4(255,0.0,0.0,255));
                window.draw(activeMonster->getSprite(), &shader);
            }else if(activeMonster->isSelected){
                shader.setUniform("color",sf::Glsl::Vec4(255,0.0,0.0,255));
                window.draw(activeMonster->getSprite(), &shader);
            }else{
                window.draw(activeMonster->getSprite());
            }

            window.draw(activeMonster->healthBar);
        }
    }

}
bool Updater::isPointerOverSprite(sf::Vector2f position, const sf::Sprite &sprite){
    return	(position.x < (sprite.getPosition().x - (sprite.getOrigin().x*sprite.getScale().x))  + ((sprite.getLocalBounds().width)*sprite.getScale().x)) && ((sprite.getPosition().x - (sprite.getOrigin().x*sprite.getScale().x)) < position.x) &&
              (position.y < (sprite.getPosition().y - (sprite.getOrigin().y*sprite.getScale().y)) + ((sprite.getLocalBounds().height)*sprite.getScale().y)) && ((sprite.getPosition().y - (sprite.getOrigin().y*sprite.getScale().y)) < position.y);
}