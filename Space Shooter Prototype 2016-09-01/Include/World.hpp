#pragma once

#include "Background.hpp"
#include "CommandQueue.hpp"
#include "Context.hpp"
#include "Enemy.hpp"
#include "Hud.hpp"
#include "PickupFactory.hpp"
#include "Player.hpp"
#include "PlayerController.hpp"
#include "Score.hpp"
#include "State.hpp"
#include "Tools.hpp"

typedef std::vector<PhysicalObject*> pObjectContainer;

class World
{
public:
                                        World(Context* context, std::pair<bool, State::Type>& exitFlag);
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
    void                                spawn();

private:
    CommandQueue                        m_commands;
    Context*                            m_context;
    std::pair<bool, State::Type>&       m_exitFlag;
    CollisionHandler                    m_collision;
    std::vector<PhysicalObject::Ptr>    m_physicalObjects;
    Background                          m_background;
    PickupFactory                       m_pickupFactory;
    PlayerController                    m_controller;
    Hud                                 m_hud;
    Score                               m_score;
    sf::Time                            m_spawnerTimer;
};