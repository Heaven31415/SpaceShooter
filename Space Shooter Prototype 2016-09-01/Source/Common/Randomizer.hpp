#pragma once

#include <cmath>
#include <random>
#include <SFML/System/Vector2.hpp>

class Random
{
public:
    template<typename T = int>
    static T Int(T min, T max)
    {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(generator);
    }

    template<typename T = float>
    static T Real(T min, T max)
    {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator);
    }

    static sf::Vector2f PointInCircle(const sf::Vector2f& center, float radius)
    {
        float pAngle = Real<float>(0.f, 2 * 3.14159f);
        float pRadius = Real<float>(0.f, radius);
        return{ center.x + cos(pAngle) * pRadius, center.y + sin(pAngle) * pRadius };
    }

    static sf::Vector2f PointAtCircle(const sf::Vector2f& center, float radius)
    {
        float angle = Real<float>(0.f, 2 * 3.14159f);
        return{ center.x + cos(angle) * radius, center.y + sin(angle) * radius };
    }

    static sf::Vector2f PointInRectangle(const sf::Vector2f& leftTopCorner, float width, float height)
    {
        float pWidth = Real<float>(0.f, width);
        float pHeight = Real<float>(0.f, height);
        return{ leftTopCorner.x + pWidth, leftTopCorner.y + pHeight };
    }

    static sf::Vector2f PointAtRectangle(const sf::Vector2f& leftTopCorner, float width, float height)
    {
        float x, y;
        switch (Int(1, 4))
        {
        case 1:
            x = Real<float>(leftTopCorner.x, leftTopCorner.x + width);
            y = leftTopCorner.y;
            break;
        case 2:
            x = Real<float>(leftTopCorner.x, leftTopCorner.x + width);
            y = leftTopCorner.y + height;
            break;
        case 3:
            x = leftTopCorner.x;
            y = Real<float>(leftTopCorner.y, leftTopCorner.y + height);
            break;
        case 4:
            x = leftTopCorner.x + width;
            y = Real<float>(leftTopCorner.y, leftTopCorner.y + height);
            break;
        }
        return{ x, y };
    }

private:
    static std::random_device random;
    static std::default_random_engine generator;
};

std::random_device Random::random;
std::default_random_engine Random::generator(random());
