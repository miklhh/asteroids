#include "TextureHandler.h"
#include "Collision.h"
#include "AsteroidException.h"
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

const sf::Texture &TextureHandler::getTexture(const std::string &filename)
{
    // If the texture has already been loaded, return the already loaded
    // texture. Otherwise create a new texture, store it in the container, let
    // it load from file and then return it.
    if (textures.find(filename) != textures.end())
    {
        return textures.at(filename);
    }
    else
    {
        // Try to create a new texture and load it from the file.
        typedef std::pair<std::string, sf::Texture> pair;
        textures.insert(pair(filename, sf::Texture{}));
        if (!Collision::CreateTextureAndBitmask(textures.at(filename), filename))
        {
            // Failed to load the image from file. Throw an asteroid exception.
            std::string msg;
            msg += std::string("TextureHandler failed to load from file: '");
            msg += filename;
            msg += std::string("'.");
            throw AsteroidException(msg);
        }
        else
        {
            return textures.at(filename);
        }
    }
}

void TextureHandler::setSmooth(const std::string &filename, bool smooth)
{
    textures.at(filename).setSmooth(smooth);
}

// Initialization of static memeber field.
std::unordered_map<std::string, sf::Texture> TextureHandler::textures{};
