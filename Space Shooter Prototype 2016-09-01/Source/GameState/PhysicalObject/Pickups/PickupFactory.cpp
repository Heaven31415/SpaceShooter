#include "PickupFactory.hpp"
#include "../../World.hpp"

PickupFactory::PickupFactory(Context & context, World & world)
: m_context(context)
, m_world(world)
{
    // define your pickups templates here
    m_data["heal"] = PickupData(100.f, "PickupGreen", [](PhysicalObject* pickup, PhysicalObject* collider) {
        if (collider->getType() == Type::Player)
        {
            collider->heal(1);
            pickup->destroy();
        }
    });

    m_data["death"] = PickupData(200.f, "PickupRed", [](PhysicalObject* pickup, PhysicalObject* collider) {
        //auto enemies = world->getNearestpObjectsWithType(pickup->getPosition(), 1000.f, Type::Enemy);
        //for (auto& enemyPtr : enemies)
            //enemyPtr->destroy();
        //pickup->destroy();
    });
    
}

PhysicalObject::Ptr PickupFactory::build(std::string name)
{
    auto iterator = m_data.find(name);
    if (iterator != m_data.end())
    {
        PhysicalObject::Ptr pickup = std::make_unique<Pickup>(m_context, m_world, iterator->second);
        return pickup;
    }
    else // nothing was found
        return nullptr;
}
