#include "TextureHandler.h"
#include "Animation.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <stdexcept> // Implement out own exception instead.

Animation::Animation(const std::string &directory, TextureHandler &handler)
    : textureHandler(handler)
{
    // Try to load the animaiton images from file into (video) memory. The files
    // in the animation directory should be named: (1.png, 2.png, ...) and this
    // animation class will display them in order when playing.
    unsigned currentNr = 1;
    bool loadingImages = true;
    while (loadingImages)
    {
        const std::string nr = std::to_string(currentNr);
        const std::string png = ".png";
        const std::string slash = "/";
        const std::string currentFileName = directory + slash + nr + png;
        std::ifstream infile(currentFileName);
        if (infile.good())
        {
            textureHandler.getTexture(currentFileName);
            textureNames.push_back(currentFileName);
            currentNr++;
        }
        else
        {
            loadingImages = false;
        }
    }

    // If no image we're able to load from the animation director we throw an
    // exception.
    if (textureNames.empty())
    {
        // TODO: Throw a game exception instead.
        const std::string errorMsg = 
            std::string("Failed to load animation from: ") + directory;
        throw std::out_of_range(errorMsg);
    }
}

bool Animation::testComplete() const
{
    return currentTextureIndex == textureNames.size() - 1;
}

const sf::Texture &Animation::getNextTexture()
{
    const std::string textureName = textureNames.at(currentTextureIndex);
    ++currentTextureIndex;
    return textureHandler.getTexture(textureName);
}
