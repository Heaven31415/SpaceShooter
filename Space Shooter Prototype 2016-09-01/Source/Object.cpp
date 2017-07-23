#include "../Include/Object.hpp"

void Object::draw(sf::RenderTarget & target) const
{
    target.draw(m_sprite, getTransform());
}

void Object::update(sf::Time dt)
{
}

Object::Object(Type::Type type)
: m_type(type)
, m_sprite()
{
}

Object::Object(Type::Type type, const sf::Texture & texture)
: m_type(type)
, m_sprite(texture)
{
}

Object::Object(Type::Type type, const sf::Texture & texture, const sf::IntRect & rectangle)
: m_type(type)
, m_sprite(texture, rectangle)
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