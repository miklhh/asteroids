#include "Asteroid.h"
#include "Projectile.h"
#include "GameFrame.h"
#include "TextureHandler.h"
#include <string>
#include <cmath>

Asteroid::Asteroid(
        float x, float y, float xSpeed, float ySpeed,
        int size, float rotationSpeed, GameFrame &gameFrame) :
    Entity(gameFrame),
    gameFrame(gameFrame),
    deathAnimation("Images/AsteroidAnimation", gameFrame.textureHandler),
    xSpeed(xSpeed),
    ySpeed(ySpeed),
    rotationSpeed(rotationSpeed),
    size(size)
{
    // Set the texture.
    const int realSize = std::pow(2, size);
    const std::string name = "Images/asteroid";
    const std::string nr = std::to_string(realSize);
    const std::string png = ".png";
    const std::string textureName = name + nr + png;
    setTexture(gameFrame.textureHandler.getTexture(textureName));
    gameFrame.textureHandler.setSmooth(textureName, true);
    setPosition(x,y);
    setOrigin(133,133);
}

bool Asteroid::iterate()
{
    // Handle movement and positioning.
    move(xSpeed, ySpeed);
    rotate(rotationSpeed);
    if (getPosition().x > SCREEN_WIDTH + DEFAULT_BLIND_SPOT)
    {
        setPosition(0, getPosition().y);
    }
    if (getPosition().y > SCREEN_HEIGHT + DEFAULT_BLIND_SPOT)
    {
        setPosition(getPosition().x, -DEFAULT_BLIND_SPOT);
    }
    if (getPosition().x < -DEFAULT_BLIND_SPOT)
    {
        setPosition(SCREEN_WIDTH + DEFAULT_BLIND_SPOT, getPosition().y);
    }
    if (getPosition().y < -DEFAULT_BLIND_SPOT)
    {
        setPosition(getPosition().x, SCREEN_HEIGHT + DEFAULT_BLIND_SPOT);
    }

    // Play death animation when hit by a projectile. When animation has played
    // the asteroid is destroyd.
    if (beenHit)
    {
        if (!deathAnimation.testComplete())
        {
            setTexture(deathAnimation.getNextTexture());
        }
        else
        {
            isAlive = false;
        }
    }

    return !isAlive;
}

void Asteroid::handleCollision(const Entity &other)
{
    // Collision with projectile.
    if (dynamic_cast<const Projectile *>(&other))
    {
        //Asteroids with size > 0 is split into two smaller asteroids.
        if (size > 0)
        {
            float rotation = M_PI/4;
            gameFrame.addEntity(std::make_unique<Asteroid>(
                    getPosition().x, getPosition().y,
                    1.3f*(xSpeed*std::cos(rotation)-ySpeed*std::sin(rotation)),
                    1.3f*(xSpeed*std::sin(rotation)+ySpeed*std::cos(rotation)),
                    size - 1, rotationSpeed * 1.5, gameFrame));
            gameFrame.addEntity(std::make_unique<Asteroid>(
                    getPosition().x, getPosition().y,
                    1.3f*(xSpeed*std::cos(-rotation)-ySpeed*std::sin(-rotation)),
                    1.3f*(xSpeed*std::sin(-rotation)+ySpeed*std::cos(-rotation)),
                    size - 1, -rotationSpeed * 1.5, gameFrame));
            isAlive = false;
        }
        else
        {
            beenHit = true;
        }
    }
}
