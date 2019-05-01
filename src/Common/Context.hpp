#pragma once

#include "ResourceHolder.hpp"
#include "SoundSystem.hpp"

struct Context
{
    Context(sf::RenderWindow& _window, TextureHolder& _textures, SoundHolder& _sounds, FontHolder& _fonts)
    : window(_window)
    , textures(_textures)
    , sounds(_sounds)
    , fonts(_fonts)
    , soundSystem{_sounds}
    {
    }

    sf::RenderWindow&       window;
    TextureHolder&          textures;
    SoundHolder&            sounds;
    FontHolder&             fonts;
    SoundSystem             soundSystem;
};