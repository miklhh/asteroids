#include "Frame.h"
#include "GameFrame.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <memory>
#include <cmath>
#include <cstdlib>

// Render method for drawing all 'Frame' assiciated objects to the screen.
// This method should not alter the state of the frame.
void GameFrame::render(sf::RenderWindow &window) const
{
    // Draw all the 'default' entities.
    for (const std::unique_ptr<Entity> &entity : entities)
    {
        window.draw(*entity);
    }

    // Draw all the asteroids.
    for (const std::unique_ptr<Entity> &asteroid : asteroids)
    {
        window.draw(*asteroid);
    }

    // Draw the score to the screen.
    window.draw(getScore());

    // If the game is over, draw the gameover screen.
    if (gameOver)
    {

        // Draw the score.
        window.draw(getEndScore());

        // Draw the 'press enter to return to menu'.
        window.draw(getReturnText());
    }
}

// Method for letting the frame handle system events. This method makes it
// possible for two different frames to handle the same event-type in
// different manners.
void GameFrame::handleEvent(const sf::Event &event)
{
    (void) event;
}

// Method for adding a new Entity to the GameFrame:s entities container.
// The Entity should already be initialized and should have dynamic
// storage duration.
void GameFrame::addEntity(std::unique_ptr<Entity> entity)
{
    entitiesBuffer.push_back(std::move(entity));
}

// GameFrame constructor.
GameFrame::GameFrame()
{
    font.loadFromFile("Fonts/8bitfont.ttf");
    srand(time(NULL));
}

// Handles all the collision in the game frame.
void GameFrame::frameHandleCollision()
{
    // Collision is handled by first testing for collision between all the
    // entity objects, and then between all entities and asteroids.
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        // Test for collision with the current entity and the remaining
        // entities.
        for (auto remIt = it+1; remIt != entities.end(); ++remIt)
        {
            Entity &curEntity = **it;       // Current entitiy.
            Entity &remEntity = **remIt;    // Remainding entitiy.
            if (curEntity.testCollision(remEntity))
            {
                curEntity.handleCollision(remEntity);
                remEntity.handleCollision(curEntity);
            }
        }

        // Test for collision with the current entities and all the asteroids.
        for (auto astIt = asteroids.begin(); astIt != asteroids.end(); ++astIt)
        {
            Entity &curEntity = **it;       // Current entitiy.
            Entity &astEntity = **astIt;    // Asteroid entitiy.
            if (curEntity.testCollision(astEntity))
            {
                curEntity.handleCollision(astEntity);
                astEntity.handleCollision(curEntity);
            }
        }
    }
}

// Iterates all the elements in the game frame. This method handles the removal
// of entitiy objects.
void GameFrame::frameIterateEntities()
{
    // Set the gamescore if it is unset.
    if (gameOver && gameScore == 0)
    {
        sf::Time scoreTime = scoreClock.getElapsedTime();
        gameScore = scoreTime.asMilliseconds() / 100;
    }

    // Containers of indexes to all the entities that should be destroyed.
    std::vector<size_t> removeEntities;
    std::vector<size_t> removeAsteroids;

    // Iterate all the 'default' entities.
    for (size_t i = 0; i < entities.size(); ++i)
    {
        if (entities.at(i)->iterate())
        {
            if (dynamic_cast<const SpaceShip *>( entities.at(i).get() ))
            {
                gameOver = true;
            }
            removeEntities.push_back(i);
        }
    }

    // Iterate all the asteroids.
    for (size_t i = 0; i < asteroids.size(); ++i)
    {
        if (asteroids.at(i)->iterate())
        {
            removeAsteroids.push_back(i);
        }
    }

    // Remove all the entities that should be removed. The entieies with the
    // greates index should be removed first to keep the all the indexes valid
    // throughout the erasing.
    auto inverter = [](size_t a, size_t b)->bool{ return a > b; };
    std::sort(removeEntities.begin(), removeEntities.end(), inverter);
    std::sort(removeAsteroids.begin(), removeAsteroids.end(), inverter);
    for (size_t index : removeEntities)
    {
        entities.erase(entities.begin() + index);
    }
    for (size_t index : removeAsteroids)
    {
        asteroids.erase(asteroids.begin() + index);
    }

    // Add all the new entities from the buffer container to the 'real'
    // container. Here we separate the asteroids from the ohter entities.
    while (!entitiesBuffer.empty())
    {
        auto current = entitiesBuffer.end() - 1;
        if (dynamic_cast<const Asteroid *>((*current).get()))
        {
            asteroids.push_back(std::move(*current));
        }
        else
        {
            entities.push_back(std::move(*current));
        }
        entitiesBuffer.erase(current);
    }
}

// Spawn enemies in waves,
void GameFrame::frameHandleSpawning()
{
    // If the wavetime (from settings.h) has passed,
    // spawn new enemies and powerups and update difficulty.
    if (waveTimer.getElapsedTime() > waveTime)
    {
	    asteroidFrequency += 0.5;
        asteroidSpeed += 0.5;
        waveTime = sf::seconds(1.05*waveTime.asSeconds());
        powerUpLifeTime = waveTime;
        waveNumber++;
    	for (int i = 0; i < std::ceil(asteroidFrequency); i++)
    	{
    	    spawnAsteroid(asteroidSpeed);
    	}

        for (int n = 0; n <= waveNumber; n++)
        {
            spawnPowerUp();
        }

    	// Start counting towards the next wave.
    	waveTimer.restart();
    }
    // Do nothing if a full wave has not passed yet.
}

void GameFrame::spawnAsteroid(float asteroidSpeed)
{
    int x{};
    int y{};

    // Calculate a random 0-2*PI radian angle,
    // a random 0-2*PI angular velocity,
    // a random 0-3 asteroid size and
    // a random starting edge (0 - left, 1 - up, 2 - right, 3 - down).
    float speedAngle = 2.0f * M_PI * static_cast<float>(std::rand()) / RAND_MAX;
    float rotationSpeed = 3.0f * M_PI * static_cast<float>(std::rand()) / RAND_MAX;
    int size = std::rand() % 4;
    int edge = std::rand() % 4;

    // Decide starting position for the asteroid.
    if (edge == 0)
    {
        x = -DEFAULT_BLIND_SPOT;
	    y = std::rand() % SCREEN_HEIGHT;
    }
    else if (edge == 1)
    {
        x = std::rand() % SCREEN_WIDTH;
        y = -DEFAULT_BLIND_SPOT;
    }
    else if (edge == 2)
    {
        x = SCREEN_WIDTH + DEFAULT_BLIND_SPOT;
        y = std::rand() % SCREEN_HEIGHT;
    }
    else if (edge == 3)
    {
        x = std::rand() % SCREEN_WIDTH;
        y = SCREEN_HEIGHT + DEFAULT_BLIND_SPOT;
    }

    float xSpeed = asteroidSpeed * std::cos(speedAngle);
    float ySpeed = asteroidSpeed * std::sin(speedAngle);

    addEntity(
	std::make_unique<Asteroid>(x, y,
				   xSpeed / sqrt(static_cast<float>(size + 1)),
				   ySpeed / sqrt(static_cast<float>(size + 1)),
				   size, rotationSpeed / size, *this)
    );
}

// Method for getting the first spaceship in the gameframe whos spaceship
// tag is not equal to the tag in the spaceship in parameter.
SpaceShip *GameFrame::getOtherSpaceShip(const SpaceShip *other)
{
    for (std::unique_ptr<Entity> &entity : entities)
    {
        if (SpaceShip *spaceship = dynamic_cast<SpaceShip *>(entity.get()))
        {
            if (spaceship->getId() != other->getId())
            {
                return spaceship;
            }
        }
    }
    return nullptr;
}

sf::Text GameFrame::getScore() const
{
    sf::Text scoreText{};
    scoreText.setFont(font);
    scoreText.setCharacterSize(16); // In pixels, not points.
    scoreText.setPosition(SCREEN_WIDTH/2-10, 10);
    sf::Time time = scoreClock.getElapsedTime();
    scoreText.setString("Score: " + std::to_string(time.asMilliseconds()/100));
    return scoreText;
}

sf::Text GameFrame::getEndScore() const
{
    sf::Text endScore{};
    endScore.setFont(font);
    endScore.setCharacterSize(32);
    endScore.setPosition(SCREEN_WIDTH / 2-200, SCREEN_HEIGHT / 2);
    endScore.setString("SCORE: " + std::to_string(gameScore));
    return endScore;
}

sf::Text GameFrame::getReturnText() const
{
    sf::Text endScore{};
    endScore.setFont(font);
    endScore.setCharacterSize(32);
    endScore.setPosition(SCREEN_WIDTH / 2-200, SCREEN_HEIGHT / 2 - 50);
    endScore.setString("GAME OVER. PRESS 'ENTER' TO RETURN TO THE MENU!");
    return endScore;
}
