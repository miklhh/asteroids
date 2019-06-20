#include "Frame.h"
#include "StartFrame.h"
#include "SingleplayerFrame.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "Settings.h"
#include "SpeedChange.h"
#include "SizeChange.h"
#include "Invert.h"
#include "AddFireingRate.h"
#include "AddBarrels.h"
#include <cmath>
#include <SFML/Graphics.hpp>

// Method for iterating the 'Frame'. This method together with the render
// method makes for an entire 'game-loop' iteration.
Frame *SingleplayerFrame::iterate()
{
    frameHandleCollision();
    frameIterateEntities();
    frameHandleSpawning();

    if (gameOver && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)))
    {
            nextFrame = new StartFrame(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    return nextFrame;
}

// GameFrame constructor.
SingleplayerFrame::SingleplayerFrame()
    : GameFrame()
{
    // TODO: Spaceship constructor has been updated in more recent commits.
    addEntity(std::make_unique<SpaceShip>(
	    SCREEN_WIDTH/2, SCREEN_HEIGHT/2, *this, 1,
            DEFAULT_KEY_PLAY1_ACCELERATE,
            DEFAULT_KEY_PLAY1_LEFT,
            DEFAULT_KEY_PLAY1_RIGHT,
            DEFAULT_KEY_PLAY1_SHOOT));
}


void SingleplayerFrame::spawnPowerUp()
{
    int randomNumber = rand() % 4;
    if (randomNumber == 0)
    {
        addEntity(std::make_unique<SpeedChange>(*this, false, powerUpLifeTime));
    }
    if (randomNumber == 1)
    {
        addEntity(std::make_unique<SizeChange>(*this, false, powerUpLifeTime));
    }
    if (randomNumber == 2)
    {
        addEntity(std::make_unique<AddBarrels>(*this, false, powerUpLifeTime));
    }
    if (randomNumber == 3)
    {
        addEntity(std::make_unique<AddFireingRate>(*this, false, powerUpLifeTime));
    }
}
