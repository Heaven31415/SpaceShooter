#pragma once

#include "Context.hpp"
#include "Object.hpp"
#include "Tools.hpp"

class Score : public Object
{
public:
                            Score(Context* context);
    virtual void            draw(sf::RenderTarget& target) const override;
    virtual void            update(sf::Time dt) override;
    void                    setPoints(std::size_t points);

private:
    Context*                m_context;
    sf::Text                m_text;
};