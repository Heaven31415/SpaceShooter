#pragma once
#include <random>

class Randomizer
{
public:
    Randomizer();

    template<typename T = int>
    T getIntNumber(T a, T b)
    {
        std::uniform_int_distribution<T> distribution(a, b);
        return distribution(engine);
    }

    template<typename T = float>
    T getRealNumber(T a, T b)
    {
        std::uniform_real_distribution<T> distribution(a, b);
        return distribution(engine);
    }

private:
    std::random_device randomDevice;
    std::mt19937 engine;
};