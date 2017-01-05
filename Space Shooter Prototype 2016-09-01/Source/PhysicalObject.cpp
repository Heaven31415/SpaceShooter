#include "../Include/PhysicalObject.hpp"
#include "../Include/CollisionHandler.hpp"

PhysicalObject::PhysicalObject(CollisionHandler* collision, Type::Type type)
: Object(type)
, m_destroyed(false)
{
    collision->registerObject(this);
}

PhysicalObject::PhysicalObject(CollisionHandler* collision, Type::Type type, const sf::Texture & texture)
: Object(type, texture)
, m_destroyed(false)
{
    collision->registerObject(this);
}

PhysicalObject::PhysicalObject(CollisionHandler* collision, Type::Type type, const sf::Texture & texture, const sf::IntRect & rectangle)
: Object(type, texture, rectangle)
, m_destroyed(false)
{
    collision->registerObject(this);
}

bool PhysicalObject::isDestroyed() const
{
    return m_destroyed;
}

unsigned PhysicalObject::getCollisionMatch()
{
    switch (m_type)
    {
        case Type::Player:
            return Type::Enemy + Type::EnemyWeapon;
        case Type::Enemy:
            return Type::Player + Type::PlayerWeapon;
        case Type::EnemyWeapon:
            return Type::Player;
        case Type::PlayerWeapon:
            return Type::Enemy;
        default:
            return 0;
    }
    return 0;
}

void PhysicalObject::destroy()
{
    m_destroyed = true;
}