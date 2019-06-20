#include "GameFrame.h"
#include "TextureHandler.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "PowerUp.h"
#include "Settings.h"
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <stdexcept>
#include <cmath>
#include <memory>

SpaceShip::SpaceShip(
        float x, float y, GameFrame &gameFrame, int id,
        sf::Keyboard::Key keyAccelerate,
        sf::Keyboard::Key keyLeft,
        sf::Keyboard::Key keyRight,
        sf::Keyboard::Key keyShoot) :
    Entity(gameFrame),
    id(id),
    deathAnimation(
            std::string("Images/DeathAnimation") + std::to_string(id),
            gameFrame.textureHandler),
    keyAccelerate(keyAccelerate),
    keyLeft(keyLeft),
    keyRight(keyRight),
    keyShoot(keyShoot)
{
    // Load the texture.
    const std::string fileName = "Images/player" + std::to_string(id) + ".png";
    setTexture(gameFrame.textureHandler.getTexture(fileName));
    gameFrame.textureHandler.setSmooth(fileName, true);

    // Set the spaceship sprite properties.
    setOrigin(400, 155);
    setRotation(-90);
    setScale(scale, scale);
    setPosition(x, y);
}

void SpaceShip::handleCollision(const Entity &other)
{
    if (dynamic_cast<const Asteroid *>(&other))
    {
        beenHit = true;
    }

    if (const PowerUp *powerup = dynamic_cast<const PowerUp *>(&other))
    {
        // Test if it is an anti power up.
        if (powerup->testAnti())
        {
            // If any opponent ship exists, we activate the power up on the
            // opponent.
            if (SpaceShip *other = gameFrame.getOtherSpaceShip(this))
            {
                other->addPowerUp(powerup);
            }
            //gameFrame.getOtherSpaceShip(this)->addPowerUp(powerup);
        }
        else
        {
            addPowerUp(powerup);
            //powerUps.push_back(powerup);
            //powerup->activate(*this);
        }
    }
}

bool SpaceShip::iterate()
{
    // Handle user keyboard input.
    if (sf::Keyboard::isKeyPressed(keyAccelerate))
    {
        const float pi = 3.1415926535f;
        ySpeed += sin(getRotation() * pi / 180) * speed;
        xSpeed += cos(getRotation() * pi / 180) * speed;
    }
    if (sf::Keyboard::isKeyPressed(keyLeft))
    {
        const float stearingDirection = invertedStearing ? -1 : 1;
        rotate(stearingDirection * -DEFAULT_SHIP_ROTATE_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(keyRight))
    {
        const float stearingDirection = invertedStearing ? -1 : 1;
        rotate(stearingDirection * DEFAULT_SHIP_ROTATE_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(keyShoot))
    {
        shoot();
    }

    // Handle movement and deacceleration.
    xSpeed /= DEFAULT_SHIP_BREAK_COEFF;
    ySpeed /= DEFAULT_SHIP_BREAK_COEFF;
    move(xSpeed, ySpeed);
    if (getPosition().x > SCREEN_WIDTH + DEFAULT_BLIND_SPOT)
    {
        setPosition(0.0f, getPosition().y);
    }
    if (getPosition().y > SCREEN_HEIGHT + DEFAULT_BLIND_SPOT)
    {
        setPosition(getPosition().x, 0.0f - DEFAULT_BLIND_SPOT);
    }
    if (getPosition().x < 0.0f - DEFAULT_BLIND_SPOT)
    {
        setPosition(SCREEN_WIDTH + DEFAULT_BLIND_SPOT, getPosition().y);
    }
    if (getPosition().y < 0.0f - DEFAULT_BLIND_SPOT)
    {
        setPosition(getPosition().x, SCREEN_HEIGHT + DEFAULT_BLIND_SPOT);
    }

    // Play the death animation if the ship collided with an asteroid.
    if (beenHit)
    {
        if (!deathAnimation.testComplete())
        {
            setTexture(deathAnimation.getNextTexture());
        }
        else
        {
            isAlive = false;
        }
    }

    // Handle the powerups acting on the spaceship.
    handlePowerUps();

    return !isAlive;
}

void SpaceShip::shoot()
{
    // Only fire the gun if the time elapsed since last shoot is greater than
    // the firerate time period.
    sf::Time firePeriod = sf::seconds(1.0f/fireRate);
    if(coolDown.getElapsedTime() > firePeriod)
    {
        // Aquire parameters.
        std::function<float(float)> sqr = [](float x)->float { return x * x; };
        float x = getPosition().x;
        float y = getPosition().y;
        float speed = DEAFULT_PROJECTILE_SPEED + sqrt(sqr(xSpeed) + sqr(ySpeed));
        float rotation = getRotation();

        // Fire one shot in the forward direction.
        xSpeed -= recoil * cos(rotation/180*M_PI);
        ySpeed -= recoil * sin(rotation/180*M_PI);
        gameFrame.addEntity(
                std::make_unique<Projectile>(x, y, speed, rotation, gameFrame));

        // Shot one extra projectile one both sides for each extra barrel.
        for (int barrel = 1; barrel <= extraBarrels; barrel++ )
        {
            xSpeed -= 2*recoil*cos(rotation/180*M_PI);
            ySpeed -= 2*recoil*sin(rotation/180*M_PI);
            gameFrame.addEntity(
                    std::make_unique<Projectile>(
                            x, y, speed, rotation + barrel*10, gameFrame));
            gameFrame.addEntity(
                    std::make_unique<Projectile>(
                            x, y, speed, rotation - barrel*10, gameFrame));
        }

        // Reset the cooldown.
        coolDown.restart();
    }
}

void SpaceShip::addPowerUp(const PowerUp* powerUp)
{
    powerUps.push_back(powerUp);
    powerUp->activate(*this);
}

int SpaceShip::getId() const
{
    return id;
}

void SpaceShip::addWeaponAttributes(float fireingRateToAdd, int extraBarrelsToAdd)
{
    fireRate += fireingRateToAdd;
    extraBarrels += extraBarrelsToAdd;
}

void SpaceShip::addSpeed(float speedToAdd)
{
    speed += speedToAdd;
}

void SpaceShip::addScale(float scaleToAdd)
{
    setScale(scaleToAdd, scaleToAdd);
}

void SpaceShip::invertStearing()
{
    invertedStearing = !invertedStearing;
}

void SpaceShip::handlePowerUps()
{
    auto timesUp = [this](const PowerUp *powerUp)->bool 
    { 
        if (powerUp->timeLeft() <= sf::milliseconds(0))
        {
            powerUp->deactivate(*this);
            return true;
        }
        return false;
    };
    powerUps.erase(
            std::remove_if(powerUps.begin(), powerUps.end(), timesUp),
            powerUps.end());
}
