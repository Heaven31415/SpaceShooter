#include "EnemyAggressor.hpp"
#include "../../World.hpp"
#include "../../PhysicalObject/Enemies/Enemy.hpp"

EnemyAggressor::EnemyAggressor()
{
    m_states[Aggressor::VerticalPositioning] = std::make_unique<EnemyAggressor::VerticalPositioning>();
    m_states[Aggressor::HorizontalPositioning] = std::make_unique<EnemyAggressor::HorizontalPositioning>();
    m_states[Aggressor::Shooting] = std::make_unique<EnemyAggressor::Shooting>();
    m_states[Aggressor::Evading] = std::make_unique<EnemyAggressor::Evading>();
}

EnemyAggressor::VerticalPositioning::VerticalPositioning()
: minDistance(0.f)
, maxDistance(0.f)
{
}

void EnemyAggressor::VerticalPositioning::update(Enemy * enemy, sf::Time dt, Message * message)
{
}

EnemyAggressor::HorizontalPositioning::HorizontalPositioning()
: distance(0.f)
{
}

void EnemyAggressor::HorizontalPositioning::update(Enemy * enemy, sf::Time dt, Message * message)
{
}

EnemyAggressor::Shooting::Shooting()
: fired(0)
, cooldown(sf::seconds(0.3f))
{
}

void EnemyAggressor::Shooting::update(Enemy * enemy, sf::Time dt, Message * message)
{
}

EnemyAggressor::Evading::Evading()
: time(sf::Time::Zero)
{
}

void EnemyAggressor::Evading::update(Enemy * enemy, sf::Time dt, Message * message)
{
}
