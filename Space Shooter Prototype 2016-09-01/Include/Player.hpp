#pragma once

#include "LaserHandler.hpp"
#include "Observer.hpp"

namespace Event
{
    enum Type
    {
        EnemyKilled
    };
}

class Player : public PhysicalObject, public Subject
{
    enum class Status
    {
        Alive,
        DeadWithLasers,
        DeadWithoutLasers,
    };
public:
                                        Player(Context* context, CollisionHandler* collision);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const;
    virtual void                        update(sf::Time dt) override;
    void                                handleEvent(const sf::Event& event);

    std::size_t                         getHealth() const;
    void                                enemyKilled();
    void                                updateStatus();
    void                                updatePlayer(sf::Time dt);
    void                                heal(std::size_t amount);

private:
    Status                              m_status;
    Context*                            m_context;
    LaserHandler::Ptr                   m_laserHandler;

private:
    std::map<std::string, sf::IntRect>  m_frames;
    sf::Vector2f                        m_velocity;
    bool                                m_goingUp;
    bool                                m_goingDown;
    bool                                m_turningLeft;
    bool                                m_turningRight;
    std::size_t                         m_health;
    const std::size_t                   m_maxHealth;
};