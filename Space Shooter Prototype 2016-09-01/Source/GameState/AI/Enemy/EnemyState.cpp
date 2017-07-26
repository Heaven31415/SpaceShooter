#include "EnemyState.hpp"
#include "../../World.hpp"
#include "../../PhysicalObject/Enemies/Enemy.hpp"

EnemyChasing::EnemyChasing()
: m_distance(0.f)
{
    Randomizer random;
    m_distance = random.getRealNumber(300.f, 500.f);
}

void EnemyChasing::update(Enemy * enemy, sf::Time dt)
{
    // move vertically to be able to hit player more easily
    Player* player = enemy->getWorld()->getNearestPlayer();
    if (player && std::abs(player->getPosition().y - enemy->getPosition().y) > m_distance)
    {
        enemy->move(0.f, enemy->getVelocity().y * dt.asSeconds());
    }
    else
        enemy->changeState(EnemyState::HorizontalPositioning);
}

EnemyHorizontalPositioning::EnemyHorizontalPositioning()
: m_distance(0.f)
{
    Randomizer random;
    m_distance = random.getRealNumber(5.f, 50.f);
}

void EnemyHorizontalPositioning::update(Enemy * enemy, sf::Time dt)
{
    // move horizontally, to be able to shoot
    Player* player = enemy->getWorld()->getNearestPlayer();
    if (player && std::abs(player->getPosition().x - enemy->getPosition().x) > m_distance)
    {
        if (player->getPosition().x > enemy->getPosition().x)
            enemy->move(enemy->getVelocity().x * dt.asSeconds(), 0.f);
        else
            enemy->move(-enemy->getVelocity().x * dt.asSeconds(), 0.f);
    }
    else
        enemy->changeState(EnemyState::Shooting);
}

EnemyShooting::EnemyShooting()
: m_fired(0)
, m_cooldown(sf::seconds(0.3f))
{
}

void EnemyShooting::update(Enemy * enemy, sf::Time dt)
{
    // you are in good position to shoot, so do it!
    if (m_cooldown <= dt)
    {
        enemy->addLaser();
        m_fired++;
        m_cooldown = sf::seconds(0.3f);
    }
    else
        m_cooldown -= dt;

    if (m_fired == 3)
    {
        m_fired = 0;
        enemy->changeState(EnemyState::Evading);
    }
}

EnemyEvading::EnemyEvading()
: m_time(sf::Time::Zero)
{
    Randomizer random;
    m_time = sf::seconds(random.getRealNumber(1.f, 3.f));
}

void EnemyEvading::update(Enemy * enemy, sf::Time dt)
{
    if (m_time >= dt)
    {
        Player* player = enemy->getWorld()->getNearestPlayer();
        if (player)
        {
            // run away from player, we are trying to evade attacks!
            if (player->getPosition().x < enemy->getPosition().x)
                enemy->move(enemy->getVelocity().x * dt.asSeconds(), 0.f);
            else
                enemy->move(-enemy->getVelocity().x * dt.asSeconds(), 0.f);
        }
    }
    else
        m_time -= dt;

    if (m_time == sf::Time::Zero)
    {
        // after evasive maneuvers, start from beginning
        m_time = sf::seconds(3.f);
        enemy->changeState(EnemyState::Chasing);
    }
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
