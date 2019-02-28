#ifndef PROCY_MONSTER_H
#define PROCY_MONSTER_H

#include <list>
#include "SFML/Graphics.hpp"
#include "../../Engine/Settings.h"
#include "../Pathfinder/Paths.h"
#include "../Game/Player.h"

class Monster {
public:
    Monster(sf::Vector2i spawn, Settings &json, Paths& paths, MonsterClass &monsterType);

    sf::Sprite sprite;
    sf::IntRect spriteRect;
    float textureUpdateTimer = 0;
    sf::RectangleShape healthBar;
    std::vector<int> direction;
    int health;
    int maxHealth;
    int value;
    int damage;
    float speed;
    float direction_left;
    bool visible;
    bool isSelected = false;
    sf::Vector2f currentPosition;
    sf::Texture monsterTexture;
    float teleport_time;
    std::string texturePath;
    MonsterClass monsterType;
    sf::Vector2i spawn;
    int unique_id;

    sf::Sprite getSprite();

    void tick(Player &player,Timer &gameTimer,sf::Shader &shader,sf::RenderWindow &window, Paths& paths);
    void hit(Player &player,int damage, std::list<Monster> &monster_active, int unique_id);

    void addHealth(int amount);
    int getHealth();
    void setHealthBar(sf::Texture &texture);
    sf::RectangleShape getHealthBar();
    bool isPointerOverMonster(sf::Vector2f gamePosition, sf::Sprite &monsterSprite);

    void removeMonster(std::list<Monster> &monster_active, int unique_id);

};


#endif