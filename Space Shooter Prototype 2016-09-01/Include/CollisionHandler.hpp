#pragma once

#include <vector>
#include "PhysicalObject.hpp"

class CollisionHandler
{
public:
                                    CollisionHandler();
    bool                            typeMatch(PhysicalObject* objectA, PhysicalObject* objectB);
    bool                            collision(PhysicalObject* objectA, PhysicalObject* objectB);
    void                            checkCollision();          
    void                            addPermanent(PhysicalObject* object);
    void                            addTemporary(PhysicalObject* object);

private:
    std::vector<PhysicalObject*>    m_permanentObjects;
    std::vector<PhysicalObject*>    m_temporaryObjects;
};