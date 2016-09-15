#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

class Object : public sf::Transformable
{
public:
    enum class Type
    {
        Special         = -1,
        Handler         = -1,
        Match           = +1,
        Player          = +3,
        EnemyWeapon     = +4,
        Enemy           = +6,
        PlayerWeapon    = +7,
    };
                            Object(Type type);
                            Object(Type type, const sf::Texture& texture);
                            Object(Type type, const sf::Texture& texture, const sf::IntRect& rectangle);
    virtual void            collision() = 0;
    virtual void            draw(sf::RenderTarget& target) const;
    virtual void            update(sf::Time dt) = 0;
    virtual void            monitor() = 0;

public:
    Object::Type            getType() const;
    sf::FloatRect           getLocalBounds() const;
    sf::FloatRect           getGlobalBounds() const;
    bool                    isDestroyed() const;
    void                    destroy();
    void                    setTexture(const sf::Texture& texture);
    void                    setTextureRect(const sf::IntRect& rectangle);
    void                    setColor(const sf::Color& color);
    void                    centerOrigin();

protected:
    Object::Type            m_type;

private:
    sf::Sprite              m_sprite;
    bool                    m_destroyed;
};