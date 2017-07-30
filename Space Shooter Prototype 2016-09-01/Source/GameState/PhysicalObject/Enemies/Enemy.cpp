#include "Enemy.hpp"
#include "../../../Game.hpp"

Enemy::Enemy(Context& context, World& world, LaserFactory& laserFactory)
: PhysicalObject(context, world, Type::Enemy, context.textures.get("EnemyShip"))
, m_laserFactory(laserFactory)
, m_manager(nullptr)
{
    setVelocity({0.f, 0.f});
    setMaxVelocity(Game::Config.enemySpeed);
    /* for now, they doesn't use configuration for their health
    setMaxHealth(Game::Config.enemyHealth);
    setHealth(getMaxHealth());
    */
    centerOrigin();

    // this shouldn't be here
    Randomizer random;
    sf::Vector2f mapSize = static_cast<sf::Vector2f>(Game::Config.windowSize);
    sf::Vector2f position = { random.getRealNumber(1.f/10.f * mapSize.x, 9.f/10.f * mapSize.x), random.getRealNumber(-mapSize.y / 10, 0.f) };
    setPosition(position);
}

void Enemy::collision(PhysicalObject* object)
{
    if (object->getType() == Type::Player)
    {
        object->takeDamage(1);
        takeDamage(1);
    }
    getContext().soundSystem.playSound("Explosion");
}

void Enemy::update(sf::Time dt)
{
    Object::update(dt);

    if (!isDestroyed() && m_manager)
        m_manager->update(this, dt);
}

void Enemy::changeState(unsigned state)
{
    if(m_manager) m_manager->changeState(state);
}

void Enemy::addLaser()
{
    auto laser = m_laserFactory.build("enemyLaser");
    laser->setOwner(this);
    laser->setPosition(getPosition());

    addChild(laser.get());
    getWorld().add(std::move(laser));
}

std::size_t Enemy::countLasers()
{
    std::size_t count = 0;
    for (auto& child : m_children)
        if (child->getType() == Type::EnemyWeapon)
            count++;
    return count;
}

void Enemy::setAI(EnemyStateManager::Ptr manager)
{
    m_manager.swap(manager);
}
