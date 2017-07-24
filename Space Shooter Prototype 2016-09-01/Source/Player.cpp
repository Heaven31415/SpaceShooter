#include "../Include/Game.hpp"
#include "../Include/Player.hpp"

Player::Player(Context* context, World* world)
: PhysicalObject(world->getCollision(), Type::Player, context->textures.get("Ship"))
, m_context(context)
, m_world(world)
, m_velocity(Game::Config.playerSpeed)
, m_goingUp(false)
, m_goingDown(false)
, m_turningLeft(false)
, m_turningRight(false)
, m_health(Game::Config.playerHealth)
, m_maxHealth(m_health)
, m_lasers(0)
, m_maxLasers(Game::Config.playerMaxLaser)
{
    m_frames["straight"] = { 0, 0, 100, 80 };
    m_frames["left"] = { 100, 0, 100, 80 };
    m_frames["right"] = { 200, 0, 100, 80 };
    setTextureRect(m_frames["straight"]);
    centerOrigin();
}

void Player::collision(PhysicalObject* object)
{
    if (object->getType() == Type::Pickup)
        notify(this, Event::PickupTaken);
    else
        takeDamage(1);  
}

void Player::update(sf::Time dt)
{
    if (!isDestroyed())
        updatePlayer(dt);
}

void Player::handleEvent(const sf::Event & event)
{
    if (!isDestroyed())
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W)
                m_goingUp = true;
            else if (event.key.code == sf::Keyboard::S)
                m_goingDown = true;
            else if (event.key.code == sf::Keyboard::A)
                m_turningLeft = true;
            else if (event.key.code == sf::Keyboard::D)
                m_turningRight = true;
            else if (event.key.code == sf::Keyboard::Space)
            {
                if (m_lasers < m_maxLasers)
                {
                    m_world->add(std::make_unique<Laser>(Type::PlayerWeapon, m_context, m_collision, this));
                    notify(this, Event::LaserWeaponFired);
                }
            }                   
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::W)
                m_goingUp = false;
            else if (event.key.code == sf::Keyboard::S)
                m_goingDown = false;
            else if (event.key.code == sf::Keyboard::A)
                m_turningLeft = false;
            else if (event.key.code == sf::Keyboard::D)
                m_turningRight = false;
        }
    }
}

void Player::increaseLaserCount()
{
    m_lasers++;
}

void Player::decreaseLaserCount()
{
    // if this object and last laser is destroyed
    // we can safely erase this object from the world
    // because nobody is having any reference/pointer to it
    if (isDestroyed() && m_lasers == 1)
        erase();

    m_lasers--;
}

std::size_t Player::getHealth() const
{
    return m_health;
}

void Player::enemyKilled()
{
    notify(this, Event::EnemyKilled);
}

void Player::updatePlayer(sf::Time dt)
{
    auto position = getPosition();
    auto bounds = getLocalBounds();
    auto mapSize = Game::Config.windowSize;

    auto up = position.y - bounds.height / 2.f;
    auto down = position.y + bounds.height / 2.f;
    auto left = position.x - bounds.width / 2.f;
    auto right = position.x + bounds.width / 2.f;

    auto dx = m_velocity.x * dt.asSeconds();
    auto dy = m_velocity.y * dt.asSeconds();

    if (m_turningLeft)
    {
        setTextureRect(m_frames["left"]);
        if (left > 0.f) move(-dx, 0);
    }
    else if (m_turningRight)
    {
        setTextureRect(m_frames["right"]);
        if (right < mapSize.x) move(dx, 0);
    }
    else setTextureRect(m_frames["straight"]);

    if (m_goingUp && up > 0.f)
        move(0, -dy);
    else if (m_goingDown && down < mapSize.y)
        move(0, dy);
}

void Player::heal(std::size_t amount)
{
    m_health += amount;
    if (m_health > m_maxHealth) m_health = m_maxHealth;
}

void Player::takeDamage(std::size_t amount)
{
    if (m_health > amount) m_health -= amount;
    else
    {
        // Object is destroyed when health is equal to 0, but it may not be erasable.
        // For example lasers of this object may still exist in the world and we
        // must wait until they are cleaned before we can erase this object.
        m_health = 0;
        destroy();
        // destroying this object implies removing it from collision system,
        // however this object will still remain in world
    }
        
    notify(this, Event::PlayerHit);
}

void Player::draw(sf::RenderTarget & target) const
{
    if (!isDestroyed())
        Object::draw(target);
}