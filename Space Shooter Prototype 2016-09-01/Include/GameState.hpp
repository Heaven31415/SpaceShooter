#pragma once

#include "Background.hpp"
#include "Context.hpp"
#include "EnemyHandler.hpp"
#include "Hud.hpp"
#include "Player.hpp"
#include "Score.hpp"
#include "State.hpp"
#include "Tools.hpp"

class GameState : public State
{
public:
    static const sf::Time           TimePerFrame;

                                    GameState(Context* context);
    State::Type                     run();
    void                            handleInput();
    void                            update(sf::Time dt);
    void                            render();

private:
    Context*                        m_context;
    std::pair<bool, State::Type>    m_exitFlag;
    CollisionHandler                m_collision;
    Background                      m_background;
    EnemyHandler                    m_enemies;
    Player                          m_player;
    Hud                             m_hud;
    Score                           m_score;
    sf::Music                       m_gameTheme;
};