//
// Created by Masaya on 11/7/2017.
//

#ifndef PROCY_BULLET_H
#define PROCY_BULLET_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../../GUI/Sound/Sound.h"

class Bullet{
private:
    sf::Vector2f m_Position;
    sf::Sprite m_BulletShape;
    bool m_InFlight = false;
    float m_BulletSpeed;
    float m_BulletDistanceX;
    float m_BulletDistanceY;
    float m_MaxX;
    float m_MinX;
    float m_MaxY;
    float m_MinY;
    int m_BulletRange;
public:
    Bullet();
    void stop();
    bool isInFlight();
    void shoot(float startX, float startY, float xTarget, float yTarget);
    sf::Vector2f getPosition();
    sf::Sprite getSprite();
    void setSprite(sf::Texture &tex, float scaleX, float scaleY);\
    void update(float elapsedTime, float xTarget, float yTarget);
    void setBulletSpeed(float value);
    void setBulletRange(int value);
    float getBulletSpeed();
    int getBulletRange();
};

#endif //PROCY_BULLET_H
