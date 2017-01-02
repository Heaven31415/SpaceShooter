#include "../Include/CollisionHandler.hpp"

CollisionHandler::CollisionHandler()
: m_permanentObjects()
, m_temporaryObjects()
{
}

bool CollisionHandler::typeMatch(PhysicalObject * objectA, PhysicalObject * objectB)
{
    return (objectA->getCollisionMatch() & objectB->getType()) != 0;
}

bool CollisionHandler::collision(PhysicalObject * objectA, PhysicalObject * objectB)
{
    return objectA->getGlobalBounds().intersects(objectB->getGlobalBounds());
}

void CollisionHandler::checkCollision()
{
    for (auto& object : m_permanentObjects)
        object->monitor();
        
    for(auto& objectA : m_temporaryObjects)
        for (auto& objectB : m_temporaryObjects)
                if (objectA != objectB && !(objectA->isDestroyed() || objectB->isDestroyed()))
                      if(typeMatch(objectA, objectB))
                        if (collision(objectA, objectB))
                        {
                            objectA->collision(objectB);
                            objectB->collision(objectA);
                        }

    m_temporaryObjects.clear();
}

void CollisionHandler::addPermanent(PhysicalObject * object)
{
    m_permanentObjects.push_back(object);
}

void CollisionHandler::addTemporary(PhysicalObject * object)
{
    m_temporaryObjects.push_back(object);
}
