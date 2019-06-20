/*
 * Parentclass: PowerUp
 * AddBarrels is a powerUp subclass wich, when activated on a SpaceShip,
 * changes how the SpaceShip shoots. it will shoot several projectiles in a arc
 * at the same time.
 */
#ifndef _ADD_BARRELS_H
#define _ADD_BARRELS_H

#include "PowerUp.h"
#include "Settings.h"
#include <vector>
#include <functional>

class AddBarrels : public PowerUp
{
public:
    // Default constructor.
    AddBarrels(
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
};

#endif
