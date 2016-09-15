#pragma once

#include "Player.hpp"
#include "Tools.hpp"

class Score : public Object
{
public:
                            Score(Context* context, Player* player);
    virtual void            draw(sf::RenderTarget& target) const override;
    virtual void            update(sf::Time dt) override;

private:
    Context*                m_context;
    Player*                 m_player;
    sf::Text                m_text;
};
