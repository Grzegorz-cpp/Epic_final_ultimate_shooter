#include "animated.h"

void Animated::loadTexture(sf::Vector2f position, sf::Texture &texture, sf::Vector2i textureLayout, sf::Vector2i textureSize)
{
    this -> setPosition(position);
    this -> setTexture(texture);

   for (int i = 0; i < textureLayout.y; i++)
   {
        for (int j = 0; j < textureLayout.x; j++)
        {
            frames.emplace_back(sf::IntRect(j * textureSize.x, i * textureSize.y, textureSize.x, textureSize.y));
        }
    }

}

void Animated::getTime(float elapsed)
{
    elapsed_ = elapsed;
}

