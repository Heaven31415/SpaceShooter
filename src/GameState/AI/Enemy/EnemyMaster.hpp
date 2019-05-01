#pragma once

#include "EnemyState.hpp"

namespace Master
{
    enum Type
    {
        Move,
        Evade,
    };
}

class EnemyMaster : public EnemyStateManager
{
public:
    EnemyMaster();

    struct Move : public EnemyState
    {
        Move();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);

        float minDistance;
        float maxDistance;
    };

    struct Evade : public EnemyState
    {
        Evade();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);
    };
};
