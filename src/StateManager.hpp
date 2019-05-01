#pragma once

#include "GameState\GameState.hpp"
#include "LoadingState\LoadingState.hpp"
#include "MenuState\MenuState.hpp"

class StateManager
{
public:
                                        StateManager(Context* context);
                                        StateManager(const StateManager&) = delete;
    StateManager&                       operator=(const StateManager&) = delete;

public:
    void                                run();
    State::Ptr                          factory(State::Type type);

private:
    Context*                            m_context;
    std::map<State::Type, State::Ptr>   m_states;
    State::Type                         m_next;
};