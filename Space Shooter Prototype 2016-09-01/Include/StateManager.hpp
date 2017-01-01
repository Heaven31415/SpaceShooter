#pragma once

#include "GameState.hpp"
#include "LoadingState.hpp"
#include "MenuState.hpp"

class StateManager : private sf::NonCopyable
{
public:
	                                    StateManager(Context* context);
	void                                run();
    State::Ptr                          factory(State::Type type);

private:
    Context*                            m_context;
	std::map<State::Type, State::Ptr>   m_states;
	State::Type                         m_next;
};