#include "../Include/Enemy.hpp"
#include "../Include/Game.hpp"

Enemy::Enemy(Context* context, World* world)
: PhysicalObject(world, Type::Enemy, context->textures.get("EnemyShip"))
, m_context(context)
, m_world(world)
, m_manager()
{
    setVelocity(Game::Config.enemySpeed);
    /* for now, they doesn't use configuration for their health
    setMaxHealth(Game::Config.enemyHealth);
    setHealth(getMaxHealth());
    */
    centerOrigin();

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
    m_context->soundSystem.playSound("Explosion");
}

void Enemy::draw(sf::RenderTarget & target) const
{
    if (!isDestroyed())
        Object::draw(target);
}

void Enemy::update(sf::Time dt)
{
    if (!isDestroyed())
        m_manager.update(this, dt);
}

void Enemy::changeState(EnemyState::Type state)
{
    m_manager.changeState(state);
}

void Enemy::addLaser()
{
    auto laser = std::make_unique<Laser>(Type::EnemyWeapon, m_context, m_world, this);
    // create a 'reference' pointer in children container
    addChild(laser.get());
    // move ownership of this laser to world
    m_world->add(std::move(laser));
}

std::size_t Enemy::countLasers()
{
    std::size_t count = 0;
    for (auto& child : m_children)
        if (child->getType() == Type::EnemyWeapon)
            count++;
    return count;
}
