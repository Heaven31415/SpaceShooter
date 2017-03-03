#pragma once

#include "LaserHandler.hpp"
#include "Randomizer.hpp"

class Enemy : public PhysicalObject
{
public:
    typedef std::unique_ptr<Enemy> Ptr;
    enum class Status
    {
        Alive,
        DeadWithLasers,
        DeadWithoutLasers,
    };
                                        Enemy(Context* context, CollisionHandler* collision);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const override;
    virtual void                        update(sf::Time dt) override;

    void                                updateStatus();
    void                                updateEnemy(sf::Time dt);
    bool                                readyToErase() const;

private:
    Status                              m_status;
    Context*                            m_context;
    LaserHandler::Ptr                   m_laserHandler;

private:
    sf::Vector2f                        m_velocity;
    sf::Time                            m_attackTimer;
    sf::Time                            m_maneuverTimer;
    bool                                m_turningLeft;
    bool                                m_turningRight;
};