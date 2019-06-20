/*
 * When a SpaceShip collides with a powerUp some properties of either the
 * SpaceShip which collided with it or the opposing SpaceShip (depends on the
 * type of powerUp, see the individual classes). If the powerUp affects the
 * opposing SpaceShip it is called an anti. The different powerUps will
 * be created with a random type and on a random location at the beginning of each
 * wave. The powerUps will disappear at the end of each wave. More powerUps
 * is created the longer the game continues.
 */

#ifndef _POWER_UP_H
#define _POWER_UP_H

#include "Entity.h"
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>

class SpaceShip;
class GameFrame;

class PowerUp : public Entity
{
public:
    // Default constructor and virtual destructor.
    PowerUp(
            GameFrame &gameFrame,
            bool allowAnti,
            sf::Time lifeTime,
            sf::Time activeTime);
    virtual ~PowerUp() = default;

    /*
     * Method for iterating the 'Entity'. This method will be called one time
     * each iteration in the 'game-loop'. This method should return true if it
     * wants to be destroyed after iterating kand false otherwise.
     */
    bool iterate() override;

    /*
     * 'handleCollision' method. This is where the power up is activated.
     */
    void handleCollision(const Entity &entity) override;

    /*
     * The power up activate method. This is the method in which the
     * functionality of the power up is defined. This method should be called
     * by the collider to have the effect kick in.
     */
    virtual void activate(SpaceShip &ship) const = 0;

    /*
     * The power up deactivate method. This is the method in which the
     * functionality of the power up is defined. This methods should be called
     * by the collider
     */
    virtual void deactivate(SpaceShip &ship) const = 0;

    /*
     *Sets the position to a random point on the screen.
     */
    void setRandomPosition();

    /*
     * Returns the remaining active time of an power up. This is, the time left
     * until the the power up gets destroyd if the power up has not been picked
     * up, and the time left of an active power up if it has been picked up.
     */
    sf::Time timeLeft() const;

    /*
     * Test if the powerup is an anti powerup. A powerup is considerd anti if it
     * affects the ship not taking the powerup.
     */
    bool testAnti() const;

protected:
    bool isAlive{true};
    bool isActive{false};
    bool extraIterationDone{false};
    bool anti{false};
    bool allowAnti;

    /*
     * Time main timer of the power up. The timer is used to  keep track of the
     * power up lifetime when the power up has not been activated, and it is
     * used as to keep track of the effect time once it has been activated.
     */
    sf::Clock timer{};

    /*
     * 'lifeTime' is the life time of an unpicked power up. Once 'lifeTime'
     * amount of time has passed, the power up will be removed from the playing
     * field.
     */
    sf::Time lifeTime{};

    /*
     * 'activeTime' is the amount of time the power up will have its effect.
     * Once 'activeTime' amount of time has passed the deactivate method should
     * be triggered.
     */
    sf::Time activeTime{};
};

#endif
