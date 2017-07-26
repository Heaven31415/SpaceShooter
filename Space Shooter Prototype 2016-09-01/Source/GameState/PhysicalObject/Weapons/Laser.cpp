#include "Laser.hpp"
#include "../../../Game.hpp"
#include "../../PhysicalObject/Player.hpp"

Laser::Laser(Type::Type type, Context * context, World * world, Object * owner)
: PhysicalObject(world, type)
, m_context(context)
, m_owner(owner)
{
    sf::Vector2f velocity = { 0, Game::Config.laserSpeed };
    if (type == Type::PlayerWeapon)
    {
        setVelocity(velocity);
        setTexture(context->textures.get("RedLaser"));
    }
    else if (type == Type::EnemyWeapon)
    {
        setVelocity(-velocity);
        setTexture(context->textures.get("GreenLaser"));
    }

    m_frames["laser"] = { 0, 0, 9, 33 };
    m_frames["explosion"] = { 9, 0, 56, 54 };
    setTextureRect(m_frames["laser"]);

    centerOrigin();
    if(owner) setPosition(owner->getPosition());
}

Laser::~Laser()
{
    // tell the owner that we no longer exist
     if (m_owner) static_cast<PhysicalObject*>(m_owner)->removeChild(this);
}

void Laser::collision(PhysicalObject* object)
{
    if (object->getType() == Type::Enemy)
    {
        // tell player that he killed something
        if (m_owner->getType() == Type::Player)
            static_cast<Player*>(m_owner)->onEnemyKilled(object);

        object->takeDamage(1);
    }
    else if (object->getType() == Type::Player)
        object->takeDamage(1);

    destroy();
}

void Laser::draw(sf::RenderTarget & target) const
{
    if (!isDestroyed())
        Object::draw(target);
}

void Laser::update(sf::Time dt)
{
    if (!isDestroyed())
        updateLaser(dt);
}

void Laser::updateLaser(sf::Time dt)
{
    auto velocity = getVelocity();
    auto position = getPosition();
    auto bounds = getLocalBounds();
    auto mapSize = static_cast<sf::Vector2f>(Game::Config.windowSize);

    auto up = position.y - bounds.height / 2.f;
    auto down = position.y + bounds.height / 2.f;

    if (up >= mapSize.y || down <= 0) destroy();
    else move(0, -velocity.y * dt.asSeconds());
}