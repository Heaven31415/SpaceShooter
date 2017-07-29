#pragma once

#include <map>
#include "Object.hpp"
#include "../Common/Observer.hpp"

class World;

// @todo: find a better place for this
typedef std::map<std::string, sf::IntRect> GraphicsFrames;

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

                            PhysicalObject(Context& context, World& world, Type::Type type);
                            PhysicalObject(Context& context, World& world, Type::Type type, const sf::Texture& texture);
                            PhysicalObject(Context& context, World& world, Type::Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
    virtual                ~PhysicalObject();
    virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void            update(sf::Time dt);
    virtual void            collision(PhysicalObject* object);

public:
    bool                    isDestroyed() const;
    unsigned                getCollisionMatch();
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
    Children                m_children; // @todo: move to object

private:
    std::size_t             m_health;
    std::size_t             m_maxHealth;

private:
    bool                    m_destroyed;
};