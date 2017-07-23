#pragma once

#include "Object.hpp"

class CollisionHandler;

class PhysicalObject : public Object
{
public:
    typedef std::unique_ptr<PhysicalObject> Ptr;

                            PhysicalObject(CollisionHandler* collision, Type::Type type);
                            PhysicalObject(CollisionHandler* collision, Type::Type type, const sf::Texture& texture);
                            PhysicalObject(CollisionHandler* collision, Type::Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
                            ~PhysicalObject();
    virtual void            collision(PhysicalObject* object) = 0;

public:
    bool                    isDestroyed() const;
    unsigned                getCollisionMatch();
    void                    destroy();

protected:
    CollisionHandler*       m_collision;

private:
    bool                    m_destroyed;
};