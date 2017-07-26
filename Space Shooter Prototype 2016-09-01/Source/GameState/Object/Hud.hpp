#pragma once

#include "Context.hpp"
#include "Observer.hpp"
#include "Player.hpp"

class Hud : public Object, public Observer
{
public:
                            Hud(Context* context, World* world);
    virtual void            onNotify(Object* obj, unsigned int code) override;

private:
    Context*                m_context;
    World*                  m_world;
    std::size_t             m_actualHealth;
    sf::Vector2i            m_textureSize;
};