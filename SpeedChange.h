/*
 * Type of powerUp which will change the speed of the SpaceShip. Will make the
 * SpaceShip faster, if it is anti it will make the opposing SpaceShip smaller.
 */

#ifndef _SPEED_CHANGE_H
#define _SPEED_CHANGE_H

#include "PowerUp.h"
#include "Settings.h"
#include <vector>
#include <functional>

class SpeedChange : public PowerUp
{
public:
    // Default constructor.
    SpeedChange(
            GameFrame &gameFrame,
            bool allowAnti,
            sf::Time lifeTime   = DEFAULT_POWER_UP_LIFE_TIME,
            sf::Time activeTime = DEFAULT_POWER_UP_ACTIVE_TIME);

    /*
    * The power up activate method. This is the method in which the
    * functionality of the power up is defined.
    */
    void activate(SpaceShip &ship) const override;

    /*
    * The power up deactivate method. This is the method in which the
    * functionality of the power up is defined.
    */
    void deactivate(SpaceShip &ship) const override;
private:
    float speedToAdd{};
    std::string file{};
};

#endif
