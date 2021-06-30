#pragma once

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Animated : public sf::Sprite
{
public:
    void loadTexture(sf::Vector2f position, sf::Texture &texture, sf::Vector2i textureLayout, sf::Vector2i textureSize);
    void getTime(float elapesd);

    int frame_ = 0;
    int frequency_ = 1;
    std::vector<sf::IntRect> frames;

protected:
    float elapsed_;
    int gunType_;
};

