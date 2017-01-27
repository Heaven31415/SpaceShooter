#include "../Include/MenuState.hpp"

const sf::Time MenuState::TimePerFrame = sf::seconds(1.f / 60.f);

MenuState::MenuState(Context * context)
: m_context(context)
, m_exitFlag({ false, State::Exit })
, m_cursor(context->textures.get("Cursor"))
, m_gui(context->window)
, m_particleSystem()
{
    m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(context->window)));
    buildGui();
    buildParticleSystem();
}

State::Type MenuState::run()
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

void MenuState::handleInput()
{
    sf::Event event;
    auto& window = m_context->window;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                    m_exitFlag = { true, State::Exit };
            }
            break;

            case sf::Event::Closed:
            {
                m_exitFlag = { true, State::Exit };
            }
            break;

            case sf::Event::MouseLeft:
            {
                m_cursor.setColor({ 0,0,0,0 });
            }
            break;

            case sf::Event::MouseEntered:
            {
                m_cursor.setColor({ 255,255,255,255 });
            }
            break;

            m_gui.handleEvent(event);
        }
    }
}

void MenuState::update(sf::Time dt)
{
    m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_context->window)));
    m_particleSystem.update(dt);
}

void MenuState::render()
{
    auto& window = m_context->window;

    window.clear();
    m_gui.draw();
    window.draw(m_cursor);
    window.draw(m_particleSystem);
    window.display();
}

void MenuState::buildGui()
{
    tgui::Theme theme{ "Resources/Widgets/Black.txt" };

    auto backgroundPicture = tgui::Picture::create(m_context->textures.get("Menu"), false);
    backgroundPicture->setSize(tgui::bindSize(m_gui));

    auto label = tgui::Label::create("Space Shooter");
    label->setPosition("(parent.width - width) / 2", "parent.height * 0.05");
    label->setTextSize(60);
    label->setRenderer(theme.getRenderer("Label"));

    auto newGameBtn = tgui::Button::create("New Game");
    newGameBtn->setPosition("(parent.width - width) / 2", "parent.height * 0.3");
    newGameBtn->setSize("parent.width * 0.25", "parent.height * 0.1");
    newGameBtn->setRenderer(theme.getRenderer("Button"));
    
    auto optionsBtn = tgui::Button::copy(newGameBtn);
    optionsBtn->setText("Options");
    optionsBtn->setPosition(tgui::bindLeft(newGameBtn), tgui::bindBottom(newGameBtn));

    auto authorsBtn = tgui::Button::copy(newGameBtn);
    authorsBtn->setText("Authors");
    authorsBtn->setPosition(tgui::bindLeft(newGameBtn), tgui::bindBottom(optionsBtn));

    auto exitBtn = tgui::Button::copy(newGameBtn);
    exitBtn->setText("Exit");
    exitBtn->setPosition(tgui::bindLeft(newGameBtn), tgui::bindBottom(authorsBtn));

    auto mainMenu = tgui::Panel::create({ tgui::bindWidth(m_gui), tgui::bindHeight(m_gui) });
    mainMenu->add(backgroundPicture, "backgroundPicture");
    mainMenu->add(newGameBtn, "newGame");
    mainMenu->add(optionsBtn, "optionsBtn");
    mainMenu->add(authorsBtn, "authorsBtn");
    mainMenu->add(exitBtn, "exitBtn");
    m_gui.add(mainMenu);
    m_gui.add(label);
}

void MenuState::buildParticleSystem()
{
    thor::UniversalEmitter emitter;
    emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));
    emitter.setEmissionRate(10.f);
    emitter.setParticleScale([]() {return sf::Vector2f(thor::random(0.05f, 0.1f), thor::random(0.05f, 0.1f)); });
    emitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(1.f), sf::seconds(5.f)));
    emitter.setParticlePosition(thor::Distributions::circle({ 400.f, 320.f }, 50.f));

    thor::ForceAffector affector{ { 0.f, 10.0f } };
    m_particleSystem.setTexture(m_context->textures.get("Particle"));
    m_particleSystem.addAffector(affector);
    m_particleSystem.addEmitter(emitter);
}
