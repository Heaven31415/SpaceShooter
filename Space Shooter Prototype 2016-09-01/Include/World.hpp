#pragma once

#include "Background.hpp"
#include "Context.hpp"
#include "EnemyHandler.hpp"
#include "Hud.hpp"
#include "Pickup.hpp"
#include "Player.hpp"
#include "Score.hpp"
#include "State.hpp"
#include "Tools.hpp"

class World
{
public:
                                    World(Context* context, std::pair<bool, State::Type>& exitFlag);
    void                            handleInput();
    void                            update(sf::Time dt);
    void                            render();

private:
    Context*                        m_context;
    std::pair<bool, State::Type>&   m_exitFlag;
    CollisionHandler                m_collision;
    std::vector<Object::Ptr>        m_objects;
    Background                      m_background;
    EnemyHandler                    m_enemies;
    Pickup                          m_pickup;
    Player                          m_player;
    Hud                             m_hud;
    Score                           m_score;
};