#include "World.hpp"
#include "../Game.hpp"

World::World(CommandQueue & commands, Context * context, std::pair<bool, State::Type> & exitFlag)
: m_commands(commands)
, m_context(context)
, m_exitFlag(exitFlag)
, m_collision()
, m_pickupFactory(*context, *this)
, m_laserFactory(*context, *this)
, m_controller(*context, *this)
, m_hud(*context, *this)
, m_score(*context, *this)
{
    auto windowSize = static_cast<sf::Vector2f>(Game::Config.windowSize);

    auto backgroundPartOne = std::make_unique<Background>(*context, *this);
    auto backgroundPartTwo = std::make_unique<Background>(*context, *this);
    backgroundPartTwo->setPosition({ 0.f, -windowSize.y });

    add(std::move(backgroundPartOne));
    add(std::move(backgroundPartTwo));

    auto player = std::make_unique<Player>(*context, *this, m_laserFactory);
    player->setPosition({ windowSize.x * 0.5f, windowSize.y * 0.75f });
    player->add(&m_hud);
    player->add(&m_score); 
    add(std::move(player));

    auto enemy = std::make_unique<Enemy>(*context, *this, m_laserFactory);
    enemy->setAI(std::make_unique<EnemyMaster>());
    add(std::move(enemy));
}

void World::add(Object::Ptr obj)
{
    m_objects.push_back(std::move(obj));
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
        m_controller.handleEventInput(event);
    }
    m_controller.handleRealTimeInput();
}

void World::update(sf::Time dt)
{
    handleCommands(dt);

    // if object is destroyed and has no children, get rid of it
    std::experimental::erase_if(m_objects, [](const Object::Ptr& obj) { return obj->isErasable(); });

    // use this instead of range based for loop because update may invalidate iterators
    for (std::size_t i = 0; i < m_objects.size(); i++)
        m_objects[i]->update(dt);

    m_hud.update(dt);
    m_score.update(dt);
    m_collision.checkCollision();
}

void World::render()
{
    auto& window = m_context->window;

    window.clear();

    for (const auto& obj : m_objects) window.draw(*obj);
    window.draw(m_hud);
    window.draw(m_score);

    window.display();
}

void World::handleCommands(sf::Time dt)
{
    while (!m_commands.isEmpty())
    {
        auto command = m_commands.pop();
        for (std::size_t i = 0; i < m_objects.size(); i++)
            if (command.who & m_objects[i]->getType())
                command.action(m_objects[i].get(), dt);
    }
}

CommandQueue & World::getCommandQueue()
{
    return m_commands;
}

CollisionHandler * World::getCollision()
{
    return &m_collision;
}

Player * World::getPlayer()
{
    for (const auto& objectPtr : m_objects)
        if (objectPtr->getType() == Type::Player)
            return static_cast<Player*>(objectPtr.get());
    return nullptr;
}
