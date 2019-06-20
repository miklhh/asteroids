/*
 * Parentclass: PowerUp
 * AddFireingRate is a powerUp subclass wich, when activated on a SpaceShip,
 * changes how the SpaceShip shoots. it will increase how fast the SpaceShip
 * shoots, by adding a constant. 
 */
#ifndef _ADD_FIREING_RATE_
#define _ADD_FIREING_RATE_

#include "PowerUp.h"
#include "Settings.h"
#include <vector>
#include <functional>

class AddFireingRate : public PowerUp
{
public:
    // Default constructor.
    AddFireingRate(
            GameFrame &gameFrame,
            bool allowAnti,
            sf::Time lifeTime   = DEFAULT_POWER_UP_LIFE_TIME,
            sf::Time activeTime = DEFAULT_POWER_UP_ACTIVE_TIME);

    // The power up activate method. This is the method in which the
    // functionality of the power up is defined.
    void activate(SpaceShip &ship) const override;

    // The power up deactivate method. This is the method in which the
    // functionality of the power up is defined.
    void deactivate(SpaceShip &ship) const override;

private:
    float fireingrate{};
};

#endif
