#include "../Include/Score.hpp"

Score::Score(Context* context)
: Object(Object::Type::Special)
, m_context(context)
, m_text("Score: 0" , context->fonts.get("Candara"), 35)
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

}

void Score::setPoints(std::size_t points)
{
    m_text.setString("Score: " + std::to_string(points));
    ts::rightTopOrigin(m_text);
}
