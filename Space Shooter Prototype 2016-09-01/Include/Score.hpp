#pragma once

#include "Context.hpp"
#include "Observer.hpp"
#include "Tools.hpp"

class Score : public Object, public Observer
{
public:
                            Score(Context* context);
    virtual void            draw(sf::RenderTarget& target) const override;
    virtual void            onNotify(Object* obj, unsigned int code) override;

private:
    Context*                m_context;
    unsigned int            m_enemyKilled;
    sf::Text                m_text;
};