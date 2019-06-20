/*
 * Entity base class. An entity is a renderable game object. It inherits all
 * functionality from the SFML sprite class. Futher, all entities support
 * collision detection in the asteroids game.
 */

#ifndef _ASTEROIDS_ENTITY_H
#define _ASTEROIDS_ENTITY_H

#include <SFML/Graphics/Sprite.hpp>
#include "Collision.h"

class GameFrame;

class Entity : public sf::Sprite
{
public:
    // Method for pixel perfect collision detection with other 'Entity'-objects.
    bool testCollision(const Entity &other, sf::Uint8 alphaLimit = 0) const;

    // Method for handling collision with other 'Entity'-objects. Every 'Entity'
    // object handles themself in their resprective 'handleCollision' method,
    // and does not affect any other 'Entity'.
    virtual void handleCollision(const Entity &other) = 0;

    // Method for iterating the 'Entity'. This method will be called one time
    // each iteration in the 'game-loop'. This method should return true if it
    // wants to be destroyed after iterating kand false otherwise.
    virtual bool iterate() = 0;

    // Virtual destructor.
    virtual ~Entity() = default;

protected:
    // Entity is not instanciatable, protected constructor.
    Entity(GameFrame &gameFrame);

    // Reference to frame in which the intance of the entity is held.
    GameFrame &gameFrame;
};

#endif
