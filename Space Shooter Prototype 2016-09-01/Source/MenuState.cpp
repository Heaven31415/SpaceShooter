#include "../Include/MenuState.hpp"

const sf::Time MenuState::TimePerFrame = sf::seconds(1.f / 60.f);

MenuState::MenuState(Context * context)
: m_context(context)
, m_exitFlag({ false, State::Exit })
, m_menu(m_context->textures.get("Menu"))
, m_cursor(m_context->textures.get("Cursor"))
, m_titleLabel("Space Shooter", m_context->fonts.get("Candara"), 60)
, m_newGameLabel("New Game", m_context->fonts.get("Candara"))
, m_exitLabel("Exit", m_context->fonts.get("Candara"))
, m_optionsWindow()
{
    auto windowSize = static_cast<sf::Vector2f>(GC::windowSize);
    auto bounds = m_menu.getGlobalBounds();
    // scale menu so it can fit nicely into whole window
    m_menu.setScale(windowSize.x / bounds.width, windowSize.y / bounds.height );

    ts::centerOrigin(m_cursor);
    ts::centerOrigin(m_titleLabel);
    ts::centerOrigin(m_newGameLabel);
    ts::centerOrigin(m_exitLabel);

    m_titleLabel.setOutlineThickness(1.f);
    m_newGameLabel.setOutlineThickness(1.f);
    m_exitLabel.setOutlineThickness(1.f);

    m_titleLabel.setPosition(windowSize.x / 2.f, windowSize.y * 0.1f);
    m_newGameLabel.setPosition(windowSize.x / 2.f, windowSize.y * 0.5f);
    m_exitLabel.setPosition(windowSize.x / 2.f, windowSize.y * 0.6f);

    m_optionsWindow.setSize({ windowSize * 0.25f });
    m_optionsWindow.setPosition(windowSize.x / 2.f, windowSize.y * 0.55f);
    m_optionsWindow.setFillColor({ 0,0,200,100 });
    m_optionsWindow.setOutlineColor({ 0, 0, 255, 200 });
    m_optionsWindow.setOutlineThickness(1.f);
    ts::centerOrigin(m_optionsWindow);
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
    m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_context->window)));
}

void MenuState::render()
{
    auto& window = m_context->window;

    window.clear();
    window.draw(m_menu);
    window.draw(m_optionsWindow);
    window.draw(m_titleLabel);
    window.draw(m_newGameLabel);
    window.draw(m_exitLabel);
    window.draw(m_cursor);
    window.display();
}
