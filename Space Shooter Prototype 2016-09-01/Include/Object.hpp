#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

namespace Type
{
    enum Type : unsigned
    {
        Special = 0,
        Handler = 0,
        Player = 1,
        Enemy = 2,
        EnemyWeapon = 4,
        PlayerWeapon = 8,
    };
}


class Object : public sf::Transformable
{
public:
    
                            Object(Type::Type type);
                            Object(Type::Type type, const sf::Texture& texture);
                            Object(Type::Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
    virtual void            draw(sf::RenderTarget& target) const;
    virtual void            update(sf::Time dt) = 0;

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