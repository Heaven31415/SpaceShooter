#pragma once

#include <TGUI/TGUI.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Math.hpp>

#include "Context.hpp"
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
    void                            buildGui();
    void                            buildOptions();

private:
    Context*                        m_context;
    std::pair<bool, State::Type>    m_exitFlag;
    sf::Sprite                      m_cursor;
    tgui::Gui                       m_gui;
};