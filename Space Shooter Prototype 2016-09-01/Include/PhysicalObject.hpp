#pragma once

#include "Object.hpp"
#include "Observer.hpp"

class World;

namespace Event
{
    enum Type
    {
        Collided,
        EnemyKilled,
        Healed,
        PickupTaken,
        TakenDamage,
        WeaponFired,
    };
}

class PhysicalObject : public Object, public Subject
{
public:
    typedef std::unique_ptr<PhysicalObject> Ptr;
    typedef std::vector<PhysicalObject*> Children;

                            PhysicalObject(World* world, Type::Type type);
                            PhysicalObject(World* world, Type::Type type, const sf::Texture& texture);
                            PhysicalObject(World* world, Type::Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
    virtual                ~PhysicalObject();
    virtual void            collision(PhysicalObject* object);

public:
    bool                    isDestroyed() const;
    bool                    isErasable() const;
    unsigned                getCollisionMatch();
    void                    destroy();
    void                    erase();

    void                    setVelocity(sf::Vector2f velocity);
    sf::Vector2f            getVelocity() const;
    void                    setHealth(std::size_t health);
    std::size_t             getHealth() const;
    void                    setMaxHealth(std::size_t health);
    std::size_t             getMaxHealth() const;

    void                    heal(std::size_t amount);
    void                    takeDamage(std::size_t amount);

    void                    addChild(PhysicalObject* child);
    void                    removeChild(PhysicalObject* child);

protected:
    World*                  m_world;
    Children                m_children;

private:
    sf::Vector2f            m_velocity;
    std::size_t             m_health;
    std::size_t             m_maxHealth;

private:
    bool                    m_destroyed;
    bool                    m_erasable;
};