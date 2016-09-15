#pragma once

#include <SFML/Graphics/Sprite.hpp>

namespace ts 
{
    static void centerOrigin(sf::Sprite& sprite)
    {
        auto bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }
    static void centerOrigin(sf::Text& text)
    {
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    }
    static void rightTopOrigin(sf::Text& text)
    {
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width, 0);
    }
}


