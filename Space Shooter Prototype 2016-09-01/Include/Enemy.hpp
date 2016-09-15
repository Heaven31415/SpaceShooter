#pragma once

#include "LaserHandler.hpp"
#include "Randomizer.hpp"

class Enemy : public PhysicalObject
{
    enum class Status
    {
        Alive,
        DeadWithLasers,
        DeadWithoutLasers,
    };
public:
                                        Enemy(Context* context, CollisionHandler* collision);
    virtual void                        collision() override;
    virtual void                        draw(sf::RenderTarget& target) const override;
    virtual void                        update(sf::Time dt) override;
    virtual void                        monitor() override;

    void                                updateStatus();
    void                                updateEnemy(sf::Time dt);
    bool                                readyToErase() const;

private:
    Status                              m_status;
    Context*                            m_context;
    CollisionHandler*                   m_collision;
    LaserHandler                        m_laserHandler;

private:
    sf::Vector2f                        m_velocity;
    sf::Time                            m_attackTimer;
    sf::Time                            m_maneuverTimer;
    bool                                m_turningLeft;
    bool                                m_turningRight;
    sf::Sound                           m_laserAttack;
    sf::Sound                           m_explosion;
};