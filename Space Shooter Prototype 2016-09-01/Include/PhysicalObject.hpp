#pragma once

#include "Object.hpp"

class CollisionHandler;

class PhysicalObject : public Object
{
public:
                            PhysicalObject(CollisionHandler* collision, Type::Type type);
                            PhysicalObject(CollisionHandler* collision, Type::Type type, const sf::Texture& texture);
                            PhysicalObject(CollisionHandler* collision, Type::Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
    virtual void            collision(PhysicalObject* object) = 0;

public:
    bool                    isDestroyed() const;
    unsigned                getCollisionMatch();
    void                    destroy();

private:
    bool                    m_destroyed;
};