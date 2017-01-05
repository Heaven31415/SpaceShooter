#include "../Include/EnemyHandler.hpp"

EnemyHandler::EnemyHandler(Context* context, CollisionHandler* collision)
: PhysicalObject(collision, Type::Handler)
, m_context(context)
, m_collision(collision)
, m_enemies()
, m_spawnTimer(sf::Time::Zero)
, m_maximum(10)
{
    m_enemies.reserve(m_maximum);
}

void EnemyHandler::draw(sf::RenderTarget& target) const
{
    for (auto& enemy : m_enemies) enemy->draw(target);
}

void EnemyHandler::collision(PhysicalObject* object)
{
}

void EnemyHandler::update(sf::Time dt)
{
    m_spawnTimer += dt;
    if (m_spawnTimer >= sf::seconds(1.f))
    {
        if (m_enemies.size() < m_maximum)
        {
            auto enemy = std::make_unique<Enemy>(m_context, m_collision);
            m_enemies.push_back(std::move(enemy));
        }
        m_spawnTimer = sf::Time::Zero;
    }

    std::experimental::erase_if(m_enemies, [](Enemy::Ptr& enemy) { return enemy->isDestroyed() && enemy->readyToErase(); });
    for (auto& enemy : m_enemies) enemy->update(dt);
}