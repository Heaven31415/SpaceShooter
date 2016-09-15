#pragma once

#include "LaserHandler.hpp"

class Player : public PhysicalObject
{
    enum class Status
    {
        Alive,
        DeadWithLasers,
        DeadWithoutLasers,
    };
public:
                                        Player(Context* context, CollisionHandler* collision);
    virtual void                        collision() override;
    virtual void                        draw(sf::RenderTarget& target) const;
    virtual void                        update(sf::Time dt) override;
    virtual void                        monitor() override;
    void                                handleEvent(const sf::Event& event);

    std::size_t                         getHealth() const;
    std::size_t                         getScore() const;
    void                                updateStatus();
    void                                updatePlayer(sf::Time dt);

private:
    Status                              m_status;
    Context*                            m_context;
    CollisionHandler*                   m_collision;
    LaserHandler                        m_laserHandler;

private:
    std::map<std::string, sf::IntRect>  m_frames;
    sf::Vector2f                        m_velocity;
    bool                                m_goingUp;
    bool                                m_goingDown;
    bool                                m_turningLeft;
    bool                                m_turningRight;
    std::size_t                         m_health;
    std::size_t                         m_score;
    sf::Sound                           m_laserAttack;
    sf::Sound                           m_damageTaken;
};
