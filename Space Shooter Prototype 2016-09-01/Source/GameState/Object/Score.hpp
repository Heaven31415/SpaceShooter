#pragma once

#include "../Object.hpp"
#include "../../Common/Context.hpp"
#include "../../Common/Observer.hpp"
#include "../../Common/Tools.hpp"

class Score : public Object, public Observer
{
public:
                            Score(Context& context, World& world);
    virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void            onNotify(Object* obj, unsigned int code) override;

private:
    unsigned int            m_enemyKilled;
    sf::Text                m_text;
};