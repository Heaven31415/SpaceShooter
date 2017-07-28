#pragma once

#include "../Object.hpp"
#include "../../Common/Context.hpp"

class Background : public Object
{
public:
                                Background(Context* context);

public:
    virtual void                draw(sf::RenderTarget& target) const override;
    virtual void                update(sf::Time dt) override;

private:
    Context*                    m_context;
    sf::Sprite                  m_bgExtra;
    const sf::Vector2f          m_mapSize;
    const float                 m_velocity;
};