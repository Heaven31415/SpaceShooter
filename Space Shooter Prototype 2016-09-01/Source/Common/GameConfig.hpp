#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include <vector>

typedef std::vector<std::string> extensions;

struct GameConfig
{
    GameConfig();
    const bool                  keyRepeatEnabled;
    const bool                  verticalSyncEnabled;
    const sf::Vector2u          windowSize;
    const std::string           windowTitle;
    const extensions            texturesExts;
    const extensions            soundsExts;
    const extensions            fontsExts;
    const std::string           texturesPath;
    const std::string           soundsPath;
    const std::string           fontsPath;
    const float                 laserSpeed;
    const float                 backgroundSpeed;
    const sf::Vector2f          enemySpeed;
    const std::size_t           enemyMaxLaser;
    const sf::Vector2f          playerSpeed;
    const std::size_t           playerHealth;
    const std::size_t           playerMaxLaser;
    const float                 pickupSpeed;
    const std::size_t           enemyMaxNumber;
    const sf::Time              enemySpawnTimer;
};