/*
 * PowerUp subclass which when activated inverts the controls of the opposing
 * player.
 */
#ifndef _INVERT_H
#define _INVERT_H

#include "PowerUp.h"
#include "Settings.h"
#include <vector>
#include <functional>

class Invert : public PowerUp
{
public:
    // Default constructor.
    Invert(
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
};

#endif
