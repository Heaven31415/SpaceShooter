#include "../Include/CollisionHandler.hpp"

CollisionHandler::CollisionHandler()
: m_objects()
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
    for(auto& objectA : m_objects)
        for (auto& objectB : m_objects)
                if (objectA != objectB && !(objectA->isDestroyed() || objectB->isDestroyed()))
                      if(typeMatch(objectA, objectB))
                        if (collision(objectA, objectB))
                        {
                            objectA->collision(objectB);
                            objectB->collision(objectA);
                        }

    std::experimental::erase_if(m_objects, [](const PhysicalObject* object) { return object->isDestroyed(); }); // lookout
}

void CollisionHandler::registerObject(PhysicalObject * object)
{
    m_objects.push_back(object);
}
