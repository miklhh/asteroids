#include "SpeedChange.h"
#include "SpaceShip.h"
#include "GameFrame.h"
#include <string>

SpeedChange::SpeedChange(
        GameFrame &gameFrame,
        bool allowAnti,
        sf::Time lifeTime,
        sf::Time activeTime)
    : PowerUp(gameFrame, allowAnti, lifeTime, activeTime)
{
    if (anti)
    {
    file = "Images/PowerUps/SpeedChange-.png";
    speedToAdd = -0.5f;
    }
    else
    {
    file = "Images/PowerUps/SpeedChange+.png";
    speedToAdd = 0.5f;
    }
    setTexture(gameFrame.textureHandler.getTexture(file));
    setScale(0.5f, 0.5f);
    setRandomPosition();
}

void SpeedChange::activate(SpaceShip &ship) const
{
    ship.addSpeed(speedToAdd);
}

void SpeedChange::deactivate(SpaceShip &ship) const
{
    ship.addSpeed(-1*speedToAdd);
}
