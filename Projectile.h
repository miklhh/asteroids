/*
 * Parentclass: Entity
 * SpaceShip is initiatied by SpaceShip. It will be destroid if it collides with
 * an asteroid of if it travels beyond the edge of the screen. Once initiated 
 * it will travel at a constant velocity in a straight line.
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

class GameFrame;

class Projectile : public Entity
{
public:
    Projectile(float x, float y, float speed, float rotation, GameFrame &parentFrame);
    bool iterate() override;
    void handleCollision(const Entity &other) override;

private:
    float xSpeed{};
    float ySpeed{};
    bool isAlive{};
    GameFrame &gameFrame;
};

#endif
