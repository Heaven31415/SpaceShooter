#pragma once

#include "Context.hpp"
#include "PhysicalObject.hpp"
#include "Randomizer.hpp"

class World;

typedef std::function<void(PhysicalObject*, PhysicalObject*)> OnCollisionFunc;

struct PickupData
{
    PickupData()
        : speed(0), textureName(""), onCollision() {}
    PickupData(float _speed, std::string _textureName, OnCollisionFunc _onCollision)
        : speed(_speed), textureName(_textureName), onCollision(_onCollision) {}

    float speed;
    std::string textureName;
    OnCollisionFunc onCollision;
};

class Pickup : public PhysicalObject
{
public:
    typedef std::unique_ptr<Pickup> Ptr;

                                        Pickup(Context* context, World* world, PickupData data);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const;
    virtual void                        update(sf::Time dt) override;

private:
    OnCollisionFunc                     m_onCollision;

private:
    Context*                            m_context;
    sf::Time                            m_respawnTimer;
};
