#include "../Include/LaserHandler.hpp"

LaserHandler::LaserHandler(Context* context, CollisionHandler* collision, Object* owner, std::size_t maximum)
: Object(Type::Handler)
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
    for (auto& laser : m_lasers) laser->draw(target);
}

void LaserHandler::update(sf::Time dt)
{
    std::experimental::erase_if(m_lasers, [](const Laser::Ptr& laser) { return laser->isDestroyed() /*&& laser->readyToErase()*/; });
    for (auto& laser : m_lasers) laser->update(dt);
}

bool LaserHandler::push(Type::Type type)
{
    if (m_lasers.size() < m_maximum) 
    {
        auto laser = std::make_unique<Laser>(type, m_context, m_collision, m_owner);
        m_lasers.push_back(std::move(laser));
        return true;
    }
    else return false;
}

bool LaserHandler::empty() const
{
    return m_lasers.empty();
}