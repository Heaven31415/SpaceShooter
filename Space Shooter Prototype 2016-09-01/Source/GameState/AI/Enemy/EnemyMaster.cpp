#include "EnemyMaster.hpp"
#include "../../World.hpp"
#include "../../PhysicalObject/Enemies/Enemy.hpp"

EnemyMaster::EnemyMaster()
{
    // save union somewhere, bla bla
    m_states[Master::Move] = std::make_unique<EnemyMaster::Move>();
    m_states[Master::Evade] = std::make_unique<EnemyMaster::Evade>();
}

EnemyMaster::Move::Move()
: minDistance(200.f)
, maxDistance(250.f)
{
}

void EnemyMaster::Move::update(Enemy * enemy, sf::Time dt, Message * message)
{
}

EnemyMaster::Evade::Evade()
{
}

void EnemyMaster::Evade::update(Enemy * enemy, sf::Time dt, Message * message)
{
}
