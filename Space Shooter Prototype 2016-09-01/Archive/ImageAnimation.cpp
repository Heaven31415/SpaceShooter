#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Randomizer.hpp"

class ImageAnimation
{
public:
    ImageAnimation(const std::string& filepath)
    : m_timer(sf::Time::Zero)
    {
        sf::Image image;
        image.loadFromFile(filepath);
        sf::Vector2u size = image.getSize();

        m_image.create(size.x, size.y, sf::Color::Black);
        for (std::size_t y = 0; y < size.y; ++y)
            for (std::size_t x = 0; x < size.x; ++x)
                m_pixels.push_back({ { x, y }, image.getPixel(x, y) });

        auto engine = std::default_random_engine{};
        std::shuffle(std::begin(m_pixels), std::end(m_pixels), engine);
    }

    void update(sf::Time dt)
    {
        m_timer += dt;
        Randomizer random;

        while (m_timer >= sf::seconds(0.1f))
        {
            for (std::size_t i = 0; i < 5000; ++i)
            {
                if (m_pixels.empty()) break;;
                auto& pair = m_pixels.back();
                m_image.setPixel(pair.first.x, pair.first.y, pair.second);
                m_pixels.pop_back();
            }
            m_timer -= sf::seconds(0.1f);
        }
    }

    void draw(sf::RenderTarget& target)
    {
        m_texture.loadFromImage(m_image);
        target.draw(sf::Sprite(m_texture));
    }

private:
    sf::Texture                                     m_texture;
    sf::Image                                       m_image;
    std::vector<std::pair<sf::Vector2u, sf::Color>> m_pixels;
    sf::Time                                        m_timer;
};

int main()
{
    sf::RenderWindow window({ 800, 600 }, "Test");
    sf::Clock clock;
    sf::Time dt = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

    ImageAnimation animation("test.png");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        dt += clock.restart();

        while (dt >= timePerFrame)
        {
            animation.update(timePerFrame);
            dt -= timePerFrame;
        }

        window.clear();
        animation.draw(window);
        window.display();
    }
}