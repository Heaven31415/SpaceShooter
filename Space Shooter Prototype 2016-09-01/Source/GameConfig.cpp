#include "../Include/GameConfig.hpp"

GameConfig::GameConfig()
: keyRepeatEnabled{false}
, verticalSyncEnabled{true}
, windowSize{ 800u, 600u }
, windowTitle{ "Space Shooter" }
, texturesExts{ "png" }
, soundsExts{ "ogg", "wav" }
, fontsExts{ "ttf" }
, texturesPath{ "Resources/Graphics" }
, soundsPath{ "Resources/Sounds" }
, fontsPath{ "Resources/Fonts" }
, laserSpeed{500.f}
, backgroundSpeed{100.f}
, enemySpeed{150.f, 200.f}
, enemyMaxLaser{5}
, playerSpeed{250.f, 350.f}
, playerHealth{5}
, playerMaxLaser{5}
, pickupSpeed{100.f}
, enemyMaxNumber{10}
, enemySpawnTimer{sf::seconds(1.f)}
{
}
