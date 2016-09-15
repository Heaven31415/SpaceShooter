#pragma once

#include "Context.hpp"
#include "Object.hpp"

class Laser : public Object
{
    enum class Status
    {
        Alive,
        Explosion,
        Destroyed,
    };
public:
                                        Laser(Object::Type type, Context* context, const sf::Vector2f& position);
    virtual void                        collision() override;
    virtual void                        draw(sf::RenderTarget& target) const;
    virtual void                        update(sf::Time dt) override;
    virtual void                        monitor() override;

    void                                updateStatus();
    bool                                readyToErase() const;

private:
    Status                              m_status;
    Context*                            m_context;
    float                               m_velocity;
    bool                                m_exploded;
    std::map<std::string, sf::IntRect>  m_frames;
    sf::Time                            m_explosionTimer;
};