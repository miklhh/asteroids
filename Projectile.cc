#include "Projectile.h"
#include "GameFrame.h"
#include "Asteroid.h"
#include "Settings.h"
#include <cmath>


Projectile::Projectile(float x, float y, float speed, float rotation, GameFrame &gameFrame)
  : Entity(gameFrame), isAlive(true), gameFrame(gameFrame)
{
    // Set speed position and rotation.
    xSpeed = speed*std::cos(rotation/360*2*M_PI);
    ySpeed = speed*std::sin(rotation/360*2*M_PI);
    setPosition(x,y);
    setRotation(rotation);

    // Set the projectile texture and look.
    const std::string file = "Images/projectile.png";
    setTexture(gameFrame.textureHandler.getTexture(file));
    setOrigin(1,0);
}


bool Projectile::iterate()
{
    //Checks if projectile is outside frame
    move(xSpeed, ySpeed);
    if ( (getPosition().x > SCREEN_WIDTH + DEFAULT_BLIND_SPOT)  ||
         (getPosition().x < 0 - DEFAULT_BLIND_SPOT)             ||
         (getPosition().y > SCREEN_HEIGHT + DEFAULT_BLIND_SPOT) ||
         (getPosition().y < 0 - DEFAULT_BLIND_SPOT)             )
    {
        isAlive = false;
    }

    return !isAlive;
}

void Projectile::handleCollision(const Entity &other)
{
    if (dynamic_cast<const Asteroid *>(&other))
    {
        isAlive = false;
    }
}

