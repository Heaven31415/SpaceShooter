#include "../Include/Game.hpp"
#include "../Include/Pickup.hpp"
#include "../Include/Player.hpp"

Pickup::Pickup(Context * context, World * world, PickupData data)
: PhysicalObject(world, Type::Pickup, context->textures.get(data.textureName))
, m_context(context)
, m_respawnTimer(sf::Time::Zero)
, m_onCollision(data.onCollision)
{
    //setVelocity({ 0, Game::Config.pickupSpeed });
    setVelocity({ 0, data.speed });
    centerOrigin();

    Randomizer random;
    sf::Vector2f mapSize = static_cast<sf::Vector2f>(context->window.getSize());
    sf::Vector2f position = { random.getRealNumber(0.1f * mapSize.x, 0.9f * mapSize.x), -mapSize.y };
    setPosition(position);
}

void Pickup::collision(PhysicalObject * object)
{
    /*if (object->getType() == Type::Player)
    {
        static_cast<Player*>(object)->heal(1);
        destroy();
    }*/

    m_onCollision(this, object);
}

void Pickup::draw(sf::RenderTarget & target) const
{
    if (!isDestroyed())
        Object::draw(target);
}

void Pickup::update(sf::Time dt)
{
    if (!isDestroyed())
    {
        auto dy = getVelocity().y * dt.asSeconds();
        move(0, dy);
    }
}
