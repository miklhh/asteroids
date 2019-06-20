#include "Entity.h"
#include "Collision.h"

// Collision detection method. Pixel perfect pixel detection with other
// 'Entity'-objects.
bool Entity::testCollision(const Entity &other, sf::Uint8 alphaLimit) const
{
    return Collision::PixelPerfectTest(*this, other, alphaLimit);
}


// Default constructor.
Entity::Entity(GameFrame &gameFrame)
    : Sprite(), gameFrame(gameFrame)
{

}
