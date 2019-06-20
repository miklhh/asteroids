/*
 * Parentclass: Entity
 * Asteroid is initiatied by SingleplayerFrame or MultiplayerFrame. If it collides
 * with a projektil two more asteroids will spawn in its place if it's size is 
 * above 0
 */

#ifndef _ASTEROIDS_ASTEROID_H
#define _ASTEROIDS_ASTEROID_H

#include "Entity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <vector>

class GameFrame;

class Asteroid : public Entity
{
public:
    Asteroid(
            float x, float y, float xSpeed, float ySpeed,
            int size, float rotationSpeed, GameFrame &gameFrame);
    bool iterate() override;
    void handleCollision(const Entity &other);

private:
    GameFrame &gameFrame;
    Animation deathAnimation;
    float xSpeed;
    float ySpeed;
    float rotationSpeed;
    int size;
    bool isAlive{true};
    bool beenHit{false};
};

#endif
