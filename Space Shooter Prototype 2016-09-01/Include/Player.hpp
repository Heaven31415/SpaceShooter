#pragma once

#include "Context.hpp"
#include "Observer.hpp"
#include "PhysicalObject.hpp"
#include "Laser.hpp"

class World;

namespace Event
{
    enum Type
    {
        EnemyKilled,
        LaserWeaponFired,
        PickupTaken,
        PlayerHit,
    };
}

class Player : public PhysicalObject, public Subject
{
public:
                                        Player(Context* context, World* world);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const;
    virtual void                        update(sf::Time dt) override;
    void                                handleEvent(const sf::Event& event);

    void                                increaseLaserCount();
    void                                decreaseLaserCount();

    std::size_t                         getHealth() const;
    void                                enemyKilled();
    void                                updatePlayer(sf::Time dt);
    void                                heal(std::size_t amount);
    void                                takeDamage(std::size_t amount);

private:
    Context*                            m_context;
    World*                              m_world;

private:
    std::map<std::string, sf::IntRect>  m_frames;
    sf::Vector2f                        m_velocity;
    bool                                m_goingUp;
    bool                                m_goingDown;
    bool                                m_turningLeft;
    bool                                m_turningRight;
    std::size_t                         m_health;
    const std::size_t                   m_maxHealth;
    std::size_t                         m_lasers;
    const std::size_t                   m_maxLasers;
};