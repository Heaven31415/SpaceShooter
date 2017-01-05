#pragma once

#include "Laser.hpp"

class LaserHandler : public PhysicalObject
{
public:
    typedef std::unique_ptr<LaserHandler> Ptr;

                           LaserHandler(Context* context, CollisionHandler* collision, Object* owner = nullptr, std::size_t maximum = 5);
    bool                   push(Type::Type type);
    bool                   empty() const;

public:
    virtual void           collision(PhysicalObject* object) override;
    virtual void           draw(sf::RenderTarget& target) const override;
    virtual void           update(sf::Time dt) override;

private:
    Context*                m_context;
    CollisionHandler*       m_collision;
    Object*                 m_owner;
    std::vector<Laser::Ptr> m_lasers;
    std::size_t             m_maximum;
};