#include "..\Include\World.hpp"

World::World(Context * context, std::pair<bool, State::Type>& exitFlag)
: m_context(context)
, m_exitFlag(exitFlag)
, m_collision()
, m_background(context)
, m_enemies(context, &m_collision)
, m_pickup(context, &m_collision)
, m_player(context, &m_collision)
, m_hud(context, &m_player)
, m_score(context)
{
    m_player.setPosition({ 400.f, 300.f });
    m_player.add(&m_context->soundSystem);
    m_player.add(&m_score);
}

void World::handleInput()
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

void World::update(sf::Time dt)
{
    m_background.update(dt);
    m_enemies.update(dt);
    m_pickup.update(dt);
    m_player.update(dt);
    m_hud.update(dt);
    m_score.update(dt);

    m_collision.checkCollision();
}

void World::render()
{
    auto& window = m_context->window;

    window.clear();
    m_background.draw(window);
    m_pickup.draw(window);
    m_enemies.draw(window);
    m_player.draw(window);
    m_hud.draw(window);
    m_score.draw(window);
    window.display();
}
