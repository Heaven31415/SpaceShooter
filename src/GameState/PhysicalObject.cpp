#include "PhysicalObject.hpp"
#include "World.hpp"

PhysicalObject::PhysicalObject(Context& context, World& world, Type::Type type)
: Object(context, world, type)
, m_health(1)
, m_maxHealth(1)
, m_destroyed(false)
{
    getWorld().getCollision()->registerObject(this);
}

PhysicalObject::PhysicalObject(Context& context, World& world, Type::Type type, const sf::Texture & texture)
: Object(context, world, type, texture)
, m_health(1)
, m_maxHealth(1)
, m_destroyed(false)
{
    getWorld().getCollision()->registerObject(this);
}

PhysicalObject::PhysicalObject(Context& context, World& world, Type::Type type, const sf::Texture & texture, const sf::IntRect & rectangle)
: Object(context, world, type, texture, rectangle)
, m_health(1)
, m_maxHealth(1)
, m_destroyed(false)
{
    getWorld().getCollision()->registerObject(this);
}

PhysicalObject::~PhysicalObject()
{
    // automatically remove object from collision system at it's destruction
    getWorld().getCollision()->unregisterObject(this);
}

void PhysicalObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    if (!isDestroyed())
        Object::draw(target, states);
}

void PhysicalObject::update(sf::Time dt)
{
    if (!isDestroyed())
        Object::update(dt);
}

void PhysicalObject::collision(PhysicalObject * object)
{
    notify(this, Event::Collided);
}

bool PhysicalObject::isDestroyed() const
{
    // does object exist in the game world
    return m_destroyed;
}

unsigned PhysicalObject::getCollisionMatch()
{
    // check whether two kinds of objects should collide
    switch (getType())
    {
        case Type::Player:
            return Type::Enemy + Type::EnemyWeapon;
        case Type::Enemy:
            return Type::Player + Type::PlayerWeapon;
        case Type::EnemyWeapon:
            return Type::Player;
        case Type::PlayerWeapon:
            return Type::Enemy;
        case Type::Pickup:
            return Type::Player;
        default:
            return 0;
    }
    return 0;
}

void PhysicalObject::destroy()
{
    m_destroyed = true;
    // if this object is destroyed, let us check whether
    // it has any children, if no, we can safely erase it
    if (m_children.empty()) erase();
}

void PhysicalObject::setHealth(std::size_t health)
{
    if (health > m_maxHealth) m_health = m_maxHealth;
    else m_health = health;
}

std::size_t PhysicalObject::getHealth() const
{
    return m_health;
}

void PhysicalObject::setMaxHealth(std::size_t health)
{
    m_maxHealth = health;
    if (m_health > m_maxHealth) m_health = m_maxHealth;
}

std::size_t PhysicalObject::getMaxHealth() const
{
    return m_maxHealth;
}

void PhysicalObject::heal(std::size_t amount)
{
    m_health += amount;
    // Quicker than using modulo to cut health 'overflow'?
    if (m_health > m_maxHealth) m_health = m_maxHealth;

    notify(this, Event::Healed);
}

void PhysicalObject::takeDamage(std::size_t amount)
{
    if (m_health > amount)
        m_health -= amount;
    else
    {
        // this object will be destroyed, meaning nobody will have
        // a chance to see it or interact with it
        m_health = 0;
        destroy();
    }

    notify(this, Event::TakenDamage);
}

void PhysicalObject::addChild(GUID guid)
{
    m_children.push_back(guid);
}

void PhysicalObject::removeChild(GUID guid)
{
    for (std::size_t i = 0; i < m_children.size(); i++)
    {
        if (m_children[i] == guid)
        {
            m_children.erase(m_children.begin() + i);
            break;
        }
    }

    // if this object is destroyed and it has no children, 
    // we can delete it from program memory
    if (isDestroyed() && m_children.empty())
        erase(); 
}

PhysicalObject::Children PhysicalObject::getChildren() const
{
    return m_children;
}
