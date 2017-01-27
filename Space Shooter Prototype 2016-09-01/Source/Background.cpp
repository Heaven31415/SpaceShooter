#include "../Include/Game.hpp"
#include "../Include/Background.hpp"

Background::Background(Context* context)
: Object(Type::Special)
, m_context(context)
, m_velocity(Game::Config.backgroundSpeed)
{
    auto mapSize = static_cast<sf::Vector2i>(Game::Config.windowSize);
    auto& texture = context->textures.get("StarBackground");
    texture.setRepeated(true);

    setTexture(texture);
    setTextureRect({ 0, 0, mapSize.x, mapSize.y });
    setPosition(0, 0);

    m_bgExtra.setTexture(texture);
    m_bgExtra.setTextureRect({ 0, 0, mapSize.x, mapSize.y });
    m_bgExtra.setPosition(0, -static_cast<float>(mapSize.y));
}

void Background::draw(sf::RenderTarget & target) const
{
    Object::draw(target);
    target.draw(m_bgExtra);
}

void Background::update(sf::Time dt)
{
    auto mapSize = static_cast<sf::Vector2f>(Game::Config.windowSize);
    auto dy = m_velocity * dt.asSeconds();
    move(0, dy);
    m_bgExtra.move(0, dy);

    if (getPosition().y >= mapSize.y) move(0, -2 * mapSize.y);
    if (m_bgExtra.getPosition().y >= mapSize.y) m_bgExtra.move(0, -2 * mapSize.y);
}