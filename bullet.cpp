#include "bullet.h"

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

Bullet::Bullet(sf::Vector2f size)
{
    bullet.setSize(size);
}

int Bullet::getRight()
{
    return bullet.getPosition().x;
}

int Bullet::getLeft()
{
    return bullet.getPosition().x + bullet.getGlobalBounds().width;
}

int Bullet::getTop()
{
    return bullet.getPosition().y;
}

int Bullet::getBottom()
{
    return bullet.getPosition().y + bullet.getGlobalBounds().height;
}

void Bullet::setOrigin(sf::Vector2f origin)
{
    bullet.setOrigin(origin);
}

sf::Vector2f Bullet::shootingDirection(sf::Vector2f mousePosition)
{
    float mouseX = mousePosition.x;
    float mouseY = mousePosition.y + 20;
    float heroPositionX = 1110;
    float heroPositionY = 670;

    float bulletDirectionX = std::abs(mouseX - heroPositionX) / (std::abs(mouseX - heroPositionX) + std::abs(mouseY - heroPositionY));
    float bulletDirectionY = std::abs(mouseY - heroPositionY) / (std::abs(mouseX - heroPositionX) + std::abs(mouseY - heroPositionY));

    if (mousePosition.x < 1110)
    {
        bulletDirectionX = -bulletDirectionX;
    }
    if (mousePosition.y < 670)
    {
        bulletDirectionY = -bulletDirectionY;
    }

    sf::Vector2f direction(bulletDirectionX, bulletDirectionY);

    return direction;
}

void Bullet::fire(float speed, sf::Vector2f direction)
{
    bullet.move(direction.x * speed, direction.y * speed);
    bullet.setRotation((std::atan(direction.y / direction.x) * 180 / M_PI));
}

void Bullet::setPosition(sf::Vector2f position)
{
    bullet.setPosition(position);
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(bullet);
}

sf:: FloatRect Bullet::getGlobalBoungs()
{
    return bullet.getGlobalBounds();
}

void Bullet::deleteBullet()
{
    bullet.setPosition(1000000 , 1000000);
}



















