#pragma once

#include "animated.h"
#include "bullet.h"
#include "gun.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Enemy : public Animated
{
public:
    Enemy(const sf::Vector2f &position, sf::Texture &texture, sf::Vector2i textureLayout, sf::Vector2i textureSize, bool is_walking, bool orientated_right,
          float speed, float health, int gunType, float detectedDistanceX, float detectedDistanceY, std::vector<sf::Sprite> obstacles);
    void standby(sf::Vector2f heroPosition, int colisionType);
    void atack(sf::Vector2f heroPosition, int colisionType);
    bool hit(std::vector<Bullet*> &BulletVector, Gun* gun);
    void control();
    int isColliding(std::vector<sf::Sprite> obstacles);
    void gravity(std::vector<sf::Sprite> obstacles);
    bool getOrientation();

    bool clear_shoot = false;
    int x = 0;

protected:
    bool is_walking_;
    bool orientated_right_;
    bool move_forward = false;
    bool move_backward = false;
    bool move_flag = true;
    std::vector<sf::Sprite> obstacles_;
    float maxSpeed_ = 200;
    float acceleration_ = 10;
    float speedUp_ = 0;
    int floorOffset_ = 0;
    float gravity_ = 10;
    bool move_up = false;
    bool is_on_floor_ = false;
    float health_ = 100;
    bool detected = false;
    float detectedDistanceX_ = 0;
    float detectedDistanceY_ = 0;
    float speedForward_= 30;
    float speedBackward_ = -30;
};
