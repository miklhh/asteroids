#include "AddBarrels.h"
#include "SpaceShip.h"
#include "GameFrame.h"

AddBarrels::AddBarrels(
        GameFrame &gameFrame,
        bool allowAnti,
        sf::Time lifeTime,
        sf::Time activeTime)
    : PowerUp(gameFrame, allowAnti, lifeTime, activeTime)
{
    anti = false;
    const std::string file = "Images/PowerUps/AddBarrels.png";
    setTexture(gameFrame.textureHandler.getTexture(file));
    setScale(0.5f,0.5f);
    setRandomPosition();
}

void AddBarrels::activate(SpaceShip &ship) const
{
    ship.addWeaponAttributes(0.0f, 2);
}

void AddBarrels::deactivate(SpaceShip &ship) const
{
    ship.addWeaponAttributes(0.0f, -2);
}
