#pragma once

#include "EnemyState.hpp"

namespace Aggressor
{
    enum Type
    {
        VerticalPositioning,
        HorizontalPositioning,
        Shooting,
        Evading,
    };
}

class EnemyAggressor : public EnemyStateManager
{
public:
    EnemyAggressor();

    struct VerticalPositioning : public EnemyState
    {
        VerticalPositioning();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);

        float minDistance;
        float maxDistance;
    };

    struct HorizontalPositioning : public EnemyState
    {
        HorizontalPositioning();
        virtual void update(Enemy* enemy, sf::Time dt, Message* message);

        float distance;
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
