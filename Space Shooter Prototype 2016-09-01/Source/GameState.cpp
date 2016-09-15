#include "../Include/GameState.hpp"

const sf::Time GameState::TimePerFrame = sf::seconds(1.f / 60.f);

GameState::GameState(Context* context)
: m_context(context)
, m_exitFlag({ false, State::Exit })
, m_collision()
, m_background(context)
, m_enemies(context, &m_collision)
, m_player(context, &m_collision)
, m_hud(context, &m_player)
, m_score(context, &m_player)
{
    if (!m_gameTheme.openFromFile("Resources/Music/GameTheme.ogg"))
        throw std::runtime_error("\"Resources/Music/GameTheme.ogg\" is missing!");
    m_gameTheme.play();
    m_gameTheme.setLoop(true);

    m_player.setPosition({ 400.f, 300.f });
    m_collision.addPermanent(&m_enemies);
    m_collision.addPermanent(&m_player);
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
            m_collision.checkCollision();
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
        m_player.handleEvent(event);
    }
}

void GameState::update(sf::Time dt)
{
    m_background.update(dt);
    m_enemies.update(dt);
    m_player.update(dt);
    m_hud.update(dt);
    m_score.update(dt);
}

void GameState::render()
{
    auto& window = m_context->window;

    window.clear();
    m_background.draw(window);
    m_enemies.draw(window);
    m_player.draw(window);
    m_hud.draw(window);
    m_score.draw(window);
    window.display();
}
