#pragma once

#include <TGUI/TGUI.hpp>

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
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructs an opaque black color. It is equivalent to
    /// sf::Color(0, 0, 0, 255).
    ///
    ////////////////////////////////////////////////////////////
    void                            buildGui();

private:
    Context*                        m_context;
    std::pair<bool, State::Type>    m_exitFlag;
    sf::Sprite                      m_cursor;
    tgui::Gui                       m_gui;
};