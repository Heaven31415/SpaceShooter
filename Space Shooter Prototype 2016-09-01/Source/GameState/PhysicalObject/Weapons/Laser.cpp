#include "Laser.hpp"
#include "../../../Game.hpp"
#include "../../PhysicalObject/Player.hpp"

Laser::Laser(Context & context, World & world, LaserData data)
: PhysicalObject(context, world, data.type, context.textures.get(data.textureName))
, m_owner(nullptr)
, m_frames{ {"laser", { 0, 0, 9, 33 }}, {"explosion", { 9, 0, 56, 54 }} }
{
    setVelocity(data.velocity);
    setMaxVelocity(data.velocity);
    setTextureRect(m_frames.at("laser"));
    centerOrigin();
}

Laser::~Laser()
{
    // tell the owner that we no longer exist
     if (m_owner) m_owner->removeChild(this);
}

void Laser::collision(PhysicalObject* object)
{
    destroy();
    object->takeDamage(1);

    if (object->getType() == Type::Enemy && m_owner->getType() == Type::Player)
        static_cast<Player*>(m_owner)->onEnemyKilled(object);
}

void Laser::update(sf::Time dt)
{
    Object::update(dt);

    // check whether laser is still inside map
    auto position = getPosition();
    auto bounds = getGlobalBounds();
    auto mapSize = static_cast<sf::Vector2f>(Game::Config.windowSize);

    auto up = position.y - bounds.height * 0.5f;
    auto down = position.y + bounds.height * 0.5f;

    if (up >= mapSize.y || down <= 0) 
        destroy();
}

void Laser::setOwner(PhysicalObject * owner)
{
    m_owner = owner;
}
