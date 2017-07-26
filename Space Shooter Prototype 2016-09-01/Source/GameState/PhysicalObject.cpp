#include "../Include/PhysicalObject.hpp"
#include "../Include/World.hpp"

PhysicalObject::PhysicalObject(World* world, Type::Type type)
: Object(type)
, m_world(world)
, m_health(1)
, m_maxHealth(1)
, m_destroyed(false)
{
    #ifdef _DEBUG
        std::cout << "Physical Object created " << this << '\n';
    #endif
    world->getCollision()->registerObject(this);
}

PhysicalObject::PhysicalObject(World* world, Type::Type type, const sf::Texture & texture)
: Object(type, texture)
, m_world(world)
, m_destroyed(false)
{
    #ifdef _DEBUG
        std::cout << "Physical Object created " << this << '\n';
    #endif
    world->getCollision()->registerObject(this);
}

PhysicalObject::PhysicalObject(World* world, Type::Type type, const sf::Texture & texture, const sf::IntRect & rectangle)
: Object(type, texture, rectangle)
, m_world(world)
, m_destroyed(false)
{
    #ifdef _DEBUG
        std::cout << "Physical Object created " << this << '\n';
    #endif
    world->getCollision()->registerObject(this);
}

PhysicalObject::~PhysicalObject()
{
    #ifdef _DEBUG
        std::cout << "Physical Object destroyed " << this << '\n';
    #endif
    // automatically remove object from collision system at it's destruction
    m_world->getCollision()->unregisterObject(this);
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
        case Type::Pickup:
            return Type::Player;
        default:
            return 0;
    }
    return 0;
}

World * PhysicalObject::getWorld()
{
    return m_world;
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

void PhysicalObject::addChild(PhysicalObject* child)
{
    // add a reference pointer to children container
    m_children.push_back(child);
}

void PhysicalObject::removeChild(PhysicalObject* child)
{
    // search for a reference pointer
    // and delete it if it was found
    for (std::size_t i = 0; i < m_children.size(); i++)
        if (m_children[i] == child)
        {
            m_children.erase(m_children.begin() + i);
            break;
        }

    // if this object is destroyed and it has no children, 
    // we can erase it (delete from program memory)
    if (isDestroyed() && m_children.empty())
        erase(); 
}
