#include "Hud.hpp"
#include "../World.hpp"
#include "../../Game.hpp"

Hud::Hud(Context* context, World* world)
: Object(Type::Special)
, m_context(context)
, m_world(world)
, m_texture(context->textures.get("Life"))
{
    m_texture.setRepeated(true);
    setTexture(m_texture);
    setPosition(Game::Config.hudPosition);
    updateHealthFrame(Game::Config.playerHealth);
}

void Hud::onNotify(Object * object, unsigned int code)
{
    if (object->getType() == Type::Player)
    {
        auto event = static_cast<Event::Type>(code);
        if (event == Event::TakenDamage || event == Event::Healed)
        {
            Player* player = m_world->getPlayer();
            std::size_t health = player->getHealth();
            // player not found, 'hide' hud
            if (!player) health = 0;
            updateHealthFrame(health);
        }
    }
}

void Hud::updateHealthFrame(std::size_t health)
{
    sf::Vector2i size = static_cast<sf::Vector2i>(m_texture.getSize());
    setTextureRect({ 0, 0, static_cast<int>(health) * size.x, size.y });
}
