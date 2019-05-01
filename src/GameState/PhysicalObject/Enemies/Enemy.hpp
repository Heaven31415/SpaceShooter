#pragma once

#include "../Weapons/LaserFactory.hpp"
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
    
                                        Enemy(Context& context, World& world, LaserFactory& laserFactory);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        update(sf::Time dt) override;
    void                                changeState(unsigned state);
    void                                addLaser();
    std::size_t                         countLasers();
    void                                setAI(EnemyStateManager::Ptr manager);

private:
    LaserFactory&                       m_laserFactory;
    EnemyStateManager::Ptr              m_manager;
};