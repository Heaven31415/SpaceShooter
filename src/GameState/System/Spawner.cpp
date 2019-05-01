#include "Spawner.hpp"

Spawner::Spawner(Context * context, World * world)
: m_context(context)
, m_world(world)
, m_actions()
, m_nextActionTimer(sf::Time::Zero)
{
}

void Spawner::update(sf::Time dt)
{
    if (!m_actions.empty())
    {
        if (m_actions.front().time >= m_nextActionTimer + dt)
        {
            m_actions.front().spawn();
            m_actions.pop();
            m_nextActionTimer = sf::Time::Zero;
        }
        else
            m_nextActionTimer += dt;
    }
}
