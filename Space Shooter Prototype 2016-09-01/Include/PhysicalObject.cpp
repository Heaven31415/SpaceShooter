#include "PhysicalObject.hpp"

PhysicalObject::PhysicalObject(Type type)
: Object(type)
, m_destroyed(false)
{
}

PhysicalObject::PhysicalObject(Type type, const sf::Texture & texture)
: Object(type, texture)
, m_destroyed(false)
{
}

PhysicalObject::PhysicalObject(Type type, const sf::Texture & texture, const sf::IntRect & rectangle)
: Object(type, texture, rectangle)
, m_destroyed(false)
{
}

bool PhysicalObject::isDestroyed() const
{
    return m_destroyed;
}

void PhysicalObject::destroy()
{
    m_destroyed = true;
}
