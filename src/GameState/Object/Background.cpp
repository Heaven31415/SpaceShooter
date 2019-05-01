#include "Background.hpp"
#include "../../Game.hpp"

Background::Background(Context & context, World & world)
: Object(context, world, Type::Special)
, m_mapSize(static_cast<sf::Vector2f>(Game::Config.windowSize))
{
    auto& texture = context.textures.get("StarBackground");
    texture.setRepeated(true);

    setTexture(texture);
    setTextureRect({ { 0,0 }, static_cast<sf::Vector2i>(m_mapSize) });

    setMaxVelocity(Game::Config.backgroundSpeed);
    setVelocity(Game::Config.backgroundSpeed);
}

void Background::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    Object::draw(target, states);
}

void Background::update(sf::Time dt)
{
    Object::update(dt);
    if (getPosition().y >= m_mapSize.y) 
        move(0, -2 * m_mapSize.y);
}