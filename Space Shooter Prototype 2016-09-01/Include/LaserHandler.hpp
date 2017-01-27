#pragma once

#include "Laser.hpp"

class LaserHandler : public Object
{
public:
    typedef std::unique_ptr<LaserHandler> Ptr;

                           LaserHandler(Context* context, CollisionHandler* collision, Object* owner, std::size_t maximum);
    bool                   push(Type::Type type);
    bool                   empty() const;

public:
    virtual void           draw(sf::RenderTarget& target) const override;
    virtual void           update(sf::Time dt) override;

private:
    Context*                m_context;
    CollisionHandler*       m_collision;
    Object*                 m_owner;
    std::vector<Laser::Ptr> m_lasers;
    std::size_t             m_maximum;
};