#include "Hud.hpp"
#include "../World.hpp"
#include "../../Game.hpp"

Hud::Hud(Context* context, World* world)
: Object(Type::Special)
, m_context(context)
, m_world(world)
, m_actualHealth(Game::Config.playerHealth)
{
    auto& texture = context->textures.get("Life");
    texture.setRepeated(true);
    m_textureSize = static_cast<sf::Vector2i>(texture.getSize());

    setTexture(texture);
    setTextureRect({ 0, 0, static_cast<int>(m_actualHealth) * m_textureSize.x, m_textureSize.y });

    setPosition(5.f, 5.f);
}

void Hud::onNotify(Object * obj, unsigned int code)
{
    if (obj->getType() == Type::Player)
    {
        auto event = static_cast<Event::Type>(code);
        if (event == Event::TakenDamage || event == Event::Healed)
        {
            auto* player = m_world->getPlayer();
            if (player) m_actualHealth = player->getHealth();
            setTextureRect({ 0, 0, static_cast<int>(m_actualHealth) * m_textureSize.x, m_textureSize.y });
        }
    }
}
