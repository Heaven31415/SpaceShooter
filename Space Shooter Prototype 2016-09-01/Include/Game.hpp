#pragma once

#include "GameConfig.hpp"
#include "ResourceHolder.hpp"
#include "StateManager.hpp"

class Game
{
public:
    static GameConfig       Config;

public:
                            Game();
                            Game(const Game&) = delete;
    Game&                   operator=(const Game&) = delete;
    void                    run();

private:
    sf::RenderWindow        m_window;
    TextureHolder           m_textures;
    SoundHolder             m_sounds;
    FontHolder              m_fonts;
    Context                 m_context;
    StateManager            m_manager;
};