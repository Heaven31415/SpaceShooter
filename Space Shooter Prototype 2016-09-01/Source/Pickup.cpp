#include "../Include/Game.hpp"
#include "../Include/Pickup.hpp"
#include "../Include/Player.hpp"

Pickup::Pickup(Context * context, CollisionHandler * collision)
: PhysicalObject(collision, Type::Pickup, context->textures.get("Pickup"))
, m_context(context)
, m_respawnTimer(sf::Time::Zero)
, m_velocity(Game::Config.pickupSpeed)
{
    centerOrigin();

    Randomizer random;
    sf::Vector2f mapSize = static_cast<sf::Vector2f>(context->window.getSize());
    sf::Vector2f position = { random.getRealNumber(0.1f * mapSize.x, 0.9f * mapSize.x), -mapSize.y };
    setPosition(position);
}

void Pickup::collision(PhysicalObject * object)
{
    if (object->getType() == Type::Player)
    {
        auto player = static_cast<Player*>(object);
        player->heal(1);

        Randomizer random;
        sf::Vector2f mapSize = static_cast<sf::Vector2f>(Game::Config.windowSize);
        sf::Vector2f position = { random.getRealNumber(0.1f * mapSize.x, 0.9f * mapSize.x), -mapSize.y };
        setPosition(position);
    }
}

void Pickup::update(sf::Time dt)
{
    auto dy = m_velocity * dt.asSeconds();
    move(0, dy);
}
