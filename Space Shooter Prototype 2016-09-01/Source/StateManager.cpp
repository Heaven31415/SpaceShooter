#include "../Include/StateManager.hpp"

StateManager::StateManager(Context* context)
: m_context(context)
, m_next(State::Loading)
{
}

void StateManager::run()
{
	while (m_next != State::Exit)
	{
        if (m_states[m_next] == nullptr)
            m_states[m_next] = factory(m_next);
        else
		    m_next = m_states[m_next]->run();
	}
}

State::Ptr StateManager::factory(State::Type type)
{
    switch (type)
    {
        case State::Exit:
            return nullptr;
        case State::Game:
            return State::Ptr(new GameState(m_context));
        case State::Loading:
            return State::Ptr(new LoadingState(m_context));
    }
    return nullptr;
}
