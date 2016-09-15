#include "../Include/Hud.hpp"

Hud::Hud(Context* context, Player* player)
: Object(Object::Type::Special)
, m_context(context)
, m_player(player)
{
    auto& texture = context->textures.get("Life");
    texture.setRepeated(true);
    m_textureSize = static_cast<sf::Vector2i>(texture.getSize());

    setTexture(texture);
    update(sf::Time::Zero);

    setPosition(5.f, 5.f);
}

void Hud::collision()
{
}

void Hud::update(sf::Time dt)
{
    auto health = m_player->getHealth();
    setTextureRect({ 0, 0, static_cast<int>(health) * m_textureSize.x, m_textureSize.y });
}

void Hud::monitor()
{
}
