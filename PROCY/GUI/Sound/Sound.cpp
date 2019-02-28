//
// Created by Admin on 08.10.2017.
//

#include "Sound.h"


void Sound::StartMenuMusic() {
    if(!music.openFromFile("Texture/Sound/Music/menu-music.ogg")){
        lError("Music for menu could not open");
        return;
    }
    lDebug("Playing menu music one");
    storedFile = "menu-music.ogg";
    music.play();
    music.setLoop(true);
}

void Sound::StartGameMusic_1() {
    if(!music.openFromFile("Texture/Sound/Music/game-music1.ogg")){
        lError("Music for menu could not open");
        return;
    }
    lDebug("Playing game music one");
    storedFile = "game-music1.ogg";
    music.play();
    music.setLoop(true);
}

void Sound::SoundClick() {
    if(!buffer.loadFromFile("Texture/Sound/Sound/click.ogg")){
        lError("click sound could not open");
        return;
    }
    system.setBuffer(buffer);
    system.play();
}

void Sound::SoundClickBack() {
    if(!buffer.loadFromFile("Texture/Sound/Sound/back.ogg")){
        lError("click back sound could not open");
        return;
    }
    system.setBuffer(buffer);
    system.play();
}

void Sound::setMusicVolum(int volum) {
    music.setVolume(volum);
}

void Sound::setSoundVolum(int volum) {
    sound.setVolume(volum);
}

void Sound::setSystemVolum(int volum) {
    system.setVolume(volum);
}


void Sound::getClickStart() {
    if(!buffer.loadFromFile("Texture/Sound/Sound/start.ogg")){
        lError("click start sound could not open");
        return;
    }
    system.setBuffer(buffer);
    system.play();
}

void Sound::StartPauseMusic() {
    storedTime = music.getPlayingOffset(); //Storing game music position
    if(!music.openFromFile("Texture/Sound/Music/pause-music.wav")){
        lError("Music for pause could not open");
        return;
    }
    lDebug("Playing pause music");
    music.play();
    music.setLoop(true);

}

void Sound::restoreLastMusic() {
    try{
        if(!music.openFromFile("Texture/Sound/Music/"+storedFile)){
            lError("Music stored could not open");
            return;
        }
        music.play();
        music.setPlayingOffset(storedTime);
        music.setLoop(true);

    }catch (...){
        lError("Tried to restore music, but failed");
    }
}

void Sound::towerShoot(std::string &soundName){
    if(!buffer.loadFromFile("Texture/Sound/Sound/"+soundName+".wav")){
        lError("click back sound could not open");
        return;
    }
    sound.setBuffer(buffer);
    sound.play();
}

void Sound::setSound(bool muted, int music, int sound, int system) {
    if(muted){
        setMusicVolum(0);
        setSoundVolum(0);
        setSystemVolum(0);
    }
    else{
        setMusicVolum(music);
        setSoundVolum(sound);
        setSystemVolum(system);
    }
}

void Sound::getWaveStarted() {
    if(!buffer.loadFromFile("Texture/Sound/Sound/Bells.ogg")){
        lError("Bell back sound could not open");
        return;
    }
    sound.setBuffer(buffer);
    sound.play();
}


