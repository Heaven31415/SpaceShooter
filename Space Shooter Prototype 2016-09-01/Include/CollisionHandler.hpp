#pragma once

#include <vector>
#include "Object.hpp"

class CollisionHandler
{
public:
                                CollisionHandler();
    bool                        typeMatch(Object* objectA, Object* objectB);
    bool                        collision(Object* objectA, Object* objectB);
    void                        checkCollision();          
    void                        addPermanent(Object* object);
    void                        addTemporary(Object* object);

private:
    std::vector<Object*>        m_permanentObjects;
    std::vector<Object*>        m_temporaryObjects;
};
