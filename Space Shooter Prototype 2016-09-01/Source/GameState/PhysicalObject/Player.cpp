#include "Player.hpp"
#include "../../Game.hpp"

Player::Player(Context& context, World& world, LaserFactory& laserFactory)
: PhysicalObject(context, world, Type::Player, context.textures.get("Ship"))
, m_laserFactory(laserFactory)
, m_frames{ {"straight", {0, 0, 100, 80}}, {"left", { 100, 0, 100, 80 }}, {"right", { 200, 0, 100, 80 }} }
, m_maxWeaponCount(Game::Config.playerMaxWeaponCount)
{
    setMaxVelocity(Game::Config.playerSpeed);
    setMaxHealth(Game::Config.playerHealth);
    setHealth(getMaxHealth());

    setTextureRect(m_frames.at("straight"));
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
            setTextureRect(m_frames.at("straight"));
            centerOrigin();
            break;
        case Player::Frame::Left:
            setTextureRect(m_frames.at("left"));
            centerOrigin();
            break;
        case Player::Frame::Right:
            setTextureRect(m_frames.at("right"));
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
            auto laser = m_laserFactory.build("playerLaser");
            laser->setOwner(this);
            laser->setPosition(getPosition());
            addChild(laser.get());
            getWorld().add(std::move(laser));
            getContext().soundSystem.playSound("PlayerLaser");
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