#pragma once

#include "Laser.hpp"
#include <experimental/vector>

class LaserHandler : public PhysicalObject
{
public:
                           LaserHandler(Context* context, CollisionHandler* collision, Object* owner = nullptr, std::size_t maximum = 5);
    bool                   push(Object::Type type);
    bool                   empty() const;

public:
    virtual void           collision(PhysicalObject* object) override;
    virtual void           draw(sf::RenderTarget& target) const override;
    virtual void           update(sf::Time dt) override;
    virtual void           monitor() override;

private:
    Context*                m_context;
    CollisionHandler*       m_collision;
    Object*                 m_owner;
    std::vector<Laser>      m_lasers;
    std::size_t             m_maximum;
};