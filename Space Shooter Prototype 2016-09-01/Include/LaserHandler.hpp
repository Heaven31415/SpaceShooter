#pragma once

#include "CollisionHandler.hpp"
#include "Laser.hpp"
#include <experimental/vector>

class LaserHandler : public PhysicalObject
{
public:
                           LaserHandler(Context* context, CollisionHandler* collision, std::size_t maximum = 10);
    bool                   push(Laser::Type type, sf::Vector2f position);
    bool                   empty() const;

public:
    virtual void           collision() override;
    virtual void           draw(sf::RenderTarget& target) const override;
    virtual void           update(sf::Time dt) override;
    virtual void           monitor() override;

private:
    Context*                m_context;
    CollisionHandler*       m_collision;
    std::vector<Laser>      m_lasers;
    std::size_t             m_maximum;
};