#pragma once

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Drop : public sf::Sprite
{
public:
    Drop(int gunType, int bulletNumber);

    int getBulletNumber();
    int getGunType();

private:
    int gunType_;
    int bulletNumber_;
};

