/*
 * The texture handler should preferably handle all the textures among the 
 * objects that want to use collision detection. By using the texture handler, 
 * textures can be shared among different instances that wants to use the same 
 * image. The texture handler also makes sure that all textures are loaded in 
 * the prefered way specified in 'Collision.h'. The application should use a
 * global texture handler for easy access to textures by all the objects that
 * want to use them.
 */

#ifndef _TEXTURE_HANDLER_H
#define _TEXTURE_HANDLER_H

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <string>

class TextureHandler
{
public:
    // Default constructor and destructor.
    TextureHandler() = default;
    ~TextureHandler() = default;

    // No copying of texture handlers.
    TextureHandler(const TextureHandler &other) = delete;
    TextureHandler &operator=(const TextureHandler &other) = delete;

    // The 'getTexture' takes a file path string as parameter and returns a
    // a reference to an SFML texture loaded with the image in the file path.
    // This is to prevent multiple instances of the same texture. This will
    // also make sure that the collision handler always creates a bitmask for
    // each texture:
    const sf::Texture &getTexture(const std::string &filename);

    // Method for setting turning on the SFML 'setSmooth' functionallity for a
    // texture in the texture handler.
    void setSmooth(const std::string &filename, bool smooth);

private:
    // Static associative container for storing all the textures. The field
    // is static to prevent loading the same texture more than once.
    static std::unordered_map<std::string, sf::Texture> textures;
};

#endif
