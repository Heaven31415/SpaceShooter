#pragma once

#include "../Object.hpp"
#include "../../Common/Context.hpp"

class Background : public Object
{
public:
                                Background(Context& context, World& world);

public:
    virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void                update(sf::Time dt) override;

private:
    const sf::Vector2f          m_mapSize;
};