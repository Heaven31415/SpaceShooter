#include "GameConfig.hpp"

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
, backgroundSpeed{0.f, 100.f}
, enemySpeed{250.f, 300.f}
, playerSpeed{250.f, 350.f}
, playerHealth{5}
, playerMaxWeaponCount{5}
, pickupSpeed{100.f}
, objectScale(0.5f)
, hudPosition{5.f, 5.f}
{
}