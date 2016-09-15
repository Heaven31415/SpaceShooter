#pragma once

#include "ResourceHolder.hpp"

struct Context
{
Context(sf::RenderWindow& _window, TextureHolder& _textures, SoundHolder& _sounds)
: window(_window)
, textures(_textures)
, sounds(_sounds)
{
}

sf::RenderWindow&       window;
TextureHolder&          textures;
SoundHolder&            sounds;
};
