#include "Entity.h"
#include "Frame.h"
#include "StartFrame.h"
#include "Settings.h"
#include "AsteroidException.h"
#include <SFML/Graphics.hpp>
#include <iostream>

volatile int i;

// The main iteration loop. 
void iterate_loop(Frame *&currentFrame, sf::RenderWindow &window)
{
    // Clear the current window buffer.
    window.clear(DEFAULT_CLEAR_COLOR);

    // Iterate the current frame and test if we shuld switch frame.
    if (Frame *nextFrame = currentFrame->iterate())
    {
        delete currentFrame;
        currentFrame = nextFrame;
    }

    // Draw the current frame.
    currentFrame->render(window);

    // Swap the window buffers.
    window.display();

    // Handle events.
    sf::Event event;
    while(window.pollEvent(event))
    {
        // Test if the user wants to exit the application.
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        // Handle frame events.
        currentFrame->handleEvent(event);
    }
}

int main()
{
    // Create the window.
    const unsigned WIDTH = static_cast<unsigned>(SCREEN_WIDTH);
    const unsigned HEIGHT = static_cast<unsigned>(SCREEN_HEIGHT);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Asteroids", 
            sf::Style::Titlebar | sf::Style::Close);

    // Create a new start frame;
    const unsigned ACCTUAL_WIDTH = window.getSize().x;
    const unsigned ACCTUAL_HEIGHT = window.getSize().y;
    StartFrame *startFrame = new StartFrame(ACCTUAL_WIDTH, ACCTUAL_HEIGHT);

    // Create and set current frame to start frame.
    Frame *currentFrame = startFrame;

    // Game Loop with its corresponding timer.
    sf::Clock clock;
    while (window.isOpen())
    {
        // Restart the timer/clock.
        clock.restart();

        // Iterate the loop.
        try
        {
            iterate_loop(currentFrame, window);
        }
        catch (const AsteroidException &e)
        {
            std::cerr << std::endl;
            std::cerr << "Fatal application failure." << std::endl;
            std::cerr << "Error message: \"" << e.what() << "\"" << std::endl;
            std::cerr << "Asteroids will now exit!" << std::endl << std::endl;
            window.close();
        }

        // Sleep for a 17 - t [ms], where t is the current iteration time.
        sf::Time time = clock.getElapsedTime();
        sf::sleep(sf::milliseconds(17) - time);
    }

    // Delete the current frame and return.
    delete currentFrame;
    return 0;
}
