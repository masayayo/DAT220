//
// Created by Masaya on 11/7/2017.
//

#include "Bullet.h"
#include <math.h>

Bullet::Bullet() = default;

void Bullet::shoot(float startX, float startY, float targetX, float targetY){
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;

    m_MinX = startX - m_BulletRange;
    m_MaxX = startX + m_BulletRange;
    m_MinY = startY - m_BulletRange;
    m_MaxY = startY + m_BulletRange;

    m_BulletDistanceX = targetX - startX;
    m_BulletDistanceY = targetY - startY;

    double angle = (atan2((m_Position.y+m_BulletShape.getOrigin().y)-
                          targetX,(m_Position.x+m_BulletShape.getOrigin().x)-
                                  targetY)) * 180 / M_PI;
    m_BulletShape.setRotation((float)angle+180);

    m_BulletShape.setPosition(m_Position);
}

void Bullet::stop(){
    m_InFlight = false;
}

bool Bullet::isInFlight() {
    return m_InFlight;
}

sf::Vector2f Bullet::getPosition() {
    return m_Position;
}

sf::Sprite Bullet::getSprite() {
    return m_BulletShape;
}

void Bullet::setSprite(sf::Texture &tex, float scaleX, float scaleY){
    m_BulletShape.setTexture(tex);
    m_BulletShape.setScale(scaleX,scaleY);
    m_BulletShape.setOrigin(m_BulletShape.getLocalBounds().left+m_BulletShape.getLocalBounds().width/2,m_BulletShape.getLocalBounds().top+m_BulletShape.getLocalBounds().height/2);
}

void Bullet::setBulletSpeed(float value){
    m_BulletSpeed = value;
}
void Bullet::setBulletRange(int value){
    m_BulletRange = value;
}
float Bullet::getBulletSpeed(){
    return m_BulletSpeed;
}
int Bullet::getBulletRange(){
    return m_BulletRange;
}

void Bullet::update(float elapsedTime, float xTarget, float yTarget)
{
    float distance = sqrt((xTarget-m_Position.x)*(xTarget-m_Position.x)+(yTarget-m_Position.y)*(yTarget-m_Position.y));

    m_BulletDistanceX = m_BulletSpeed*(xTarget-m_Position.x)/distance;
    m_BulletDistanceY = m_BulletSpeed*(yTarget-m_Position.y)/distance;
    m_Position.x += m_BulletDistanceX;
    m_Position.y += m_BulletDistanceY;


    double angle = (atan2((m_Position.y+m_BulletShape.getOrigin().y)-
                          yTarget,(m_Position.x+m_BulletShape.getOrigin().x)-
                                         xTarget)) * 180 / M_PI;
    m_BulletShape.setRotation((float)angle+270);

    m_BulletShape.setPosition(m_Position);

    if(m_Position.x < m_MinX || m_Position.x > m_MaxX ||
            m_Position.y < m_MinY || m_Position.y > m_MaxY){
        m_InFlight = false;
    }
}