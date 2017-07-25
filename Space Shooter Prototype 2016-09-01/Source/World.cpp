#include "..\Include\World.hpp"

World::World(Context * context, std::pair<bool, State::Type>& exitFlag)
: m_context(context)
, m_exitFlag(exitFlag)
, m_collision()
, m_background(context)
, m_pickupFactory(context, this)
, m_hud(context, this)
, m_score(context)
, m_spawnerTimer(sf::seconds(1.f))
{
    auto player = std::make_unique<Player>(context, this);
    player->setPosition({ 400.f, 300.f });
    player->add(&m_context->soundSystem); // let soundSystem observe Player
    player->add(&m_hud);
    player->add(&m_score); // same for scoreKeeper
    add(std::move(player));
}

void World::add(PhysicalObject::Ptr obj)
{
    m_physicalObjects.push_back(std::move(obj));
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

        // is there a better way to handle this?
        for (std::size_t i = 0; i < m_physicalObjects.size(); i++)
            if (m_physicalObjects[i]->getType() == Type::Player)
                static_cast<Player*>(m_physicalObjects[i].get())->handleEvent(event);
    }
}

void World::update(sf::Time dt)
{
    m_background.update(dt);

    // if object is destroyed and has no children, get rid of it
    std::experimental::erase_if(m_physicalObjects, [](const PhysicalObject::Ptr& obj) { return obj->isErasable(); });

    // use this instead of range based for loop because update may invalidate iterators
    for (std::size_t i = 0; i < m_physicalObjects.size(); i++)
        m_physicalObjects[i]->update(dt);

    m_hud.update(dt);
    m_score.update(dt);

    // temporary spawner
    if (m_spawnerTimer > dt)
        m_spawnerTimer -= dt;
    else
    {
        spawn();
        m_spawnerTimer = sf::seconds(1.f);
    }

    m_collision.checkCollision();
}

void World::render()
{
    auto& window = m_context->window;
    window.clear();

    // first layer
    m_background.draw(window);

    // second layer
    for (auto& obj : m_physicalObjects) obj->draw(window);

    // third layer
    m_hud.draw(window);
    m_score.draw(window);

    window.display();
}

CollisionHandler * World::getCollision()
{
    return &m_collision;
}

pObjectContainer World::getNearestpObjectsWithType(sf::Vector2f center, float distance, Type::Type type)
{
    pObjectContainer container;
    for (auto& pObjectPtr : m_physicalObjects)
    {
        if (type == Type::None)
        {
            if (ts::calculateDistance(pObjectPtr->getPosition(), center) < distance)
                container.push_back(pObjectPtr.get());
        }
        else
        {
            if (pObjectPtr->getType() == type && ts::calculateDistance(pObjectPtr->getPosition(), center) < distance)
                container.push_back(pObjectPtr.get());
        }
    }
    return container;
}

Player * World::getNearestPlayer()
{
    for (auto& pObjectPtr : m_physicalObjects)
        if (pObjectPtr->getType() == Type::Player)
            // should it be a dynamic_cast?
            return static_cast<Player*>(pObjectPtr.get());
    return nullptr;
}

Player * World::getPlayer()
{
    for (auto& pObjectPtr : m_physicalObjects)
        if (pObjectPtr->getType() == Type::Player)
            return static_cast<Player*>(pObjectPtr.get());
    return nullptr;
}

void World::spawn()
{
    Randomizer random;
    int number = random.getIntNumber(0, 100);
    if (number > 90)
        add(m_pickupFactory.build("death"));
    else if(number > 80)
        add(m_pickupFactory.build("heal"));
    else
        add(std::make_unique<Enemy>(m_context, this));
}
