#include "AddFireingRate.h"
#include "SpaceShip.h"
#include "GameFrame.h"
#include <string>

AddFireingRate::AddFireingRate(
        GameFrame &gameFrame,
        bool allowAnti,
        sf::Time lifeTime,
        sf::Time activeTime)
    : PowerUp(gameFrame, allowAnti, lifeTime, activeTime)
{
    std::string file;
    if (anti)
    {
        file = "Images/PowerUps/RPM-.png";
        fireingrate = -DEFAULT_SHIP_FIRE_RATE/1.5;
    }
    else
    {
        file = "Images/PowerUps/RPM+.png";
        fireingrate = 10.0f;
    }
    setTexture(gameFrame.textureHandler.getTexture(file));
    setScale(0.5f, 0.5f);
    setRandomPosition();
}

void AddFireingRate::activate(SpaceShip &ship) const
{
    ship.addWeaponAttributes(fireingrate, 0.0f);
}

void AddFireingRate::deactivate(SpaceShip &ship) const
{
    ship.addWeaponAttributes(-fireingrate, 0.0f);
}
