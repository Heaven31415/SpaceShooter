#include "../Include/EnemyHandler.hpp"

EnemyHandler::EnemyHandler(Context* context, CollisionHandler* collision)
: PhysicalObject(Object::Type::Handler)
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
    for (auto& enemy : m_enemies) enemy.draw(target);
}

void EnemyHandler::collision()
{
}

void EnemyHandler::update(sf::Time dt)
{
    m_spawnTimer += dt;
    if (m_spawnTimer >= sf::seconds(1.f))
    {
        if (m_enemies.size() < m_maximum) m_enemies.push_back({ m_context, m_collision });
        m_spawnTimer = sf::Time::Zero;
    }

    std::experimental::erase_if(m_enemies, [](const Enemy& enemy) { return enemy.isDestroyed() && enemy.readyToErase(); });
    for (auto& enemy : m_enemies) enemy.update(dt);
}

void EnemyHandler::monitor()
{
    for (auto& enemy : m_enemies) enemy.monitor();
}
