#include "EnemyDefender.hpp"
#include "../../World.hpp"
#include "../../PhysicalObject/Enemies/Enemy.hpp"

EnemyDefender::EnemyDefender()
{
}

EnemyDefender::Move::Move()
: horizontalDist{10.f, 50.f}
, verticalDist{300.f, 400.f}
{
}

void EnemyDefender::Move::update(Enemy * enemy, sf::Time dt, Message * message)
{
}

EnemyDefender::Search::Search()
{
}

void EnemyDefender::Search::update(Enemy * enemy, sf::Time dt, Message * message)
{
}
