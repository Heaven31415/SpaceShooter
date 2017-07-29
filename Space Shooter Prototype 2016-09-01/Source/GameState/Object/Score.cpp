#include "Score.hpp"
#include "../PhysicalObject/Player.hpp"
#include "../../Game.hpp"

Score::Score(Context& context, World& world)
: Object(context, world, Type::Special)
, m_enemyKilled(0)
, m_text("Score: " + std::to_string(m_enemyKilled), getContext().fonts.get("Candara"), 35)
{
    ts::rightTopOrigin(m_text);
    auto windowWidth = static_cast<float>(Game::Config.windowSize.x);
    m_text.setPosition(0.98f * windowWidth, 0);
}

void Score::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}

// @todo: this won't do any good when we will have multiple enemies and objectives
// with various score rewards, it should be handled via command system, not observer
void Score::onNotify(Object * obj, unsigned int code)
{
    if (obj->getType() == Type::Player && static_cast<Event::Type>(code) == Event::EnemyKilled)
    {
        m_enemyKilled++;
        m_text.setString("Score: " + std::to_string(m_enemyKilled * 10));
        ts::rightTopOrigin(m_text);
    }
}