#include "PowerUp.h"
#include "SpaceShip.h"
#include <vector>
#include <functional>

PowerUp::PowerUp(
        GameFrame &gameFrame,
        bool allowAnti,
        sf::Time lifeTime,
        sf::Time activeTime)
    : Entity(gameFrame), allowAnti(allowAnti), lifeTime(lifeTime), activeTime(activeTime)
{
    if (allowAnti)
    {
        int isAnti = 1 + rand() %2;
        anti = (isAnti == 1) ? false : true;
    }
    else
    {
        anti = false;
    }
}

void PowerUp::handleCollision(const Entity &entity)
{
    // Suppress warning.
    (void) entity;

    // Collision with a spaceship.
    if (dynamic_cast<const SpaceShip *>(&entity))
    {
        isActive = true;
        setPosition(-1000, -1000);
        timer.restart();
    }
}

void PowerUp::setRandomPosition()
{
    float x = rand() % 1920;
    float y = rand() % 1080;
    setPosition(x, y);
}

sf::Time PowerUp::timeLeft() const
{
    if (!isActive)
    {
        // Power up hasn't been activated. Return time untill it gets destroyed.
        return lifeTime - timer.getElapsedTime();
    }
    else
    {
        // Power up has been activated. Return remaining power up time.
        return activeTime - timer.getElapsedTime();
    }
}


bool PowerUp::iterate()
{
    if (timeLeft().asMilliseconds() < 0)
    {
        if (isActive)
        {
            // When the power is no longer active we wait one extra iteration
            // before we destroy it. This will guarantie that the spaceship that
            // has aquiered the power up will have it removed from its 'active
            // power up.
            isAlive = !extraIterationDone;
            extraIterationDone = true;
        }
        else
        {
            // No one took the power up. Destroy it.
            isAlive = false;
        }
    }
    return !isAlive;
}

bool PowerUp::testAnti() const
{
    return anti;
}
