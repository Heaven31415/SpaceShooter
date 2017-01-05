#pragma once

#include "Enemy.hpp"

class EnemyHandler : public PhysicalObject
{
public:
                                EnemyHandler(Context* context, CollisionHandler* collision);
public:
    virtual void                collision(PhysicalObject* object) override;
    virtual void                draw(sf::RenderTarget& target) const override;
    virtual void                update(sf::Time dt) override;

private:
    Context*                    m_context;
    CollisionHandler*           m_collision;
    std::vector<Enemy::Ptr>     m_enemies;
    sf::Time                    m_spawnTimer;
    const std::size_t           m_maximum;
};