/*
 * Game frame. 'GameFrame' is uninstanciatable just like 'Frame' but unlike it,
 * the 'GameFrame' implements collision detection between its Entities objects.
 * All objects added with the 'addEntity' method will have active collision
 * detection, will have their 'render' method called once each iteration and 
 * have their 'iterate' method called once each iteration.
 */

#ifndef _GAMEFRAME_H
#define _GAMEFRAME_H

#include "Entity.h"
#include "Frame.h"
#include "Settings.h"
#include "TextureHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>
#include <random>
#include <ctime>

class SpaceShip;

class GameFrame : public Frame
{
public:
    // Method for iterating the 'Frame'. This method together with the 'render'
    // method makes for an entire 'game-loop' iteration. When this frame
    // consider itself finished it should return a pointer to the next frame to
    // be used by the program. The returned frame should have dynamic storage
    // duration. In any other case this method should return a null-pointer.
    virtual Frame* iterate() = 0;

    // Render method for drawing all 'Frame' assiciated objects to the screen.
    // This method should not alter the state of the frame.
    void render(sf::RenderWindow &window) const override;

    // Method for letting the frame handle system events. This method makes it
    // possible for two different frames to handle the same event-type in
    // different manners.
    void handleEvent(const sf::Event &event) override;

    // Method for adding a new Entity to the GameFrame:s entities container.
    // The Entity should already be initialized and should have dynamic
    // storage duration.
    void addEntity(std::unique_ptr<Entity> entity);

    // Method for handling the spawning of all game objects in the gameframe.
    // This method should be called once each game iteration. The function will
    // return a nullptr if no ship with any other tag could be found.
    void handleSpawning();

    // Method for getting the first spaceship in the gameframe whos spaceship
    // tag is not equal to the tag in the spaceship in parameter.
    SpaceShip *getOtherSpaceShip(const SpaceShip *spaceship);

    // Constructor and destructor.
    GameFrame();
    ~GameFrame() = default;

    // Copying of gameframe not allowed.
    GameFrame(const GameFrame &other) = delete;
    GameFrame &operator=(const GameFrame &other) = delete;

    // Game frame texture manager/handler. The texture handler is public since
    // it is used by the Entities in the game frame.
    TextureHandler textureHandler{};

protected:
    // Method for handling collision in the game frame.
    void frameHandleCollision();

    // Iterates all the elements in the game frame. This method handles the
    // removal of entitiy objects.
    void frameIterateEntities();

    void frameHandleSpawning();

    void spawnAsteroid(float asteroidSpeed);

    virtual void spawnPowerUp() = 0;

    sf::Text getScore() const;

    sf::Text getEndScore() const;

    sf::Text getReturnText() const;

    // Containers for different entity objects. Keeping different entities
    // apart massively increases the performance during collision detection.
    std::vector<std::unique_ptr<Entity>> entities{};
    std::vector<std::unique_ptr<Entity>> asteroids{};
    std::vector<std::unique_ptr<Entity>> entitiesBuffer{};

    // GameFrame font.
    sf::Font font{};
    sf::Clock scoreClock{};

    // Game score.
    int gameScore{};

    bool gameOver{false};

    Frame* nextFrame{nullptr};

private:

    // Member variables for handling asteroid spawning.
    sf::Clock waveTimer{};
    sf::Time waveTime{DEFAULT_WAVETIME};

    float asteroidFrequency{INITIAL_ASTEROID_FREQUENCY};
    float asteroidSpeed{INITIAL_ASTEROID_SPEED};
    int waveNumber{0};

protected:
    sf:: Time powerUpLifeTime{DEFAULT_POWER_UP_LIFE_TIME};
};

#endif
