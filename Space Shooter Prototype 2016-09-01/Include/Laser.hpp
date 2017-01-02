#pragma once

#include "CollisionHandler.hpp"
#include "Context.hpp"
#include "PhysicalObject.hpp"

class Player;

class Laser : public PhysicalObject
{
    enum class Status
    {
        Alive,
        Explosion,
        Destroyed,
    };
public:
                                        Laser(Type::Type type, Context* context, CollisionHandler* collision, Object* owner);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const override;
    virtual void                        update(sf::Time dt) override;
    virtual void                        monitor() override;

    void                                updateStatus();
    bool                                readyToErase() const;

private:
    Status                              m_status;
    Context*                            m_context;
    CollisionHandler*                   m_collision;
    Object*                             m_owner;
    float                               m_velocity;
    bool                                m_exploded;
    std::map<std::string, sf::IntRect>  m_frames;
    sf::Time                            m_explosionTimer;
};