#pragma once

#include "EnemyState.hpp"

namespace Aggressor
{
    enum Type
    {
        Search,
        Move,
        Positioning,
        Shooting,
        Evading,
    };
}

class EnemyAggressor : public EnemyStateManager
{
public:
    EnemyAggressor();

    struct Search : public EnemyState
    {
        Search();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);
    };

    struct Move : public EnemyState
    {
        Move();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);
    };

    struct Positioning : public EnemyState
    {
        Positioning();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);

        std::pair<float, float> horizontalDistance;
        std::pair<float, float> verticalDistance;
    };

    struct Shooting : public EnemyState
    {
        Shooting();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);

        std::size_t fired;
        sf::Time cooldown;
    };

    struct Evading : public EnemyState
    {
        Evading();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);

        sf::Time time;
    };
};
