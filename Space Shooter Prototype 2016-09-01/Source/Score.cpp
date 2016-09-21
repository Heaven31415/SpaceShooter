#include "../Include/Score.hpp"

Score::Score(Context * context, Player * player)
: Object(Object::Type::Special)
, m_context(context)
, m_player(player)
, m_text("Score: " + std::to_string(player->getScore()), context->fonts.get("Candara"), 35)
{
    ts::rightTopOrigin(m_text);
    auto windowWidth = static_cast<float>(context->window.getSize().x);
    m_text.setPosition(windowWidth - 10, 0);
}

void Score::draw(sf::RenderTarget & target) const
{
    target.draw(m_text);
}

void Score::update(sf::Time dt)
{
    m_text.setString("Score: " + std::to_string(m_player->getScore()));
    ts::rightTopOrigin(m_text);
}
