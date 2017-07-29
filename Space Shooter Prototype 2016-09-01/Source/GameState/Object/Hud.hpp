#pragma once

#include "../PhysicalObject/Player.hpp"
#include "../../Common/Context.hpp"
#include "../../Common/Observer.hpp"

class Hud : public Object, public Observer
{
public:
                            Hud(Context& context, World& world);
    virtual void            onNotify(Object* object, unsigned int code) override;

private:
    void                    updateHealthFrame(std::size_t health);

private:
    sf::Texture&            m_texture;
};