#include "Object.hpp"
#include "../Game.hpp"

void Object::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform = getTransform();
    target.draw(m_sprite, states);
}

void Object::update(sf::Time dt)
{
    move(m_velocity * dt.asSeconds());
}

Object::Object(Context & context, World & world, Type::Type type)
: m_velocity()
, m_maxVelocity()
, m_context(context)
, m_world(world)
, m_guid()
, m_type(type)
, m_sprite()
, m_erasable(false)
{
    #ifdef _DEBUG
        std::cout << "Object created with " << m_guid << '\n';
    #endif

    if (m_type != Type::Special)
    {
        float scale = Game::Config.objectScale;
        setScale({ scale, scale });
    }
}

Object::Object(Context & context, World & world, Type::Type type, const sf::Texture & texture)
: Object::Object(context, world, type)
{
    m_sprite.setTexture(texture);
}

Object::Object(Context & context, World & world, Type::Type type, const sf::Texture & texture, const sf::IntRect & rectangle)
: Object::Object(context, world, type, texture)
{
    m_sprite.setTextureRect(rectangle);
}

Object::~Object()
{
    #ifdef _DEBUG
        std::cout << "Object destroyed with " << m_guid << '\n';
    #endif
}

Context & Object::getContext()
{
    return m_context;
}

World & Object::getWorld()
{
    return m_world;
}

GUID Object::getGUID() const
{
    return m_guid;
}

Type::Type Object::getType() const
{
    return m_type;
}

sf::FloatRect Object::getLocalBounds() const
{
    return m_sprite.getLocalBounds();
}

sf::FloatRect Object::getGlobalBounds() const
{
    return getTransform().transformRect(m_sprite.getLocalBounds());
}

void Object::setTexture(const sf::Texture & texture)
{
    m_sprite.setTexture(texture);
}

const sf::Texture * Object::getTexture() const
{
    return m_sprite.getTexture();
}

void Object::setTextureRect(const sf::IntRect & rectangle)
{
    m_sprite.setTextureRect(rectangle);
}

const sf::IntRect & Object::getTextureRect() const
{
    return m_sprite.getTextureRect();
}

void Object::setColor(const sf::Color & color)
{
    m_sprite.setColor(color);
}

sf::Color Object::getColor() const
{
    return m_sprite.getColor();
}

void Object::centerOrigin()
{
    auto bounds = m_sprite.getGlobalBounds();
    setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
}

void Object::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

sf::Vector2f Object::getVelocity() const
{
    return m_velocity;
}

void Object::setMaxVelocity(sf::Vector2f velocity)
{
    m_maxVelocity = velocity;
}

sf::Vector2f Object::getMaxVelocity() const
{
    return m_maxVelocity;
}

void Object::erase()
{
    m_erasable = true;
}

bool Object::isErasable() const
{
    return m_erasable;
}