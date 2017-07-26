#include "../Include/Game.hpp"
#include "../Include/Player.hpp"

Player::Player(Context* context, World* world)
: PhysicalObject(world, Type::Player, context->textures.get("Ship"))
, m_context(context)
, m_world(world)
, m_maxWeaponCount(Game::Config.playerMaxLaser)
{
    setVelocity(Game::Config.playerSpeed);
    setMaxHealth(Game::Config.playerHealth);
    setHealth(getMaxHealth());

    m_frames["straight"] = { 0, 0, 100, 80 };
    m_frames["left"] = { 100, 0, 100, 80 };
    m_frames["right"] = { 200, 0, 100, 80 };
    setTextureRect(m_frames["straight"]);
    centerOrigin();
}

void Player::collision(PhysicalObject* object)
{
    // if it's not pickup, we must have collided with something 'unhealthy'
    if (object->getType() == Type::Pickup)
        notify(this, Event::PickupTaken);
    else
        notify(this, Event::TakenDamage);
}

void Player::onEnemyKilled(PhysicalObject * object)
{
    if (object->getType() == Type::Enemy)
        notify(this, Event::EnemyKilled);
}

void Player::setGraphicsFrame(Player::Frame frame)
{
    switch (frame)
    {
        case Player::Frame::Straight:
            setTextureRect(m_frames["straight"]);
            centerOrigin();
            break;
        case Player::Frame::Left:
            setTextureRect(m_frames["left"]);
            centerOrigin();
            break;
        case Player::Frame::Right:
            setTextureRect(m_frames["right"]);
            centerOrigin();
            break;
        default:
            break;
    }
}

void Player::addWeapon(Player::Weapon weapon)
{
    switch (weapon)
    {
        case Player::Weapon::Laser:
        {
            auto laser = std::make_unique<Laser>(Type::PlayerWeapon, m_context, m_world, this);
            addChild(laser.get());
            m_world->add(std::move(laser));
            m_context->soundSystem.playSound("PlayerLaser");
            break;
        }
        default:
            break;
    }
}

std::size_t Player::getWeaponCount()
{
    std::size_t count = 0;
    for (auto& child : m_children)
        if (child->getType() == Type::PlayerWeapon)
            count++;
    return count;
}

bool Player::canAddWeapon()
{
    if (getWeaponCount() < m_maxWeaponCount) return true;
    else return false;
}

void Player::draw(sf::RenderTarget & target) const
{
    if (!isDestroyed())
        Object::draw(target);
}