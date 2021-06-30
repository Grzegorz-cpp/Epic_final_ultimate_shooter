#pragma once

#include "animated.h"
#include "bullet.h"
#include "gun.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Enemy : public Animated
{
public:
    Enemy(sf::Vector2f position, sf::Texture &texture, sf::Vector2i textureLayout, sf::Vector2i textureSize, bool is_walking, bool orientated_right,
          float speed, float health, int gunType, float detectedDistanceX, float detectedDistanceY, std::vector<sf::Sprite> obstacles);

    void standby(sf::Vector2f heroPosition, int colisionType);
    void atack(sf::Vector2f heroPosition, int colisionType);
    void control();
    void gravity(std::vector<sf::Sprite> obstacles);
    int isColliding(std::vector<sf::Sprite> obstacles);
    bool hit(std::vector<Bullet*> &BulletVector, Gun* gun, float damageMultipler);
    bool getOrientation();
    float getMaxSpeed();
    float getHealth();

    bool clear_shoot = false;

protected:
    bool is_walking_;
    bool orientated_right_;
    bool move_forward = false;
    bool move_backward = false;
    bool move_flag = true;
    bool detected = false;
    bool move_up = false;
    bool is_on_floor_ = false;
    float maxSpeed_ = 200;
    float maxSpeedDown_ = 600;
    float acceleration_ = 10;
    float speedUp_ = 0;
    float gravity_ = 30;
    float health_ = 100;
    float detectedDistanceX_ = 0;
    float detectedDistanceY_ = 0;
    float speedForward_= 30;
    float speedBackward_ = -30;
    float maxSpeedForward_;
    float maxSpeedBackward_;
    float jumpHight_ = 75;
    int floorOffset_ = 0;
    std::vector<sf::Sprite> obstacles_;
};
