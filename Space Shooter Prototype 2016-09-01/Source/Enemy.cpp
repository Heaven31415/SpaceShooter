#include "../Include/Enemy.hpp"
#include "../Include/Game.hpp"

Enemy::Enemy(Context* context, World* world)
: PhysicalObject(world->getCollision(), Type::Enemy, context->textures.get("EnemyShip"))
, m_context(context)
, m_world(world)
, m_velocity(Game::Config.enemySpeed)
, m_attackTimer(sf::Time::Zero)
, m_maneuverTimer(sf::Time::Zero)
, m_turningLeft(false)
, m_turningRight(false)
, m_health(1)
, m_maxHealth(1)
, m_lasers(0)
, m_maxLasers(Game::Config.enemyMaxLaser)
{
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
    if (m_health > 0) m_health -= 1;
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
        if (m_lasers < m_maxLasers)
        {
            m_world->add(std::make_unique<Laser>(Type::PlayerWeapon, m_context, m_collision, this));
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

    auto position = getPosition();
    auto bounds = getLocalBounds();
    auto mapSize = Game::Config.windowSize;

    auto up = position.y - bounds.height / 2.f;
    auto down = position.y + bounds.height / 2.f;
    auto left = position.x - bounds.width / 2.f;
    auto right = position.x + bounds.width / 2.f;

    auto dx = m_velocity.x * dt.asSeconds();
    auto dy = m_velocity.y * dt.asSeconds();

    if (m_turningLeft && left > 0.f) move(-dx, dy);
    else if (m_turningRight && right < mapSize.x) move(dx, dy);
    else move(0, dy);

    if (up >= mapSize.y) destroy();
}