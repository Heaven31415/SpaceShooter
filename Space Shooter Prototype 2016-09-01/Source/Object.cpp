#include "../Include/Object.hpp"

void Object::draw(sf::RenderTarget & target) const
{
    target.draw(m_sprite, getTransform());
}

void Object::update(sf::Time dt)
{
}

Object::Object(Type::Type type)
: m_velocity()
, m_type(type)
, m_sprite()
, m_erasable(false)
{
}

Object::Object(Type::Type type, const sf::Texture & texture)
: m_velocity()
, m_type(type)
, m_sprite(texture)
, m_erasable(false)
{
}

Object::Object(Type::Type type, const sf::Texture & texture, const sf::IntRect & rectangle)
: m_velocity()
, m_type(type)
, m_sprite(texture, rectangle)
, m_erasable(false)
{
}

Object::~Object()
{
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

void Object::setTextureRect(const sf::IntRect & rectangle)
{
    m_sprite.setTextureRect(rectangle);
}

void Object::setColor(const sf::Color & color)
{
    m_sprite.setColor(color);
}

void Object::centerOrigin()
{
    auto bounds = m_sprite.getLocalBounds();
    setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Object::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

sf::Vector2f Object::getVelocity() const
{
    return m_velocity;
}

void Object::erase()
{
    m_erasable = true;
}

bool Object::isErasable() const
{
    return m_erasable;
}
