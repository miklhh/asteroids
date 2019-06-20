/*
 * The multiplayer frame is the frame used in the multiplayer gamestate. In 
 * the multiplayer state 'red' powerups can spawn and the state is initiated
 * with two playable spaceships.
 */

#ifndef _MPFRAME_H
#define _MPFRAME_H

#include "Entity.h"
#include "Frame.h"
#include "GameFrame.h"
#include "Settings.h"
#include <SFML/Graphics/RenderWindow.hpp>

class MultiplayerFrame : public GameFrame
{
public:
    // Method for iterating the 'Frame'. This method together with the 'render'
    // method makes for an entire 'game-loop' iteration. When this iteration
    // is finished it should return a pointer to the next frame to
    // be used by the program. The returned frame should have dynamic storage
    // duration. In any other case this method should return a null-pointer.
    Frame* iterate() override;

    // Constructor and destructor.
    MultiplayerFrame();
    ~MultiplayerFrame() = default;

private:
    void spawnPowerUp() override;
};

#endif
