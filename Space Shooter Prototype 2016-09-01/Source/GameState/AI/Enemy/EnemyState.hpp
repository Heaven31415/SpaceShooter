#pragma once

class Enemy;
class Object;
class PhysicalObject;
class World;

#include <map>
#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include "../../GUID.hpp"

struct Message
{

    enum class Type
    {
        Int,
        Float,
        Vector2f,
        Object,
        PhysicalObject,
        GUID
    } type;

    union
    {
        int Int;
        float Float;
        sf::Vector2f Vector2f;
        Object* Object;
        PhysicalObject* PhysicalObject;
        GUID Guid;
    };
};

class EnemyState
{
public:
    typedef std::unique_ptr<EnemyState> Ptr;
    virtual ~EnemyState() {}
    virtual void update(Enemy* enemy, sf::Time dt, Message* message) = 0;
};

class EnemyStateManager
{
public:
    EnemyStateManager();
    typedef std::unique_ptr<EnemyStateManager> Ptr;
    virtual void                                    changeState(unsigned state);
    virtual void                                    update(Enemy* enemy, sf::Time dt);

protected:
    unsigned                                        m_actual;
    std::map<unsigned, EnemyState::Ptr>             m_states;
    Message                                         m_message;
};