#include "../Include/Game.hpp"
#include "../Include/Player.hpp"

Player::Player(Context* context, World* world)
: PhysicalObject(world, Type::Player, context->textures.get("Ship"))
, m_context(context)
, m_goingUp(false)
, m_goingDown(false)
, m_turningLeft(false)
, m_turningRight(false)
, m_maxLasers(Game::Config.playerMaxLaser)
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
            switch (event.key.code)
            {
                case sf::Keyboard::W: m_goingUp = true;         break;
                case sf::Keyboard::S: m_goingDown = true;       break;
                case sf::Keyboard::A: m_turningLeft = true;     break;
                case sf::Keyboard::D: m_turningRight = true;    break;
                case sf::Keyboard::Space:
                    if (countLasers() < m_maxLasers)
                    {
                        addLaser();
                        notify(this, Event::WeaponFired);
                    }
                    break;
                default:
                    break;
            }            
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W: m_goingUp = false;         break;
                case sf::Keyboard::S: m_goingDown = false;       break;
                case sf::Keyboard::A: m_turningLeft = false;     break;
                case sf::Keyboard::D: m_turningRight = false;    break;
                default:
                    break;
            }
        }
    }
}

void Player::onEnemyKilled(PhysicalObject * object)
{
    if (object->getType() == Type::Enemy)
        notify(this, Event::EnemyKilled);
}

void Player::addLaser()
{
    auto laser = std::make_unique<Laser>(Type::PlayerWeapon, m_context, m_world, this);
    // create a 'reference' pointer in children container
    addChild(laser.get());
    // move ownership of this laser to world
    m_world->add(std::move(laser));
}

void Player::updatePlayer(sf::Time dt)
{
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

std::size_t Player::countLasers()
{
    std::size_t count = 0;
    for (auto& child : m_children)
        if (child->getType() == Type::PlayerWeapon)
            count++;
    return count;
}

void Player::draw(sf::RenderTarget & target) const
{
    if (!isDestroyed())
        Object::draw(target);
}