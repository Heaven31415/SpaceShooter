#pragma once

#include "Context.hpp"
#include "Laser.hpp"
#include "PhysicalObject.hpp"
#include "Randomizer.hpp"

class World;

class Enemy : public PhysicalObject
{
public:
    typedef std::unique_ptr<Enemy> Ptr;
    
                                        Enemy(Context* context, World* world);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const override;
    virtual void                        update(sf::Time dt) override;

    void                                updateEnemy(sf::Time dt);

private:
    Context*                            m_context;
    World*                              m_world;

private:
    void                                addLaser();
    std::size_t                         countLasers();

private:
    sf::Time                            m_attackTimer;
    sf::Time                            m_maneuverTimer;
    bool                                m_turningLeft;
    bool                                m_turningRight;
    const std::size_t                   m_maxLasers;
};