#pragma once

#include "Background.hpp"
#include "Context.hpp"
#include "EnemyHandler.hpp"
#include "Hud.hpp"
#include "Player.hpp"
#include "Score.hpp"
#include "State.hpp"
#include "Tools.hpp"

class MenuState : public State
{
public:
    static const sf::Time           TimePerFrame;

    MenuState(Context* context);
    State::Type                     run();
    void                            handleInput();
    void                            update(sf::Time dt);
    void                            render();

private:
    Context*                        m_context;
    std::pair<bool, State::Type>    m_exitFlag;
    sf::Sprite                      m_menu;
};