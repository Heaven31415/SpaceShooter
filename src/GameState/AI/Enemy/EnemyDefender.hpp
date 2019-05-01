#pragma once

#include "EnemyState.hpp"

namespace Defender
{
    enum Type
    {
        Move,
        Search,
        Protect,
    };
}

class EnemyDefender : public EnemyStateManager
{
public:
    EnemyDefender();

    struct Move : public EnemyState
    {
        Move();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);

        float horizontalDist[2];
        float verticalDist[2];
    };

    struct Search : public EnemyState
    {
        Search();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);
    };
};

