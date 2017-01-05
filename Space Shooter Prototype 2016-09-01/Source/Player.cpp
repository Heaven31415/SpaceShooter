#include "../Include/Player.hpp"

Player::Player(Context* context, CollisionHandler* collision, Score* scoreKeeper)
: PhysicalObject(Type::Player, context->textures.get("Ship"))
, m_status(Player::Status::Alive)
, m_context(context)
, m_collision(collision)
, m_scoreKeeper(scoreKeeper)
, m_laserHandler(context, collision, this)
, m_velocity({250.f, 350.f})
, m_goingUp(false)
, m_goingDown(false)
, m_turningLeft(false)
, m_turningRight(false)
, m_health(5)
, m_score(0)
, m_laserAttack(context->sounds.get("PlayerLaser"))
, m_damageTaken(context->sounds.get("DamageTaken"))
{
    m_frames["straight"] = { 0, 0, 100, 80 };
    m_frames["left"] = { 100, 0, 100, 80 };
    m_frames["right"] = { 200, 0, 100, 80 };
    setTextureRect(m_frames["straight"]);
    centerOrigin();
}

void Player::collision(PhysicalObject* object)
{
    if (m_health > 0) 
    {
        m_health--;
        m_damageTaken.play();
    }
}

void Player::update(sf::Time dt)
{
    updateStatus();

    switch (m_status)
    {
        case Status::Alive:
        {
            updatePlayer(dt);
            m_laserHandler.update(dt);
        }
        break;

        case Status::DeadWithLasers:
        {
            m_laserHandler.update(dt);
        }
        break;

        case Status::DeadWithoutLasers:
        {
            if (!isDestroyed()) destroy();
        }
        break;
    }
}

void Player::monitor()
{
    m_collision->addTemporary(this);
    m_laserHandler.monitor();
}

void Player::handleEvent(const sf::Event & event)
{
    if (m_status == Status::Alive)
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
                if (m_laserHandler.push(Type::PlayerWeapon))
                    m_laserAttack.play();
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

std::size_t Player::getHealth() const
{
    return m_health;
}

std::size_t Player::getScore() const
{
    return m_score;
}

void Player::enemyKilled()
{
    m_score += 10;
    m_scoreKeeper->setPoints(m_score);
}

void Player::updateStatus()
{
    if (m_health > 0) m_status = Status::Alive;
    else if (m_health == 0 && !m_laserHandler.empty()) m_status = Status::DeadWithLasers;
    else m_status = Status::DeadWithoutLasers;
}

void Player::updatePlayer(sf::Time dt)
{
    auto position = getPosition();
    auto bounds = getLocalBounds();
    auto mapSize = m_context->window.getSize();

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

void Player::draw(sf::RenderTarget & target) const
{
    switch (m_status)
    {
        case Status::Alive:
        {
            m_laserHandler.draw(target);
            Object::draw(target);
        }
        break;

        case Status::DeadWithLasers:
        {
            m_laserHandler.draw(target);
        }
        break;
    }
}