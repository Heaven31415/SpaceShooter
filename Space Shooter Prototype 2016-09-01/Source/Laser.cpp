#include "../Include/Game.hpp"
#include "../Include/Laser.hpp"
#include "../Include/Player.hpp"

Laser::Laser(Type::Type type, Context* context, CollisionHandler* collision, Object* owner)
: PhysicalObject(collision, type)
, m_status(Laser::Status::Alive)
, m_context(context)
, m_owner(owner)
, m_velocity((type == Type::PlayerWeapon) ? Game::Config.laserSpeed : -Game::Config.laserSpeed)
, m_exploded(false)
, m_explosionTimer(sf::Time::Zero)
{
    if (type == Type::PlayerWeapon)
    {
        auto player = static_cast<Player*>(owner);
        player->increaseLaserCount();
        setTexture(context->textures.get("RedLaser"));
    }
    else
        setTexture(context->textures.get("GreenLaser"));
    

    m_frames["laser"] = { 0, 0, 9, 33 };
    m_frames["explosion"] = { 9, 0, 56, 54 };
    setTextureRect(m_frames["laser"]);

    centerOrigin();
    setPosition(owner->getPosition());
}

Laser::~Laser()
{
     if (getType() == Type::PlayerWeapon)
    {
        auto player = static_cast<Player*>(m_owner);
        player->decreaseLaserCount();
    }
}

void Laser::collision(PhysicalObject* object)
{
    if (m_owner->getType() == Type::Player)
    {
        auto player = static_cast<Player*>(m_owner);
        player->enemyKilled();
    }

    setTextureRect(m_frames["explosion"]);
    centerOrigin();
    destroy();
    m_velocity /= 5.f;
}

void Laser::draw(sf::RenderTarget & target) const
{
    switch (m_status)
    {
        case Status::Alive:
        {
            Object::draw(target);
        }
        break;

        case Status::Explosion:
        {
            Object::draw(target);
        }
        break;

        case Status::Destroyed:
        {

        }
        break;
    }
}

void Laser::update(sf::Time dt)
{
    updateStatus();

    switch (m_status)
    {
        case Status::Alive:
        {
            auto position = getPosition();
            auto bounds = getLocalBounds();
            auto mapSize = static_cast<sf::Vector2f>(Game::Config.windowSize);

            auto up = position.y - bounds.height / 2.f;
            auto down = position.y + bounds.height / 2.f;

            if (up >= mapSize.y || down <= 0) 
            {
                destroy();
                m_exploded = true;
            }
            else move(0, -m_velocity * dt.asSeconds());
        }
        break;

        case Status::Explosion:
        {
            m_explosionTimer += dt;
            if (m_explosionTimer >= sf::seconds(1.f))
            {
                m_exploded = true;
                m_explosionTimer = sf::Time::Zero;
            }
            else
            {
                auto alpha = static_cast<sf::Uint8>(255.f * (1.f - m_explosionTimer.asSeconds()));
                auto scale = 1.f - m_explosionTimer.asSeconds();

                setColor({ 255, 255, 255, alpha });
                setScale(scale, scale);
                move(0, -m_velocity * dt.asSeconds());
            }
        }
        break;

        case Status::Destroyed:
        {
            if (!isDestroyed()) destroy();
        }
        break;
    }
}

void Laser::updateStatus()
{
    if (!isDestroyed()) m_status = Status::Alive;
    else if (isDestroyed() && !m_exploded) m_status = Status::Explosion;
    else m_status = Status::Destroyed;
}

bool Laser::readyToErase() const
{
    return m_status == Status::Destroyed;
}