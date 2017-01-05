#include "..\Include\Pickup.hpp"
#include "..\Include\Player.hpp"
#pragma once

Pickup::Pickup(Context * context, CollisionHandler * collision)
: PhysicalObject(collision, Type::Pickup, context->textures.get("Pickup"))
, m_context(context)
, m_respawnTimer(sf::Time::Zero)
, m_velocity(100.f)
{
    centerOrigin();

    Randomizer random;
    sf::Vector2f mapSize = static_cast<sf::Vector2f>(context->window.getSize());
    sf::Vector2f position = { random.getRealNumber(50.f, mapSize.x - 50.f), -mapSize.y };
    setPosition(position);
}

void Pickup::collision(PhysicalObject * object)
{
    if (object->getType() == Type::Player)
    {
        auto player = static_cast<Player*>(object);
        player->heal(1);

        Randomizer random;
        sf::Vector2f mapSize = static_cast<sf::Vector2f>(m_context->window.getSize());
        sf::Vector2f position = { random.getRealNumber(50.f, mapSize.x - 50.f), -mapSize.y };
        setPosition(position);
    }
}

void Pickup::update(sf::Time dt)
{
    auto dy = m_velocity * dt.asSeconds();
    move(0, dy);
}
