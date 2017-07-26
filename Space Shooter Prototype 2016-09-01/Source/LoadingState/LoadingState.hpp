#pragma once

#include "../Common/Context.hpp"
#include "../State.hpp"
#include "../Common/Tools.hpp"

class LoadingState : public State
{
public:
    static const sf::Time           TimePerFrame;

                                    LoadingState(Context* context);
    State::Type                     run();
    void                            handleInput();
    void                            update(sf::Time dt);
    void                            render();

private:
    Context*                        m_context;
    std::pair<bool, State::Type>    m_exitFlag;
    sf::RectangleShape              m_loadingBarFill;
    sf::RectangleShape              m_loadingBarBackground;
    bool                            m_resourcesLoaded;

    sf::Sprite                      m_background;
    sf::Texture                     m_backgroundTexture;
    sf::Sprite                      m_cursor;
    sf::Texture                     m_cursorTexture;
    sf::Text                        m_loadingText;
    sf::Font                        m_loadingTextFont;
    sf::Time                        m_loadingTextTimer;
    sf::Music                       m_loadingTheme;
};