#pragma once

class Enemy;
class World;

#include <map>
#include <memory>
#include <SFML/System/Time.hpp>

class EnemyState
{
public:
    enum Type
    {
        Chasing,
        HorizontalPositioning,
        Shooting,
        Evading,
    };
    typedef std::unique_ptr<EnemyState> Ptr;
    virtual ~EnemyState() {}
    virtual void update(Enemy* enemy, sf::Time dt) = 0;
};

class EnemyChasing : public EnemyState
{
public:
    EnemyChasing();
    virtual void update(Enemy* enemy, sf::Time dt);

private:
    float m_distance;
};

class EnemyHorizontalPositioning : public EnemyState
{
public:
    EnemyHorizontalPositioning();
    virtual void update(Enemy* enemy, sf::Time dt);

private:
    float m_distance;
};

class EnemyShooting : public EnemyState
{
public:
    EnemyShooting();
    virtual void update(Enemy* enemy, sf::Time dt);

private:
    std::size_t m_fired;
    sf::Time m_cooldown;
};

class EnemyEvading : public EnemyState
{
public:
    EnemyEvading();
    virtual void update(Enemy* enemy, sf::Time dt);

private:
    sf::Time m_time;
};

class EnemyStateManager
{
public:
                                                    EnemyStateManager();
    void                                            changeState(EnemyState::Type state);
    void                                            update(Enemy* enemy, sf::Time dt);
private:
    EnemyState::Type                                m_actual;
    std::map<EnemyState::Type, EnemyState::Ptr>     m_states;
};