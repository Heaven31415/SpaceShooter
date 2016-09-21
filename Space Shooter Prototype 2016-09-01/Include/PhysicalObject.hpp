#pragma once

#include "Object.hpp"

class PhysicalObject : public Object
{
public:
                            PhysicalObject(Type type);
                            PhysicalObject(Type type, const sf::Texture& texture);
                            PhysicalObject(Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
    virtual void            collision(PhysicalObject* object) = 0;
    virtual void            monitor() = 0;

public:
    bool                    isDestroyed() const;
    void                    destroy();

private:
    bool                    m_destroyed;
};