#include "..\Include\PickupFactory.hpp"

PickupFactory::PickupFactory(Context * context, World * world)
: m_context(context)
, m_world(world)
{
    // define your pickups templates here
    m_data["heal"] = PickupData(100.f, "Pickup", [](PhysicalObject* pickup, PhysicalObject* collider) {
        if (collider->getType() == Type::Player)
        {
            collider->heal(1);
            pickup->destroy();
        }
            
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
