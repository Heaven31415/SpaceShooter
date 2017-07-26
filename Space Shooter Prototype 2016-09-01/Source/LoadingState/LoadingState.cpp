#include "../Include/LoadingState.hpp"

const sf::Time LoadingState::TimePerFrame = sf::seconds(1.f / 30.f);

LoadingState::LoadingState(Context* context)
: m_context(context)
, m_exitFlag({false, State::Exit})
, m_loadingBarFill({756.f, 36.f})
, m_loadingBarBackground({760.f, 40.f})
, m_resourcesLoaded(false)
, m_loadingTextTimer(sf::Time::Zero)
{
    // Before loading occurs we need to have access to some special resources
    // TODO: Handle it in a different way
    if (!m_backgroundTexture.loadFromFile("Resources/Graphics/Background.png"))
        throw std::runtime_error("\"Resources/Graphics/Background.png\" is missing!");
    m_background.setTexture(m_backgroundTexture);

    if (!m_cursorTexture.loadFromFile("Resources/Graphics/Cursor.png"))
        throw std::runtime_error("\"Resources/Graphics/Cursor.png\" is missing!");
    m_cursor.setTexture(m_cursorTexture);
    ts::centerOrigin(m_cursor);

    if (!m_loadingTextFont.loadFromFile("Resources/Fonts/Candara.ttf"))
        throw std::runtime_error("\"Resources/Fonts/Candara.ttf\" is missing!");
    m_loadingText.setFont(m_loadingTextFont);

    if(!m_loadingTheme.openFromFile("Resources/Music/LoadingTheme.ogg"))
        throw std::runtime_error("\"Resources/Music/LoadingTheme.ogg\" is missing!");
    m_loadingTheme.play();

    // loading text properties
    m_loadingText.setString("Loading...");
    m_loadingText.setOutlineThickness(1.f);
    ts::centerOrigin(m_loadingText);
    m_loadingText.setPosition(400, 540 - m_loadingText.getLocalBounds().height * 1.1f);

    // fill loading bar properties
    m_loadingBarFill.setPosition(22.f, 542.f);
    m_loadingBarFill.setFillColor({ 46, 8, 84 });

    // background loding bar properties
    m_loadingBarBackground.setPosition(20.f, 540.f);
    m_loadingBarBackground.setFillColor({ 155, 155, 155 });

    // load resources in different threads
    m_context->textures.load();
    m_context->sounds.load();
    m_context->fonts.load();
}

State::Type LoadingState::run()
{
    sf::Clock clock;
    sf::Time dt = sf::Time::Zero;
    auto& window = m_context->window;

    while (window.isOpen())
    {
        dt += clock.restart();
        while (dt >= TimePerFrame)
        {
            handleInput();
            update(TimePerFrame);
            dt -= TimePerFrame;
        }
        render();

        if (m_exitFlag.first == true)
        {
            m_exitFlag.first = false;
            return m_exitFlag.second;
        }
    }

    return State::Exit;
}

void LoadingState::handleInput()
{
    sf::Event event;
    auto& window = m_context->window;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_exitFlag = { true, State::Exit };
        else if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) && m_resourcesLoaded)
            m_exitFlag = { true, State::Game };
    }
}

void LoadingState::update(sf::Time dt)
{
    m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_context->window)));

    if (!m_resourcesLoaded)
    {
        m_loadingTextTimer += dt;

        float soundsProgress = m_context->sounds.getProgress();
        float texturesProgress = m_context->textures.getProgress();
        float progress = (soundsProgress + texturesProgress) / 2.f;
        m_loadingBarFill.setSize({ 756.f * progress, 36.f });

        if (m_loadingTextTimer >= sf::seconds(0.75f))
        {
            auto text = m_loadingText.getString();
            if (text == "Loading.") text = "Loading..";
            else if (text == "Loading..") text = "Loading...";
            else text = "Loading.";

            m_loadingText.setString(text);
            m_loadingTextTimer = sf::Time::Zero;
        }

        if (progress == 1.f)
        {
            m_loadingText.setString("Press any key to continue...");
            ts::centerOrigin(m_loadingText);
            auto x = static_cast<float>(m_context->window.getSize().x) / 2.f;
            auto y = m_loadingText.getPosition().y;
            m_loadingText.setPosition(x, y);
            m_loadingTheme.stop();
            m_resourcesLoaded = true;
        }
    }
}

void LoadingState::render()
{
    auto& window = m_context->window;

    window.clear();
    window.draw(m_background);
    window.draw(m_loadingBarBackground);
    window.draw(m_loadingBarFill);
    window.draw(m_loadingText);
    window.draw(m_cursor);
    window.display();
}