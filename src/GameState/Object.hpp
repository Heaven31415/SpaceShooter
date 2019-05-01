#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include "GUID.hpp"

struct Context;
class Game;
class World;

namespace Type
{
    enum Type : unsigned
    {
        None            = 0,
        Special         = 0,
        Player          = 1,
        Enemy           = 2,
        EnemyWeapon     = 4,
        PlayerWeapon    = 8,
        Pickup          = 16,
        Visual          = 32, // NYI
    };
}

class Object : public sf::Transformable, public sf::Drawable
{
public:
    typedef std::unique_ptr<Object> Ptr;

                            Object(Context& context, World& world, Type::Type type);
                            Object(Context& context, World& world, Type::Type type, const sf::Texture& texture);
                            Object(Context& context, World& world, Type::Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
    virtual                ~Object();
    virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void            update(sf::Time dt);

public:
    Context&                getContext();
    World&                  getWorld();
    GUID                    getGUID() const;
    Type::Type              getType() const;
    sf::FloatRect           getLocalBounds() const;
    sf::FloatRect           getGlobalBounds() const;
    void                    setTexture(const sf::Texture& texture);
    const sf::Texture*      getTexture() const;
    void                    setTextureRect(const sf::IntRect& rectangle);
    const sf::IntRect&      getTextureRect() const;
    void                    setColor(const sf::Color& color);
    sf::Color               getColor() const;
    void                    centerOrigin();
    void                    setVelocity(sf::Vector2f velocity);
    sf::Vector2f            getVelocity() const;
    void                    setMaxVelocity(sf::Vector2f velocity);
    sf::Vector2f            getMaxVelocity() const;
    void                    erase();
    bool                    isErasable() const;

protected:
    sf::Vector2f            m_velocity;
    sf::Vector2f            m_maxVelocity;

private:
    Context&                m_context;
    World&                  m_world;
    const GUID              m_guid;
    Type::Type              m_type;
    sf::Sprite              m_sprite;
    bool                    m_erasable;
};