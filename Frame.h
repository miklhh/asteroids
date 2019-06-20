/*
 * Base class for a 'frame' or a 'game state'. Using frames makes it very easy
 * to swap between different parts of the game, ex swap between main menu and
 * the acctuall game. All 'game states' should inherit from 'Frame'.
 */

#ifndef _FRAME_H
#define _FRAME_H

#include <SFML/Graphics/RenderWindow.hpp>

class Frame
{
public:
    // Method for iterating the 'Frame'. This method together with the 'render'
    // method makes for an entire 'game-loop' iteration. When this frame 
    // consider itself finished it should return a pointer to the next frame to
    // be used by the program. The returned frame should have dynamic storage 
    // duration. In any other case this method should return a null-pointer.
    virtual Frame *iterate() = 0;

    // Render method for drawing all 'Frame' assiciated objects to the screen.
    // This method should not alter the state of the frame.
    virtual void render(sf::RenderWindow &window) const = 0;

    // Method for letting the frame handle system events. This method makes it
    // possible for two different frames to handle the same event-type in 
    // different manners.
    virtual void handleEvent(const sf::Event &event) = 0;

    // Virtual destructor.
    virtual ~Frame() = default;

protected:
    // Protected constructor to mark 'Frame' as uninstanciatable.
    Frame() = default;
};

#endif
