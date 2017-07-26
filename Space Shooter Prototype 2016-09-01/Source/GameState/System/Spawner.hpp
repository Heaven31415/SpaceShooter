#pragma once

#include "../../Common/Context.hpp"
#include <queue>

class World;

typedef std::function<void()> Spawn;

struct SpawnAction
{
    SpawnAction() : time(sf::Time::Zero), spawn() {}
    SpawnAction(sf::Time _time, Spawn _spawn) : time(_time), spawn(_spawn) {}
    sf::Time time;
    Spawn spawn;
};

class Spawner
{
public:
    Spawner(Context* context, World* world);

private:
};
