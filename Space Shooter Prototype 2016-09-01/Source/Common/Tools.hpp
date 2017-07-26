#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <math.h>

namespace ts 
{
    template<typename T>
    static void centerOrigin(T& obj)
    {
        auto bounds = obj.getLocalBounds();
        obj.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    template<>
    static void centerOrigin(sf::Text& text)
    {
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    }

    template<typename T>
    static void rightTopOrigin(T& obj)
    {
        auto bounds = obj.getLocalBounds();
        obj.setOrigin(bounds.width, 0);
    }

    template<>
    static void rightTopOrigin(sf::Text& text)
    {
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width, 0);
    }

    inline static float calculateDistance(const sf::Vector2f& a, const sf::Vector2f& b)
    {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }
}