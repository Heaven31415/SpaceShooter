#pragma once

#include "../../PhysicalObject.hpp"
#include "../../System/CollisionHandler.hpp"
#include "../../../Common/Context.hpp"

class Player;

struct LaserData
{
    LaserData()
        : type(Type::None), velocity(), textureName("") {}
    LaserData(Type::Type _type, sf::Vector2f _velocity, std::string _textureName)
        : type(_type), velocity(_velocity), textureName(_textureName) {}

    Type::Type type;
    sf::Vector2f velocity;
    std::string textureName;
};

class Laser : public PhysicalObject
{
public:
    typedef std::unique_ptr<Laser> Ptr;
                                        Laser(Context& context, World& world, LaserData data);
                                        ~Laser();
    virtual void                        collision(PhysicalObject* object) override;
    virtual void                        update(sf::Time dt) override;
    void                                setOwner(PhysicalObject* owner);

private:
    PhysicalObject*                     m_owner;
    const GraphicsFrames                m_frames;
};