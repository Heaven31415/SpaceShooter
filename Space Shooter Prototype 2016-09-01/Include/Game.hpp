#pragma once

#include "ResourceHolder.hpp"
#include "StateManager.hpp"

class Game : private sf::NonCopyable
{
public:
                            Game();
    void                    run();

private:
    sf::RenderWindow        m_window;
    TextureHolder           m_textures;
    SoundHolder             m_sounds;
    FontHolder              m_fonts;
    Context                 m_context;
    StateManager            m_manager;
};