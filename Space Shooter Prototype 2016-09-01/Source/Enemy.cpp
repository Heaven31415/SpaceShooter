#include "../Include/Enemy.hpp"
#include "../Include/Game.hpp"

Enemy::Enemy(Context* context, World* world)
: PhysicalObject(world, Type::Enemy, context->textures.get("EnemyShip"))
, m_context(context)
, m_world(world)
, m_attackTimer(sf::Time::Zero)
, m_maneuverTimer(sf::Time::Zero)
, m_turningLeft(false)
, m_turningRight(false)
, m_maxLasers(Game::Config.enemyMaxLaser)
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

    m_attackTimer = sf::seconds(random.getRealNumber(0.5f, 1.0f));
    m_maneuverTimer = sf::seconds(random.getRealNumber(0.3f, 1.0f));
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
        updateEnemy(dt);
}

void Enemy::updateEnemy(sf::Time dt)
{
    Randomizer random;
    m_maneuverTimer -= dt;
    m_attackTimer -= dt;

    if (m_attackTimer <= sf::Time::Zero)
    {
        if (countLasers() < m_maxLasers)
        {
            addLaser();
            m_context->soundSystem.playSound("EnemyLaser");
            m_attackTimer = sf::seconds(random.getRealNumber(0.5f, 1.0f));
        }
    }

    if (m_maneuverTimer <= sf::Time::Zero)
    {
        m_turningLeft = false;
        m_turningRight = false;

        auto direction = random.getIntNumber(0, 2);
        if (direction == 1) m_turningLeft = true;
        else if (direction == 2) m_turningRight = true;
        m_maneuverTimer = sf::seconds(random.getRealNumber(0.3f, 1.0f));
    }

    auto velocity = getVelocity();
    auto position = getPosition();
    auto bounds = getLocalBounds();
    auto mapSize = Game::Config.windowSize;

    auto up = position.y - bounds.height / 2.f;
    auto down = position.y + bounds.height / 2.f;
    auto left = position.x - bounds.width / 2.f;
    auto right = position.x + bounds.width / 2.f;

    auto dx = velocity.x * dt.asSeconds();
    auto dy = velocity.y * dt.asSeconds();

    if (m_turningLeft && left > 0.f) move(-dx, dy);
    else if (m_turningRight && right < mapSize.x) move(dx, dy);
    else move(0, dy);

    if (up >= mapSize.y) destroy();
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
