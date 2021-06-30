#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(sf::Vector2f size);

    int getRight();
    int getLeft();
    int getTop();
    int getBottom();
    void fire(float speed, sf::Vector2f mousePosition);
    void getTime(float elapesd);
    void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f position);
    void setOrigin(sf::Vector2f origin);
    void setFireRate(float fireRate);
    sf::Vector2f shootingDirection(sf::Vector2f mousePosition);
    sf:: FloatRect getGlobalBounds();
    sf::Vector2f getBulletPosition();

private:
    sf::RectangleShape bullet;
};
