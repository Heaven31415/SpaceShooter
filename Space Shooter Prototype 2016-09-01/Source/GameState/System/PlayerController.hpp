#pragma once

#include "CommandQueue.hpp"
#include "../PhysicalObject/Player.hpp"

typedef std::pair<sf::Keyboard::Key, bool> KeyState;

class PlayerController
{
public:
                                            PlayerController(Context& context, World& world);
    void                                    handleRealTimeInput();
    void                                    handleEventInput(const sf::Event& event);

private:
    Context&                                m_context;
    World&                                  m_world;
    std::map<sf::Keyboard::Key, Command>    m_realTimeOrders;
    std::map<KeyState, Command>             m_eventOrders;
};