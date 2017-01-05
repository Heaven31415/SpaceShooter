#pragma once

#include <vector>
#include <experimental/vector>
#include "PhysicalObject.hpp"

class CollisionHandler
{
public:
                                    CollisionHandler();
    bool                            typeMatch(PhysicalObject* objectA, PhysicalObject* objectB);
    bool                            collision(PhysicalObject* objectA, PhysicalObject* objectB);
    void                            checkCollision();          
    void                            registerObject(PhysicalObject* object);

private:
    std::vector<PhysicalObject*>    m_objects;
};