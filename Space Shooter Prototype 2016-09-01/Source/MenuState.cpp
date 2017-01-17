#include "../Include/MenuState.hpp"

const sf::Time MenuState::TimePerFrame = sf::seconds(1.f / 60.f);

MenuState::MenuState(Context * context)
: m_context(context)
, m_exitFlag({ false, State::Exit })
, m_cursor(m_context->textures.get("Cursor"))
, m_gui(m_context->window)
{
    m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_context->window)));
    buildGui();
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

            case sf::Event::MouseLeft:
            {
                m_cursor.setColor({ 0,0,0,0 });
            }
            break;

            case sf::Event::MouseEntered:
            {
                m_cursor.setColor({ 255,255,255,255 });
            }
            break;

            m_gui.handleEvent(event);
        }
    }
}

void MenuState::update(sf::Time dt)
{
    m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_context->window)));
}

void MenuState::render()
{
    auto& window = m_context->window;

    window.clear();
    m_gui.draw();
    window.draw(m_cursor);
    window.display();
}

void MenuState::buildGui()
{
}
