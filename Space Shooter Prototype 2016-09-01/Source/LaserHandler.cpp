#include "../Include/LaserHandler.hpp"

LaserHandler::LaserHandler(Context* context, CollisionHandler* collision, Object* owner, std::size_t maximum)
: PhysicalObject(Object::Type::Handler)
, m_context(context)
, m_collision(collision)
, m_owner(owner)
, m_lasers()
, m_maximum(maximum)
{
    m_lasers.reserve(maximum);
}

void LaserHandler::draw(sf::RenderTarget & target) const
{
    for (auto& laser : m_lasers) laser.draw(target);
}

void LaserHandler::collision(PhysicalObject* object)
{
}

void LaserHandler::update(sf::Time dt)
{
    auto mapSize = static_cast<sf::Vector2f>(m_context->window.getSize());
    std::experimental::erase_if(m_lasers, [](const Laser& laser) { return laser.isDestroyed() && laser.readyToErase(); });
    for (auto& laser : m_lasers) laser.update(dt);
}

void LaserHandler::monitor()
{
    for (auto& laser : m_lasers) laser.monitor();
}

bool LaserHandler::push(Object::Type type)
{
    if (m_lasers.size() < m_maximum) 
    {
        m_lasers.push_back({ type, m_context, m_collision, m_owner });
        return true;
    }
    else return false;
}

bool LaserHandler::empty() const
{
    return m_lasers.empty();
}
