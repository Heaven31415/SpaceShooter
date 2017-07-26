#include "../Include/GameState.hpp"

const sf::Time GameState::TimePerFrame = sf::seconds(1.f / 60.f);

GameState::GameState(Context* context)
: m_commands()
, m_context(context)
, m_exitFlag({ false, State::Exit })
, m_world(m_commands, context, m_exitFlag)
{
    if (!m_gameTheme.openFromFile("Resources/Music/GameTheme.ogg"))
        throw std::runtime_error("File \"Resources/Music/GameTheme.ogg\" is missing!");
    m_gameTheme.play();
    m_gameTheme.setLoop(true);
}

State::Type GameState::run()
{
    sf::Clock clock;
    sf::Time dt = sf::Time::Zero;
    auto& window = m_context->window;

    while (window.isOpen())
    {
        dt += clock.restart();
        while (dt >= TimePerFrame)
        {
            handleInput();
            update(TimePerFrame);
            dt -= TimePerFrame;
        }
        render();

        if (m_exitFlag.first == true)
        {
            m_exitFlag.first = false;
            return m_exitFlag.second;
        }
    }

    return State::Exit;
}

void GameState::handleInput()
{
    m_world.handleInput();
}

void GameState::update(sf::Time dt)
{
    m_world.update(dt);
}

void GameState::render()
{
    m_world.render();
}