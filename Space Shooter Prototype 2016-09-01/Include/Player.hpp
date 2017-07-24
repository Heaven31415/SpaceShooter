#pragma once

#include "Context.hpp"
#include "Observer.hpp"
#include "PhysicalObject.hpp"
#include "Laser.hpp"

class World;

class Player : public PhysicalObject
{
public:
                                        Player(Context* context, World* world);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const override;
    virtual void                        update(sf::Time dt) override;
    void                                handleEvent(const sf::Event& event);

public:
    void                                onEnemyKilled(PhysicalObject* object); // callback

private:
    void                                addLaser();
    void                                updatePlayer(sf::Time dt);
    std::size_t                         countLasers();

private:
    Context*                            m_context;

private:
    std::map<std::string, sf::IntRect>  m_frames;
    bool                                m_goingUp;
    bool                                m_goingDown;
    bool                                m_turningLeft;
    bool                                m_turningRight;
    const std::size_t                   m_maxLasers;
};