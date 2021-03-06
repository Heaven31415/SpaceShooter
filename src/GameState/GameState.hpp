#pragma once

#include "World.hpp"
#include "System\CommandQueue.hpp"

class GameState : public State
{
public:
    static const sf::Time           TimePerFrame;

                                    GameState(Context* context);
    State::Type                     run();
    void                            handleInput();
    void                            update(sf::Time dt);
    void                            render();

private:
    CommandQueue                    m_commands;
    Context*                        m_context;
    std::pair<bool, State::Type>    m_exitFlag;
    World                           m_world;
    sf::Music                       m_gameTheme; // @todo: move into SoundSystem
};