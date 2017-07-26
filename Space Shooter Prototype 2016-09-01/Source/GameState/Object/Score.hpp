#pragma once

#include "../../Common/Context.hpp"
#include "../../Common/Observer.hpp"
#include "../../Common/Tools.hpp"

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