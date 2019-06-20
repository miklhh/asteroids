/*
 * The singleplayer frame is the frame used in the singleplayer gamestate. In
 * the singleplayer state NO 'red' powerups will spawn, and the state is
 * initiated with one playable spaceship.
 */

#ifndef _SPFRAME_H
#define _SPFRAME_H

#include "Frame.h"
#include "GameFrame.h"
#include "Entity.h"
#include "Settings.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class SingleplayerFrame : public GameFrame
{
public:
    // Method for iterating the 'Frame'. This method together with the 'render'
    // method makes for an entire 'game-loop' iteration. When this iteration
    // is finished it should return a pointer to the next frame to
    // be used by the program. The returned frame should have dynamic storage
    // duration. In any other case this method should return a null-pointer.
    Frame* iterate() override;

    // Constructor and destructor.
    SingleplayerFrame();
    ~SingleplayerFrame() = default;

private:
    void spawnPowerUp() override;
    sf::Clock playtimeClock{};
};

#endif
