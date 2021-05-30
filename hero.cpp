#include "hero.h"

#include <iostream>

Hero::Hero(const sf::Vector2f &position, sf::Texture &texture, sf::Vector2i textureLayout, sf::Vector2i textureSize)
{
    loadTexture(position, texture, textureLayout, textureSize);
}

void Hero::setSpeed(float speed)
{
    speedForward_ = speed;
    speedBackward_ = -speed;
}

void Hero::setSpeedUp(float speedUp)
{
    speedUp_ = speedUp;
}

void Hero::setHealth(float health)
{
    health_ = health;
}

float Hero::getArmor()
{
    return armor_;
}

void Hero::setArmor(float armor)
{
    armor_ = armor;
}

float Hero::getHealth()
{
    return health_;
}

void Hero::control()
{
    if (move_forward == true)
    {
        if (speedForward_ < maxSpeed_)
        {
            move((speedForward_ += acceleration_) * elapsed_, 0);
        }
        else
        {
            move(maxSpeed_ * elapsed_, 0);
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
        if (speedBackward_ > -maxSpeed_)
        {
            move((speedBackward_ -= acceleration_) * elapsed_, 0);
        }
        else
        {
            move(-maxSpeed_ * elapsed_, 0);
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

    if (!move_forward && !move_backward && frame_ >= 5 && oriented_right)
    {
        frame_ = 0;
    }

    if (!move_forward && !move_backward && frame_ >= 12 && !oriented_right)
    {
        frame_ = 7;
    }
}

void Hero::isColliding(std::vector<sf::RectangleShape> obstacles)
{
    bool colision = false;

    for(auto &it : obstacles)
    {
        if(getPosition().x + getGlobalBounds().width >= it.getPosition().x &&
                getPosition().x + getGlobalBounds().width <= it.getPosition().x + it.getGlobalBounds().width &&
                it.getGlobalBounds().intersects(getGlobalBounds()) &&
                getPosition().y + getGlobalBounds().height > it.getGlobalBounds().top + 20)
        {
            move_forward = false;
            colision = true;
            setSpeed(0);
        }
        if(getPosition().x <= it.getPosition().x + it.getGlobalBounds().width &&
                getPosition().x >= it.getPosition().x &&
                it.getGlobalBounds().intersects(getGlobalBounds()) &&
                getPosition().y + getGlobalBounds().height > it.getGlobalBounds().top + 15)
        {
            move_backward = false;
            colision = true;
            setSpeed(0);
        }
//        if (move_up == true)
//        {
//            move(0, speedUp_ * 0.01);
//            move_up = false;
//        }
        if(getPosition().y <= it.getPosition().y + it.getGlobalBounds().height &&
                getPosition().y >= it.getPosition().y  &&
                getPosition().y + getGlobalBounds().height >= it.getPosition().y + it.getGlobalBounds().height &&
                getPosition().x + getGlobalBounds().width >= it.getPosition().x + 5 &&
                getPosition().x <= it.getPosition().x + it.getGlobalBounds().width - 5 &&
                getPosition().y + getGlobalBounds().height > it.getPosition().y &&
                speedUp_ <= 0)
        {
            speedUp_ = 50;
        }
        if(colision)
        {
            return;
        }
    }
}

void Hero::gravity(std::vector<sf::RectangleShape> obstacles)
{
    if(!using_ladder)
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
                move(0 * elapsed_, (speedUp_ += gravity_) * elapsed_);
            }
            else
            {
                move(0 * elapsed_, maxSpeed_ * elapsed_);
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
}

void Hero::hit(std::vector<BulletEnemy *> BulletVector_enemy)
{
    for (auto &it : BulletVector_enemy)
    {
        if (getGlobalBounds().intersects(it->getGlobalBoungs()))
        {
            it->setPosition(sf::Vector2f(1000000, 1000000));
            if (armor_ > 0)
            {
                armor_ -= 2;
            }
            else
            {
                health_ -= 2;
            }
            std::cout<<health_<<std::endl;
            break;
        }
    }
}



























