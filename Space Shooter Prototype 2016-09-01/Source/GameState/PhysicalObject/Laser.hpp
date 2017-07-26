#pragma once

#include "CollisionHandler.hpp"
#include "Context.hpp"
#include "PhysicalObject.hpp"

class Player;

class Laser : public PhysicalObject
{
public:
                                        Laser(Type::Type type, Context* context, World* world, Object* owner);
                                        ~Laser();
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const override;
    virtual void                        update(sf::Time dt) override;

private:
    void                                updateLaser(sf::Time dt);

private:
    Context*                            m_context;
    World*                              m_world;
    Object*                             m_owner;
    std::map<std::string, sf::IntRect>  m_frames;
};