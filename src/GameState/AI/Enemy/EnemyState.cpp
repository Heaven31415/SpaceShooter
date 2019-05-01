#include "EnemyState.hpp"

EnemyStateManager::EnemyStateManager()
: m_actual(0)
, m_states()
, m_message{Message::Type::Int, 0}
{
}

void EnemyStateManager::changeState(unsigned state)
{
    m_actual = state;
}

void EnemyStateManager::update(Enemy * enemy, sf::Time dt)
{
    m_states[m_actual]->update(enemy, dt, &m_message);
}