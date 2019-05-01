#pragma once

#include "Pickup.hpp"

class PickupFactory
{
public:
    PickupFactory(Context& context, World& world);
    PhysicalObject::Ptr build(std::string name);

private:
    Context&                            m_context;
    World&                              m_world;
    std::map<std::string, PickupData>   m_data;
};