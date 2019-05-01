#pragma once

#include "Weapons\LaserFactory.hpp"
#include "../PhysicalObject.hpp"
#include "../../Common/Context.hpp"
#include "../../Common/Observer.hpp"

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
                                        Player(Context& context, World& world, LaserFactory& laserFactory);
    virtual void                        collision(PhysicalObject* object) override;
    void                                onEnemyKilled(PhysicalObject* object); // callback
    void                                setGraphicsFrame(Player::Frame frame);
    void                                addWeapon(Player::Weapon weapon);
    std::size_t                         getWeaponCount();
    bool                                canAddWeapon();

private:
    LaserFactory&                       m_laserFactory;
    const GraphicsFrames                m_frames;
    const std::size_t                   m_maxWeaponCount;
};