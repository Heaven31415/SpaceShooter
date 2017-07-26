#include "..\Include\Game.hpp"
#include "..\Include\PlayerController.hpp"
#include "..\Include\World.hpp"

PlayerController::PlayerController(Context * context, World * world)
: m_context(context)
, m_world(world)
{
    // event orders
    m_eventOrders[{sf::Keyboard::Space, true}] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        if (object->isDestroyed()) return;
        auto* player = static_cast<Player*>(object);
        if (player->canAddWeapon()) player->addWeapon(Player::Weapon::Laser);
    });

    m_eventOrders[{sf::Keyboard::A, true}] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        static_cast<Player*>(object)->setGraphicsFrame(Player::Frame::Left);
    });

    m_eventOrders[{sf::Keyboard::A, false}] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        static_cast<Player*>(object)->setGraphicsFrame(Player::Frame::Straight);
    });

    m_eventOrders[{sf::Keyboard::D, true}] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        static_cast<Player*>(object)->setGraphicsFrame(Player::Frame::Right);
    });

    m_eventOrders[{sf::Keyboard::D, false}] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        static_cast<Player*>(object)->setGraphicsFrame(Player::Frame::Straight);
    });

    // real-time orders 
    m_realTimeOrders[sf::Keyboard::W] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        if (object->getPosition().y > 0.f)
            object->move(0.f, -object->getVelocity().y * dt.asSeconds());
    });

    m_realTimeOrders[sf::Keyboard::A] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        if(object->getPosition().x > 0.f)
            object->move(-object->getVelocity().x * dt.asSeconds(), 0.f);
    });

    m_realTimeOrders[sf::Keyboard::S] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        if (object->getPosition().y < static_cast<float>(Game::Config.windowSize.y))
            object->move(0.f, object->getVelocity().y * dt.asSeconds());
    });

    m_realTimeOrders[sf::Keyboard::D] = Command(Type::Player, [](PhysicalObject* object, sf::Time dt) {
        if (object->getPosition().x < static_cast<float>(Game::Config.windowSize.x))
            object->move(object->getVelocity().x * dt.asSeconds(), 0.f);
    });
}

void PlayerController::handleRealTimeInput()
{
    auto& commandQueue = m_world->getCommandQueue();
    for (auto& order : m_realTimeOrders)
    {
        if (sf::Keyboard::isKeyPressed(order.first))
            commandQueue.push(order.second);
    }
}

void PlayerController::handleEventInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
    {
        auto& commandQueue = m_world->getCommandQueue();
        auto key = event.key.code;

        for (auto& order : m_eventOrders)
            if (event.type == sf::Event::KeyPressed && order.first.second && order.first.first == key ||
                event.type == sf::Event::KeyReleased && !order.first.second && order.first.first == key)
                commandQueue.push(order.second);
    }
}
