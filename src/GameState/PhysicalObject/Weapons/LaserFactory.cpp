#include "LaserFactory.hpp"

LaserFactory::LaserFactory(Context & context, World & world)
: m_context(context)
, m_world(world)
{
    // define your laser templates here
    m_data["playerLaser"] = LaserData(Type::PlayerWeapon, sf::Vector2f(0.f, -400.f), "LaserRed");
    m_data["enemyLaser"] = LaserData(Type::EnemyWeapon, sf::Vector2f(0.f, 400.f), "LaserGreen");
}

Laser::Ptr LaserFactory::build(std::string name)
{
    auto iterator = m_data.find(name);
    if (iterator != m_data.end())
        return std::make_unique<Laser>(m_context, m_world, iterator->second);
    else // nothing was found
        return nullptr;
}
