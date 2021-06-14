#pragma once

#include "animated.h"
#include "bulletenemy.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Hero : public Animated
{
public:
    Hero(const sf::Vector2f &position, sf::Texture &texture, sf::Vector2i textureLayout, sf::Vector2i textureSize);
    void control();
    void setSpeed(float speed);
    void gravity(std::vector<sf::Sprite> obstacles);
    void setSpeedUp(float speedUp);
    void isColliding(std::vector<sf::Sprite> obstacles);
    void shoot();
    void hit(std::vector<BulletEnemy*> BulletVector_enemy, std::vector<float> EnemyBulletDamage);
    float getHealth();
    void setHealth(float health);
    float getArmor();
    void setArmor(float armor);

    bool move_up = false;
    bool is_on_floor_ = false;
    bool move_forward = false;
    bool move_backward = false;
    bool oriented_right = true;
    bool is_shooting = false;
    bool is_climbing_up = false;
    bool is_climbing_down = false;
    bool using_ladder = false;

private:
    float speedForward_= 30;
    float speedBackward_ = -30;
    float maxSpeed_ = 300;
    float acceleration_ = 10;
    float speedUp_ = 0;
    int floorOffset_ = 0;
    float gravity_ = 10;
    float health_ = 100;
    float armor_ = 75;
};

