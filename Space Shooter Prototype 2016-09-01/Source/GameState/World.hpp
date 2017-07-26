#pragma once

#include "Object\Background.hpp"
#include "Object\Hud.hpp"
#include "Object\Score.hpp"
#include "PhysicalObject\Enemies\Enemy.hpp"
#include "PhysicalObject\Pickups\PickupFactory.hpp"
#include "PhysicalObject\Player.hpp"
#include "System\PlayerController.hpp"
#include "../State.hpp"
#include "../Common/Context.hpp"
#include "../Common/Tools.hpp"

typedef std::vector<PhysicalObject*> pObjectContainer;

class World
{
public:
                                        World(CommandQueue& commands, Context* context, std::pair<bool, State::Type>& exitFlag);
    void                                add(PhysicalObject::Ptr obj);
    void                                handleInput();
    void                                update(sf::Time dt);
    void                                render();

    void                                handleCommands(sf::Time dt);
    CommandQueue&                       getCommandQueue();
    CollisionHandler*                   getCollision();
    
public:
    // utility functions
    pObjectContainer                    getNearestpObjectsWithType(sf::Vector2f center, float distance, Type::Type type = Type::None);
    Player*                             getNearestPlayer();
    Player*                             getPlayer();

private:
    CommandQueue&                       m_commands;
    Context*                            m_context;
    std::pair<bool, State::Type>&       m_exitFlag;
    CollisionHandler                    m_collision;
    std::vector<PhysicalObject::Ptr>    m_physicalObjects;
    Background                          m_background;
    PickupFactory                       m_pickupFactory;
    PlayerController                    m_controller;
    Hud                                 m_hud;
    Score                               m_score;
};