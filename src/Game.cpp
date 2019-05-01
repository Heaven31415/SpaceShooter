#include "Game.hpp"

GameConfig Game::Config{};

Game::Game()
: m_window({ Config.windowSize.x, Config.windowSize.y }, Config.windowTitle)
, m_textures(Config.texturesExts, Config.texturesPath)
, m_sounds(Config.soundsExts, Config.soundsPath)
, m_fonts(Config.fontsExts, Config.fontsPath)
, m_context(m_window, m_textures, m_sounds, m_fonts)
, m_manager(&m_context)
{
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(Config.windowSize) / 2, m_window);
    m_window.setMouseCursorVisible(false);
    m_window.setKeyRepeatEnabled(Config.keyRepeatEnabled);
    m_window.setVerticalSyncEnabled(Config.verticalSyncEnabled);
}

void Game::run()
{
    m_manager.run();
}