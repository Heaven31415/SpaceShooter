#include "..\Include\EnemyState.hpp"
#include "..\Include\World.hpp"

EnemyChasing::EnemyChasing()
: m_distance(300.f)
{
}

void EnemyChasing::update(Enemy * enemy, sf::Time dt)
{
    Player* player = enemy->getWorld()->getNearestPlayer();
    // when player was found and still too far to be attacked by enemy
    if (player && ts::calculateDistance(player->getPosition(), enemy->getPosition()) > m_distance)
    {
        enemy->move(0.f, enemy->getVelocity().y * dt.asSeconds());
    }
    else
        enemy->changeState(EnemyState::HorizontalPositioning);
}

EnemyHorizontalPositioning::EnemyHorizontalPositioning()
: m_distance(30.f)
{
}

void EnemyHorizontalPositioning::update(Enemy * enemy, sf::Time dt)
{
    Player* player = enemy->getWorld()->getNearestPlayer();
    if (player && std::abs(player->getPosition().x - enemy->getPosition().x) > m_distance)
    {
        if (player->getPosition().x > enemy->getPosition().x)
            enemy->move(100.f * dt.asSeconds(), 0.f);
        else
            enemy->move(-100.f * dt.asSeconds(), 0.f);
    }
    else
        enemy->changeState(EnemyState::Shooting);
}

EnemyShooting::EnemyShooting()
: m_fired(0)
{
}

void EnemyShooting::update(Enemy * enemy, sf::Time dt)
{

}

EnemyEvading::EnemyEvading()
: m_time(sf::seconds(2.f))
{
}

void EnemyEvading::update(Enemy * enemy, sf::Time dt)
{
}

EnemyStateManager::EnemyStateManager()
: m_actual(EnemyState::Chasing)
{
    m_states[EnemyState::Chasing] = std::make_unique<EnemyChasing>();
    m_states[EnemyState::HorizontalPositioning] = std::make_unique<EnemyHorizontalPositioning>();
    m_states[EnemyState::Shooting] = std::make_unique<EnemyShooting>();
    m_states[EnemyState::Evading] = std::make_unique<EnemyEvading>();
}

void EnemyStateManager::changeState(EnemyState::Type state)
{
    m_actual = state;
}

void EnemyStateManager::update(Enemy * enemy, sf::Time dt)
{
    m_states[m_actual]->update(enemy, dt);
}
