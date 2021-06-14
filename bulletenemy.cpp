#include "bulletenemy.h"

#include "enemy.h"

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

BulletEnemy::BulletEnemy(sf::Vector2f size)
{
    bulletEnemy.setSize(size);
    bulletEnemy.setFillColor(sf::Color::Black);
}

int BulletEnemy::getRight()
{
    return bulletEnemy.getPosition().x;
}

int BulletEnemy::getLeft()
{
    return bulletEnemy.getPosition().x + bulletEnemy.getGlobalBounds().width;
}

int BulletEnemy::getTop()
{
    return bulletEnemy.getPosition().y;
}

int BulletEnemy::getBottom()
{
    return bulletEnemy.getPosition().y + bulletEnemy.getGlobalBounds().height;
}

void BulletEnemy::setOrigin(sf::Vector2f origin)
{
    bulletEnemy.setOrigin(origin);
}

sf::Vector2f BulletEnemy::shootingDirection(sf::Vector2f mousePosition, sf::Vector2f enemyPosition)
{
    float mouseX = mousePosition.x;
    float mouseY = mousePosition.y + 20;
    float heroPositionX = enemyPosition.x;
    float heroPositionY = enemyPosition.y;

    float bulletDirectionX = std::abs(mouseX - heroPositionX) / (std::abs(mouseX - heroPositionX) + std::abs(mouseY - heroPositionY));
    float bulletDirectionY = std::abs(mouseY - heroPositionY) / (std::abs(mouseX - heroPositionX) + std::abs(mouseY - heroPositionY));

    if (mousePosition.x < enemyPosition.x)
    {
        bulletDirectionX = -bulletDirectionX;
    }
    if (mousePosition.y < enemyPosition.y)
    {
        bulletDirectionY = -bulletDirectionY;
    }

    sf::Vector2f direction(bulletDirectionX, bulletDirectionY);

    return direction;
}

void BulletEnemy::fire(float speed, sf::Vector2f direction)
{
    bulletEnemy.move(direction.x * speed, direction.y * speed);
    bulletEnemy.setRotation((std::atan(direction.y / direction.x) * 180 / M_PI));
}

void BulletEnemy::setPosition(sf::Vector2f position)
{
    bulletEnemy.setPosition(position);
}

void BulletEnemy::draw(sf::RenderWindow &window)
{
    window.draw(bulletEnemy);
}

sf:: FloatRect BulletEnemy::getGlobalBounds()
{
    return bulletEnemy.getGlobalBounds();
}

void BulletEnemy::deleteBullet()
{
    bulletEnemy.setPosition(100000 , 100000);
}

















