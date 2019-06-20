#include "SizeChange.h"
#include "SpaceShip.h"
#include "GameFrame.h"
#include <string>

SizeChange::SizeChange(
        GameFrame &gameFrame,
        bool allowAnti,
        sf::Time lifeTime,
        sf::Time activeTime)
    : PowerUp(gameFrame, allowAnti, lifeTime, activeTime)

{
    if (anti)
    {
        file = "Images/PowerUps/SizeChange-.png";
        scale = DEFAULT_SHIP_SCALE*2.0f;
    }
    else
    {
        file = "Images/PowerUps/SizeChange+.png";
        scale = DEFAULT_SHIP_SCALE/2.0f;
    }
    setTexture(gameFrame.textureHandler.getTexture(file));
    setScale(0.5f, 0.5f);
    setRandomPosition();
}

void SizeChange::activate(SpaceShip &ship) const
{
    ship.addScale(scale);
}

void SizeChange::deactivate(SpaceShip &ship) const
{
    ship.addScale(DEFAULT_SHIP_SCALE);
}
