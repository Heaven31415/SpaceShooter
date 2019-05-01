#include "EnemyAggressor.hpp"
#include "../../World.hpp"
#include "../../PhysicalObject/Enemies/Enemy.hpp"

EnemyAggressor::EnemyAggressor()
{
    m_actual = Aggressor::Search;
    // states could share information by passing some shared pointer/reference to all of them here
    m_states[Aggressor::Search] = std::make_unique<EnemyAggressor::Search>();
    m_states[Aggressor::Move] = std::make_unique<EnemyAggressor::Move>();
    m_states[Aggressor::Positioning] = std::make_unique<EnemyAggressor::Positioning>();
    m_states[Aggressor::Shooting] = std::make_unique<EnemyAggressor::Shooting>();
    m_states[Aggressor::Evading] = std::make_unique<EnemyAggressor::Evading>();
}

EnemyAggressor::Search::Search()
{
}

void EnemyAggressor::Search::update(Enemy * enemy, sf::Time dt, Message * message)
{
    auto* player = enemy->getWorld().getPlayer();
    if (player && !player->isDestroyed()) // player found and alive
    {
        message->type = Message::Type::GUID;
        message->Guid = player->getGUID();
        enemy->changeState(Aggressor::Positioning);
    }
    else
    {
        enemy->setVelocity(enemy->getMaxVelocity());
        enemy->changeState(Aggressor::Move); // player not found, let's just fly!
    }  
}

EnemyAggressor::Move::Move()
{
}

void EnemyAggressor::Move::update(Enemy * enemy, sf::Time dt, Message * message)
{
    enemy->update(dt);
}

EnemyAggressor::Positioning::Positioning()
: horizontalDistance{50.f, 100.f}
, verticalDistance{100.f, 250.f}
{
}

void EnemyAggressor::Positioning::update(Enemy * enemy, sf::Time dt, Message * message)
{
    auto* player = enemy->getWorld().getObject(message->Guid);
    if (player)
    {
        auto playerPos = player->getPosition();
        auto enemyPos = enemy->getPosition();
        sf::Vector2f enemyMaxVelocity = enemy->getMaxVelocity();
        sf::Vector2f newVelocity{ 0.f, 0.f };

        auto dx = playerPos.x - enemyPos.x;
        if (std::abs(dx) < horizontalDistance.first)
        {
            // they are too close, enemy is on the right side of player
            if (dx < -25.f) newVelocity.x = enemyMaxVelocity.x;
            else if(dx > 25.f) newVelocity.x = -enemyMaxVelocity.x;
        }
        else if (std::abs(dx) > horizontalDistance.second)
        {
            // they are too far, player is on the right side of enemy
            if(dx > 25.f) newVelocity.x = enemyMaxVelocity.x;
            else if(dx < -25.f) newVelocity.x = -enemyMaxVelocity.x;
        }

        auto dy = playerPos.y - enemyPos.y;
        if (std::abs(dy) < verticalDistance.first)
        {
            // they are too close, enemy is below player
            if (dy < -25.f) newVelocity.y = enemyMaxVelocity.y;
            else if(dy > 25.f) newVelocity.y = -enemyMaxVelocity.y;
        }
        else if (std::abs(dy) > verticalDistance.second)
        {
            // they are too far, player is below enemy
            if (dy > 25.f) newVelocity.y = enemyMaxVelocity.y;
            else if(dy < -25.f) newVelocity.y = -enemyMaxVelocity.y;
        }

        enemy->setVelocity(newVelocity);

        // if it's in position, let's shoot
        if (newVelocity == sf::Vector2f(0.f, 0.f))
            enemy->changeState(Aggressor::Shooting);

    }
}

EnemyAggressor::Shooting::Shooting()
: fired(0)
, cooldown(sf::seconds(0.3f))
{
}

void EnemyAggressor::Shooting::update(Enemy * enemy, sf::Time dt, Message * message)
{
    auto* player = enemy->getWorld().getObject(message->Guid);
    if (player)
    {
        sf::Vector2f maxVelocity = enemy->getMaxVelocity();
        sf::Vector2f newVelocity = enemy->getVelocity();
        auto dx = enemy->getPosition().x - player->getPosition().x;
        // assume that player will be moving when we are shooting
        // try to anticipate where to move before next shoot to be
        // more efective
        if (dx > 25.f)
            newVelocity.x = -maxVelocity.x;
        else if(dx < -25.f)
            newVelocity.x = maxVelocity.x;

        enemy->setVelocity(newVelocity);

        if (cooldown <= dt)
        {
            enemy->addLaser();
            enemy->getContext().soundSystem.playSound("EnemyLaser");
            fired++;
            cooldown = sf::seconds(0.3f);
        }
        else cooldown -= dt;

        if (fired == 3)
        {
            enemy->changeState(Aggressor::Evading);
            fired = 0;
        }
    }
}

EnemyAggressor::Evading::Evading()
: time(sf::seconds(2.f))
{
}

void EnemyAggressor::Evading::update(Enemy * enemy, sf::Time dt, Message * message)
{
    auto* player = enemy->getWorld().getObject(message->Guid);
    if (player)
    {
        sf::Vector2f maxVelocity = enemy->getMaxVelocity();
        sf::Vector2f newVelocity{ 0.f, -maxVelocity.y * 0.5f };

        if (player->getPosition().x < enemy->getPosition().x)
            newVelocity.x = maxVelocity.x;
        else
            newVelocity.x = -maxVelocity.x;

        enemy->setVelocity(newVelocity);

        if (time <= dt)
        {
            enemy->changeState(Aggressor::Positioning);
            time = sf::seconds(2.f);
        }
        else time -= dt;
    }
}
