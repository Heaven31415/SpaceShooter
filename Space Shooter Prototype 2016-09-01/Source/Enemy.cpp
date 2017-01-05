#include "../Include/Enemy.hpp"

Enemy::Enemy(Context* context, CollisionHandler* collision)
: PhysicalObject(collision, Type::Enemy, context->textures.get("EnemyShip"))
, m_status(Status::Alive)
, m_context(context)
, m_laserHandler()
, m_velocity({ 150.f, 200.f })
, m_attackTimer(sf::Time::Zero)
, m_maneuverTimer(sf::Time::Zero)
, m_turningLeft(false)
, m_turningRight(false)
, m_laserAttack(context->sounds.get("EnemyLaser"))
, m_explosion(context->sounds.get("Explosion"))
{
    m_laserHandler = std::make_unique<LaserHandler>(context, collision, this);
    centerOrigin();

    Randomizer random;
    sf::Vector2f mapSize = static_cast<sf::Vector2f>(context->window.getSize());
    sf::Vector2f position = { random.getRealNumber(50.f, mapSize.x-50.f), random.getRealNumber(-mapSize.y / 4.f, 0.f) };
    setPosition(position);

    m_attackTimer = sf::seconds(random.getRealNumber(0.5f, 1.0f));
    m_maneuverTimer = sf::seconds(random.getRealNumber(0.3f, 1.0f));
}

void Enemy::collision(PhysicalObject* object)
{
    destroy();
    m_explosion.play();
}

void Enemy::draw(sf::RenderTarget & target) const
{
    switch (m_status)
    {
        case Status::Alive:
        {
            m_laserHandler->draw(target);
            Object::draw(target);
        }
        break;

        case Status::DeadWithLasers:
        {
            m_laserHandler->draw(target);
        }
        break;
    }
}

void Enemy::update(sf::Time dt)
{
    updateStatus();

    switch (m_status)
    {
        case Status::Alive:
        {
            updateEnemy(dt);
            m_laserHandler->update(dt);
        }
        break;

        case Status::DeadWithLasers:
        {
            m_laserHandler->update(dt);
        }
        break;

        case Status::DeadWithoutLasers:
        {
            if (!isDestroyed()) destroy();
        }
        break;
    }
}

void Enemy::updateStatus()
{
    if (!isDestroyed()) m_status = Status::Alive;
    else if (isDestroyed() && !m_laserHandler->empty()) m_status = Status::DeadWithLasers;
    else if (m_explosion.getStatus() == sf::Sound::Status::Playing) m_status = Status::DeadWithLasers;
    else m_status = Status::DeadWithoutLasers;
}

void Enemy::updateEnemy(sf::Time dt)
{
    Randomizer random;
    m_maneuverTimer -= dt;
    m_attackTimer -= dt;

    if (m_attackTimer <= sf::Time::Zero)
    {
        if (m_laserHandler->push(Type::EnemyWeapon))
            m_laserAttack.play();
        m_attackTimer = sf::seconds(random.getRealNumber(0.5f, 1.0f));
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
    auto mapSize = m_context->window.getSize();

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

bool Enemy::readyToErase() const
{
    return m_status == Status::DeadWithoutLasers;
}