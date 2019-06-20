#include "Frame.h"
#include "StartFrame.h"
#include "MultiplayerFrame.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "SpeedChange.h"
#include "SizeChange.h"
#include "Invert.h"
#include "AddFireingRate.h"
#include "AddBarrels.h"
#include <unistd.h>
#include <SFML/Graphics.hpp>

// Method for iterating the 'Frame'. This method together with the render
// method makes for an entire 'game-loop' iteration.
Frame *MultiplayerFrame::iterate()
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
MultiplayerFrame::MultiplayerFrame()
    : GameFrame()
{
    addEntity(std::make_unique<SpaceShip>(
            SCREEN_WIDTH*2/3, SCREEN_HEIGHT/2, *this, 1,
            DEFAULT_KEY_PLAY1_ACCELERATE,
            DEFAULT_KEY_PLAY1_LEFT,
            DEFAULT_KEY_PLAY1_RIGHT,
            DEFAULT_KEY_PLAY1_SHOOT));
    addEntity(std::make_unique<SpaceShip>(
	    SCREEN_WIDTH/3, SCREEN_HEIGHT/2, *this, 2,
            DEFAULT_KEY_PLAY2_ACCELERATE,
            DEFAULT_KEY_PLAY2_LEFT,
            DEFAULT_KEY_PLAY2_RIGHT,
            DEFAULT_KEY_PLAY2_SHOOT));
}

void MultiplayerFrame::spawnPowerUp()
{
    int randomNumber = rand() % 5;
    if (randomNumber == 0)
    {
        addEntity(std::make_unique<SpeedChange>(*this, true, powerUpLifeTime));
    }
    if (randomNumber == 1)
    {
        addEntity(std::make_unique<SizeChange>(*this, true, powerUpLifeTime));
    }
    if (randomNumber == 2)
    {
        addEntity(std::make_unique<AddBarrels>(*this, true, powerUpLifeTime));
    }
    if (randomNumber == 3)
    {
        addEntity(std::make_unique<AddFireingRate>(*this, true, powerUpLifeTime));
    }
    if (randomNumber == 4)
    {
        addEntity(std::make_unique<Invert>(*this, true, powerUpLifeTime));
    }
}
