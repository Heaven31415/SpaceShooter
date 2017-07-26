#pragma once

#include "Object.hpp"
#include "Observer.hpp"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

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
    unsigned                getCollisionMatch();
    World*                  getWorld();
    void                    destroy();

    void                    setHealth(std::size_t health);
    std::size_t             getHealth() const;
    void                    setMaxHealth(std::size_t health);
    std::size_t             getMaxHealth() const;

    void                    heal(std::size_t amount);
    void                    takeDamage(std::size_t amount);

    void                    addChild(PhysicalObject* child); // @todo: move to object
    void                    removeChild(PhysicalObject* child); // @todo: move to object

protected:
    World*                  m_world;
    Children                m_children; // @todo: move to object

private:
    std::size_t             m_health;
    std::size_t             m_maxHealth;

private:
    bool                    m_destroyed;
};