#include "../Include/Game.hpp"

Game::Game()
: m_window({800, 600}, "Space Shooter"/*, sf::Style::Fullscreen*/)
, m_textures({"png"}, "Resources/Graphics")
, m_sounds({"ogg", "wav"}, "Resources/Sounds")
, m_fonts({"ttf"}, "Resources/Fonts")
, m_context(m_window, m_textures, m_sounds, m_fonts)
, m_manager(&m_context)
{
    sf::Mouse::setPosition({ 400, 300 }, m_window);
    m_window.setKeyRepeatEnabled(false);
    m_window.setMouseCursorVisible(false);
    m_window.setVerticalSyncEnabled(true);
}

void Game::run()
{
    m_manager.run();
}
