/*
 * Parentclass: Entity
 * SpaceShip is initiatied by SingleplayerFrame or MultiplayerFrame. The object is
 * Controlled by the user via keyboard input. SpaceShip can create Projectile-objects.
 * Spaceships will be destroyed if it collides with an asteroid and it's prarameters
 * will be altered when it collides with powerups.
*/

#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include "Entity.h"
#include "Settings.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class PowerUp;
class GameFrame;

class SpaceShip : public Entity
{
public:
    // Constructor and destructor. Parameter 'id' shoud be set to eather '1'or
    // '2' and acts as an indentification parameter.
    SpaceShip(
            float x, float y, GameFrame &gameFrame, int id,
            sf::Keyboard::Key keyAccelerate,
            sf::Keyboard::Key keyLeft,
            sf::Keyboard::Key keyRight,
            sf::Keyboard::Key keyShoot);
    ~SpaceShip() = default;

    // Method for handling collision with other 'Entity'-objects. Every 'Entity'
    // object handles themself in their resprective 'handleCollision' method,
    // and does not affect any other 'Entity'.
    void handleCollision(const Entity &other) override;

    // Method for iterating the 'Entity'. This method will be called one time
    // each iteration in the 'game-loop'. This method should return true if it
    // wants to be destroyed after iterating kand false otherwise.
    bool iterate() override;

    // Fire the spaceship gun. The method will automaticly detect the weapon
    // attributes and fire accordingly.
    void shoot();

    // Method for aquiering and handeling a powerUp.
    void addPowerUp(const PowerUp *powerup);

    // Get the id of the spaceship.
    int getId() const;

    // Methods for changing spaceship attributes.
    void addWeaponAttributes(float fireingRateToAdd, int extraBarrelsToAdd);
    void addSpeed(float speedToAdd);
    void addScale(float scaleToAdd);
    void invertStearing();

private:
    // Private method for handling aquiered power ups.
    void handlePowerUps();

    // Ship settings.
    float   xSpeed              = 0.0f;
    float   ySpeed              = 0.0f;
    bool    isAlive             = true;
    bool    invertedStearing    = false;
    bool    beenHit             = false;
    float   speed               = DEFAULT_SHIP_SPEED;
    float   scale               = DEFAULT_SHIP_SCALE;
    float   recoil              = DEFAULT_SHIP_RECOIL;
    float   fireRate            = DEFAULT_SHIP_FIRE_RATE;
    int     extraBarrels        = DEFAULT_SHIP_EXTRA_BARRELS;
    int     projetileSpeed      = DEAFULT_PROJECTILE_SPEED;
    int     id;
    sf::Clock coolDown{};
    std::vector<const PowerUp *> powerUps{};
    Animation deathAnimation;

    // Ship controls.
    sf::Keyboard::Key keyAccelerate;
    sf::Keyboard::Key keyLeft;
    sf::Keyboard::Key keyRight;
    sf::Keyboard::Key keyShoot;
};

#endif
