#include "enemy.h"

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

#include <iostream>

Enemy::Enemy(const sf::Vector2f &position, sf::Texture &texture, sf::Vector2i textureLayout, sf::Vector2i textureSize, bool is_walking, bool orientated_right,
             float speed, float health, int gunType, float detectedDistanceX, float detectedDistanceY, std::vector<sf::Sprite> obstacles)
{
    loadTexture(position, texture, textureLayout, textureSize);
    is_walking_ = is_walking;
    speedBackward_ = speed;
    speedForward_ = -speed;
    health_ = health;
    gunType_ = gunType;
    obstacles_ = obstacles;
    orientated_right_ = orientated_right;
    detectedDistanceX_ = detectedDistanceX;
    detectedDistanceY_ = detectedDistanceY;
}

void Enemy::standby(sf::Vector2f heroPosition, int colisionType)
{
    if (detected)
    {
        atack(heroPosition, colisionType);
        return;
    }
    if ((std::abs(heroPosition.x - getPosition().x) > 10000 ||
            std::abs(heroPosition.y - getPosition().y) > 10000) &&
            detected)
    {
        detected = false;
    }
    if (!is_walking_)
    {
        if (std::abs(heroPosition.x - this -> getPosition().x) < detectedDistanceX_ &&
                std::abs(heroPosition.y - this -> getPosition().y) < detectedDistanceY_)
        {
            if ((orientated_right_ && heroPosition.x > getPosition().x) ||
                    (!orientated_right_ && heroPosition.x < getPosition().x))
            {
                atack(heroPosition, colisionType);
                detected = true;
                return;
            }
        }
    }
    if (is_walking_)
    {
        if (std::abs(heroPosition.x - this -> getPosition().x) < detectedDistanceX_ &&
                std::abs(heroPosition.y - this -> getPosition().y) < detectedDistanceY_)
        {
            if ((orientated_right_ && heroPosition.x > getPosition().x) ||
                    (!orientated_right_ && heroPosition.x < getPosition().x))
            {
                atack(heroPosition, colisionType);
                detected = true;
                return;
            }
        }
        if (colisionType == 0 && move_flag)
        {
            move_backward = true;
            move_flag = false;
        }
        if (colisionType == 1 || colisionType == 2)
        {
            move_backward = true;
        }
        if (colisionType == 2 || colisionType == 4)
        {
            move_forward = true;
        }
        for (auto &it : obstacles_)
        {
            if (getGlobalBounds().left < it.getGlobalBounds().left &&
                    getGlobalBounds().left + getGlobalBounds().width > it.getGlobalBounds().left &&
                    getGlobalBounds().top + getGlobalBounds().height >= it.getGlobalBounds().top - 10 &&
                    getGlobalBounds().top + getGlobalBounds().height <= it.getGlobalBounds().top + 10)
            {
                move_backward = false;
                move_forward = true;
                return;
            }
            else if (getGlobalBounds().left < it.getGlobalBounds().left + it.getGlobalBounds().width &&
                    getGlobalBounds().left + getGlobalBounds().width > it.getGlobalBounds().left + it.getGlobalBounds().width &&
                    getGlobalBounds().top + getGlobalBounds().height >= it.getGlobalBounds().top - 10 &&
                    getGlobalBounds().top + getGlobalBounds().height <= it.getGlobalBounds().top + 10)
            {
                move_backward = true;
                move_forward = false;
                return;
            }
        }
    }
}

void Enemy::atack(sf::Vector2f heroPosition, int colisionType)
{
    if (std::abs(heroPosition.x - this -> getPosition().x) < 500 &&
            std::abs(heroPosition.y - this -> getPosition().y) < 600)
    {
        move_forward = false;
        move_backward = false;
    }
    else if (getPosition().x < heroPosition.x)
    {
        move_forward = true;
        move_backward = false;
    }
    else if (getPosition().x > heroPosition.x)
    {
        move_forward = false;
        move_backward = true;
    }

    if (heroPosition.x > getPosition().x && !move_backward && !move_forward)
    {
        orientated_right_ = true;
        frame_ = 0;
    }
    else if (heroPosition.x < getPosition().x && !move_backward && !move_forward)
    {
        orientated_right_ = false;
        frame_ = 7;
    }

    if (colisionType == 2 && is_on_floor_ && orientated_right_)
    {
        move_up = true;
        is_on_floor_ = false;
        speedUp_ = -400;
    }
    if (colisionType == 4 && is_on_floor_ && !orientated_right_)
    {
        move_up = true;
        is_on_floor_ = false;
        speedUp_ = -400;
    }

    sf::RectangleShape fireLine(sf::Vector2f(5, 5));
    fireLine.setPosition(getPosition().x, getPosition().y);
    fireLine.setFillColor(sf::Color::Red);

    float fireLineX = std::abs(heroPosition.x - getPosition().x) / (std::abs(heroPosition.x - getPosition().x) + std::abs(heroPosition.y - getPosition().y));
    float fireLineY = std::abs(heroPosition.y - getPosition().y) / (std::abs(heroPosition.x - getPosition().x) + std::abs(heroPosition.y - getPosition().y));

    if (heroPosition.x < getPosition().x)
    {
        fireLineX = -fireLineX;
    }
    if (heroPosition.y < getPosition().y)
    {
        fireLineY = -fireLineY;
    }

    clear_shoot = true;

    //fireLine.move(fireLineX * 50, fireLineY * 50);

    for (auto i = 0; i < sqrt(std::abs(heroPosition.x - getPosition().x) * std::abs(heroPosition.x - getPosition().x) + std::abs(heroPosition.y - getPosition().y) * std::abs(heroPosition.y - getPosition().y)); i++)
    {
        fireLine.move(fireLineX, fireLineY);
        for (auto &it : obstacles_)
        {
            if (it.getGlobalBounds().intersects(fireLine.getGlobalBounds()))
            {
                clear_shoot = false;
                break;
            }
        }
    }
}

bool Enemy::hit(std::vector<Bullet*> &BulletVector, Gun* gun)
{
    for (auto &it : BulletVector)
    {
        if (getGlobalBounds().intersects(it->getGlobalBounds()))
        {
            std::cout << x << std::endl;
            x++;
            it->setPosition(sf::Vector2f(1000000, 1000000));
            health_ -= gun->getDamage();
            detected = true;
            break;
        }
    }
    if (health_ <= 0)
    {
        detected = false;

        return true;
    }
    else
    {
        return false;
    }
}


void Enemy::control()
{
    if (move_forward == true)
    {
        orientated_right_ = true;
        if (speedForward_ < maxSpeed_)
        {
            move((speedForward_ += acceleration_) * 0.01666, 0);
        }
        else
        {
            move(maxSpeed_ * 0.01666, 0);
        }

        frequency_--;

        if (frequency_ == 0)
        {
            frame_++;
            frequency_ = 5;
        }

        if (frame_ >= 21 || frame_ < 14)
        {
            frame_ = 14;
        }
    }

    if (move_backward == true)
    {
        orientated_right_ = false;
        if (speedBackward_ > -maxSpeed_)
        {
            move((speedBackward_ -= acceleration_) * 0.01666, 0);
        }
        else
        {
            move(-maxSpeed_ * 0.01666, 0);
        }

        frequency_--;

        if (frequency_ == 0)
        {
            frame_++;
            frequency_ = 5;
        }

        if (frame_ >= 28 || frame_ < 21)
        {
            frame_ = 21;
        }
    }

    if (!move_forward && !move_backward)
    {
        frequency_--;
    }

    if (!move_forward && !move_backward && frequency_ == 0)
    {
        frame_ ++;
        frequency_ = 11;
    }

    if (!move_forward && !move_backward && frame_ >= 5 && orientated_right_)
    {
        frame_ = 0;
    }

    if (!move_forward && !move_backward && frame_ >= 12 && !orientated_right_)
    {
        frame_ = 7;
    }

    if (move_up)
    {
        move(0, speedUp_ * 0.1);
    }
}

int Enemy::isColliding(std::vector<sf::Sprite> obstacles)
{
    int colisionType = 0;

    for(auto &it : obstacles)
    {
        if(getPosition().x + getGlobalBounds().width >= it.getPosition().x &&
                getPosition().x + getGlobalBounds().width <= it.getPosition().x + it.getGlobalBounds().width &&
                it.getGlobalBounds().intersects(getGlobalBounds()) &&
                getPosition().y + getGlobalBounds().height > it.getGlobalBounds().top + 20)
        {
            move_forward = false;
            if(getGlobalBounds().top <= it.getGlobalBounds().top)
            {
                colisionType = 3;
            }
            else
            {
                colisionType = 1;
            }
            speedForward_ = 0;
        }
        if(getPosition().x <= it.getPosition().x + it.getGlobalBounds().width &&
                getPosition().x >= it.getPosition().x &&
                it.getGlobalBounds().intersects(getGlobalBounds()) &&
                getPosition().y + getGlobalBounds().height > it.getGlobalBounds().top + 15)
        {
            move_backward = false;
            if(getGlobalBounds().top <= it.getGlobalBounds().top)
            {
                colisionType = 4;
            }
            else
            {
                colisionType = 2;
            }
            speedForward_ = 0;
            speedBackward_ = 0;
        }

        if(getPosition().y <= it.getPosition().y + it.getGlobalBounds().height &&
                getPosition().y >= it.getPosition().y  &&
                getPosition().y + getGlobalBounds().height >= it.getPosition().y + it.getGlobalBounds().height &&
                getPosition().x + getGlobalBounds().width >= it.getPosition().x &&
                getPosition().x <= it.getPosition().x + it.getGlobalBounds().width &&
                getPosition().y + getGlobalBounds().height > it.getPosition().y &&
                speedUp_ <= 0)
        {
            speedUp_ = 50;
        }
        if(colisionType > 0)
        {
            return colisionType;
        }
    }

    return colisionType;
}

void Enemy::gravity(std::vector<sf::Sprite> obstacles)
{
    bool gravity_flag = true;

    for(auto &it : obstacles)
    {
        if (move_up == true)
        {
            move(0, speedUp_ * 0.01);
            move_up = false;
        }
        if(getGlobalBounds().top + getGlobalBounds().height < it.getGlobalBounds().top + floorOffset_ &&
                getPosition().x + getGlobalBounds().width >= it.getPosition().x + 10 &&
                getPosition().x <= it.getPosition().x + it.getGlobalBounds().width - 10 &&
                gravity_flag)
        {
            if (speedUp_ < maxSpeed_)
            {
                this -> move(0 * elapsed_, (speedUp_ += gravity_) * 0.01666);
            }
            else
            {
                this -> move(0 * elapsed_, maxSpeed_ * 0.01666);
            }
            is_on_floor_ = false;
            gravity_flag = false;
        }
        else if (getGlobalBounds().top + getGlobalBounds().height >= it.getGlobalBounds().top + floorOffset_ &&
                 getPosition().x + getGlobalBounds().width >= it.getPosition().x + 10 &&
                 getPosition().x <= it.getPosition().x + it.getGlobalBounds().width - 10 &&
                 getPosition().y < it.getPosition().y)
        {
            setPosition(getPosition().x, it.getGlobalBounds().top - getGlobalBounds().height + floorOffset_);
            speedUp_ = 0;
            is_on_floor_ = true;
        }
    }
}

bool Enemy::getOrientation()
{
    return orientated_right_;
}
























