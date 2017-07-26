#pragma once

#include "../PhysicalObject/Player.hpp"
#include "../../Common/Context.hpp"
#include "../../Common/Observer.hpp"

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