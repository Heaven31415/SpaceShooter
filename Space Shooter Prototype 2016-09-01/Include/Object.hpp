#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

namespace Type
{
    enum Type : unsigned
    {
        Special         = 0,
        Player          = 1,
        Enemy           = 2,
        EnemyWeapon     = 4,
        PlayerWeapon    = 8,
        Pickup          = 16,
    };
}

class Object : public sf::Transformable
{
public:
    typedef std::unique_ptr<Object> Ptr;
    
                            Object(Type::Type type);
                            Object(Type::Type type, const sf::Texture& texture);
                            Object(Type::Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
    virtual                ~Object();
    virtual void            draw(sf::RenderTarget& target) const;
    virtual void            update(sf::Time dt);

public:
    Type::Type              getType() const;
    sf::FloatRect           getLocalBounds() const;
    sf::FloatRect           getGlobalBounds() const;
    void                    setTexture(const sf::Texture& texture);
    void                    setTextureRect(const sf::IntRect& rectangle);
    void                    setColor(const sf::Color& color);
    void                    centerOrigin();

protected:
    Type::Type              m_type;

private:
    sf::Sprite              m_sprite;
};