#pragma once

#include "Context.hpp"
#include "Object.hpp"

class Background : public Object
{
public:
                            Background(Context* context);

public:
    virtual void            draw(sf::RenderTarget& target) const override;
    virtual void            update(sf::Time dt) override;

private:
    Context*                m_context;
    sf::Sprite              m_bgExtra;
    float                   m_velocity;
};