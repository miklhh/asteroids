#include "Invert.h"
#include "SpaceShip.h"
#include "GameFrame.h"
#include <string>

Invert::Invert(
        GameFrame &gameFrame,
        bool allowAnti,
        sf::Time lifeTime,
        sf::Time activeTime)
    : PowerUp(gameFrame, allowAnti, lifeTime, activeTime)

{
    anti = true;
    const std::string file = "Images/PowerUps/inv.png";
    setTexture(gameFrame.textureHandler.getTexture(file));
    setScale(0.5f, 0.5f);
    setRandomPosition();
}

void Invert::activate(SpaceShip &ship) const
{
    ship.invertStearing();
}

void Invert::deactivate(SpaceShip &ship) const
{
    ship.invertStearing();
}
