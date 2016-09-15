#pragma once

#include "Player.hpp"

class Hud : public Object
{
public:
                            Hud(Context* context, Player* player);
    virtual void            collision() override;
    virtual void            update(sf::Time dt) override;
    virtual void            monitor() override;

private:
    Context*                m_context;
    Player*                 m_player;
    sf::Vector2i            m_textureSize;
};
