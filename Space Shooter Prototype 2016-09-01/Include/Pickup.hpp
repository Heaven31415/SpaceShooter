#pragma once

#include "Context.hpp"
#include "PhysicalObject.hpp"
#include "Randomizer.hpp"

class Pickup : public PhysicalObject
{
public:
    typedef std::unique_ptr<Pickup> Ptr;

                                        Pickup(Context* context, CollisionHandler* collision);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        update(sf::Time dt) override;

private:
    Context*                            m_context;
    sf::Time                            m_respawnTimer;
    float                               m_velocity;
};
