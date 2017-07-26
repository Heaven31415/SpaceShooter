#pragma once

#include "Context.hpp"
#include "Observer.hpp"
#include "PhysicalObject.hpp"
#include "Laser.hpp"

class World;

class Player : public PhysicalObject
{
public:
    enum class Frame
    {
        Straight,
        Left,
        Right
    };

    enum class Weapon
    {
        Laser,
    };
                                        Player(Context* context, World* world);
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        draw(sf::RenderTarget& target) const override;

    void                                onEnemyKilled(PhysicalObject* object); // callback

    void                                setGraphicsFrame(Player::Frame frame);
    void                                addWeapon(Player::Weapon weapon);
    std::size_t                         getWeaponCount();
    bool                                canAddWeapon();

private:
    Context*                            m_context;
    World*                              m_world;

private:
    std::map<std::string, sf::IntRect>  m_frames;
    const std::size_t                   m_maxWeaponCount;
};