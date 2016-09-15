#pragma once

#include "Enemy.hpp"

class EnemyHandler : public PhysicalObject
{
public:
                                EnemyHandler(Context* context, CollisionHandler* collision);
public:
    virtual void                collision() override;
    virtual void                draw(sf::RenderTarget& target) const override;
    virtual void                update(sf::Time dt) override;
    virtual void                monitor() override;

private:
    Context*                    m_context;
    CollisionHandler*           m_collision;
    std::vector<Enemy>          m_enemies;
    sf::Time                    m_spawnTimer;
    const std::size_t           m_maximum;
};