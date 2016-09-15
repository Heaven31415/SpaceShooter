#include "../Include/Game.hpp"
#include <iostream>

int main()
{
    try 
    {
        Game game;
        game.run();
    }
    catch (const std::runtime_error& exception)
    {
        std::cerr << exception.what() << '\n';
    }

    return 0;
}