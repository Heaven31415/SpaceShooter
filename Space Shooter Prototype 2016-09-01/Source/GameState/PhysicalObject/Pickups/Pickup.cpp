#include "Pickup.hpp"
#include "../../../Game.hpp"
#include "../../PhysicalObject/Player.hpp"

Pickup::Pickup(Context & context, World & world, PickupData data)
: PhysicalObject(context, world, Type::Pickup, context.textures.get(data.textureName))
, m_respawnTimer(sf::Time::Zero)
, m_onCollision(data.onCollision)
{
    setVelocity({ 0, data.speed });
    centerOrigin();

    Randomizer random;
    sf::Vector2f mapSize = static_cast<sf::Vector2f>(context.window.getSize());
    sf::Vector2f position = { random.getRealNumber(0.1f * mapSize.x, 0.9f * mapSize.x), -mapSize.y };
    setPosition(position);
}

void Pickup::collision(PhysicalObject * object)
{
    m_onCollision(this, object);
}
