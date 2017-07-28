#include "Background.hpp"
#include "../../Game.hpp"

Background::Background(Context* context)
: Object(Type::Special)
, m_context(context)
, m_mapSize(static_cast<sf::Vector2f>(Game::Config.windowSize))
, m_velocity(Game::Config.backgroundSpeed)
{
    auto& texture = context->textures.get("StarBackground");
    texture.setRepeated(true);

    setTexture(texture);
    m_bgExtra.setTexture(texture);

    sf::IntRect rectangle{ {0,0}, static_cast<sf::Vector2i>(m_mapSize) };
    setTextureRect(rectangle);
    m_bgExtra.setTextureRect(rectangle);

    setPosition(0, 0);
    m_bgExtra.setPosition({ 0, m_mapSize.y });
}

void Background::draw(sf::RenderTarget & target) const
{
    Object::draw(target);
    target.draw(m_bgExtra);
}

void Background::update(sf::Time dt)
{
    auto dy = m_velocity * dt.asSeconds();
    move(0, dy);
    m_bgExtra.move(0, dy);

    if (getPosition().y >= m_mapSize.y)
        move(0, -2 * m_mapSize.y);
    if (m_bgExtra.getPosition().y >= m_mapSize.y) 
        m_bgExtra.move(0, -2 * m_mapSize.y);
}