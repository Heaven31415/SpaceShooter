#pragma once

#include "Laser.hpp"

class LaserFactory
{
public:
    LaserFactory(Context& context, World& world);
    Laser::Ptr build(std::string name);

private:
    Context&                            m_context;
    World&                              m_world;
    std::map<std::string, LaserData>    m_data;
};
