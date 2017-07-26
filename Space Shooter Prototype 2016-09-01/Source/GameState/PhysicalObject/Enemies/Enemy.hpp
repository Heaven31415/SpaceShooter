#pragma once

#include "../Weapons/Laser.hpp"
#include "../../PhysicalObject.hpp"
#include "../../AI/Enemy/EnemyState.hpp"
#include "../../../Common/Context.hpp"
#include "../../../Common/Randomizer.hpp"

class EnemyState;
class World;

class Enemy : public PhysicalObject
{
public:
    typedef std::unique_ptr<Enemy> Ptr;
    
                                        Enemy(Context* context, World* world);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const override;
    virtual void                        update(sf::Time dt) override;
    void                                changeState(EnemyState::Type state);
    void                                addLaser();
    std::size_t                         countLasers();

private:
    Context*                            m_context;
    World*                              m_world;

private:
    EnemyStateManager                   m_manager;
};