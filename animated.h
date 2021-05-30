#pragma once

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Animated : public sf::Sprite
{
public:
    void loadTexture(const sf::Vector2f &position, sf::Texture &texture, sf::Vector2i textureLayout, sf::Vector2i textureSize);
    void getTime(float elapesd);

    std::vector<sf::IntRect> frames;

    int frame_ = 0;
    int frequency_ = 1;

protected:
    float elapsed_;
    int gunType_;
};

