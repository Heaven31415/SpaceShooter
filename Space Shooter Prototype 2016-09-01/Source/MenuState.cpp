#include "../Include/MenuState.hpp"

const sf::Time MenuState::TimePerFrame = sf::seconds(1.f / 60.f);

MenuState::MenuState(Context * context)
: m_context(context)
, m_exitFlag({ false, State::Exit })
, m_menu(m_context->textures.get("Menu"))
{
}

State::Type MenuState::run()
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

void MenuState::handleInput()
{
    sf::Event event;
    auto& window = m_context->window;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                    m_exitFlag = { true, State::Exit };
            }
            break;

            case sf::Event::Closed:
            {
                m_exitFlag = { true, State::Exit };
            }
            break;
        }
    }
}

void MenuState::update(sf::Time dt)
{
}

void MenuState::render()
{
    auto& window = m_context->window;

    window.clear();
    window.draw(m_menu);
    window.display();
}
