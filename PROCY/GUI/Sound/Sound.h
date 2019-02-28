//
// Created by Admin on 08.10.2017.
//

#ifndef PROCY_MUSIC_H
#define PROCY_MUSIC_H

#include <SFML/Audio.hpp>
#include "../../Debugger/Logging.h"

class Sound {
public:
    Sound() = default;

    void StartMenuMusic();

    void StartGameMusic_1();

    void StartPauseMusic();

    void setMusicVolum(int volum);

    void setSoundVolum(int volum);

    void setSystemVolum(int volum);

    void SoundClick();

    void SoundClickBack();

    void getClickStart();

    void getWaveStarted();

    void restoreLastMusic();

    void towerShoot(std::string &soundName);

    void setSound(bool muted, int music,int sound,int system);

private:
    sf::Music music;
    sf::Sound sound;
    sf::Sound system;
    sf::SoundBuffer buffer;
    std::string storedFile;
    sf::Time storedTime;
};


#endif //PROCY_MUSIC_H
