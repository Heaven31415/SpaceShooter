#include "CollisionHandler.hpp"

CollisionHandler::CollisionHandler()
: m_objects()
{
}

inline bool CollisionHandler::typeMatch(PhysicalObject * objectA, PhysicalObject * objectB)
{
    return (objectA->getCollisionMatch() & objectB->getType()) != 0;
}

inline bool CollisionHandler::collision(PhysicalObject * objectA, PhysicalObject * objectB)
{
    return objectA->getGlobalBounds().intersects(objectB->getGlobalBounds());
}

void CollisionHandler::checkCollision()
{
    for(auto& objectA : m_objects)
        for (auto& objectB : m_objects)
                if (objectA != objectB && !(objectA->isDestroyed() || objectB->isDestroyed()))
                      if(typeMatch(objectA, objectB))
                        if (collision(objectA, objectB))
                        {
                            objectA->collision(objectB);
                            objectB->collision(objectA);
                        }

    // delete "reference" pointers to destroyed objects, but don't delete them (World is their sole owner)
    std::experimental::erase_if(m_objects, [](const PhysicalObject* object) { return object->isDestroyed(); });
}

void CollisionHandler::registerObject(PhysicalObject * object)
{
    m_objects.push_back(object);
}

void CollisionHandler::unregisterObject(PhysicalObject * object)
{
    auto result = std::find(m_objects.begin(), m_objects.end(), object);
    if (result != m_objects.end())
        m_objects.erase(result);
}