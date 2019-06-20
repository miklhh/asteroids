/*
 * Animation handles the animation for SpaceShip and Asteroid.
 */
#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "TextureHandler.h"
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Animation
{
public:
    // Deafult constructor and destructor.
    Animation(const std::string &directory, TextureHandler &handler);
    ~Animation() = default;

    // Method for testing if the animation is over. Returns true if all the
    // images in the animations has been shown.
    bool testComplete() const;

    // Get the next texture in the animation queue. The method will return a
    // reference to a the next texture (image) in the animation. Invoking this
    // method will automaticly restart.
    const sf::Texture &getNextTexture();

private:
    TextureHandler &textureHandler;
    std::vector<std::string> textureNames{};
    size_t currentTextureIndex{0};
    bool animationOver{false};
};

#endif
