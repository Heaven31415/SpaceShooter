#include "MenuState.hpp"
#include "../Game.hpp"

const sf::Time MenuState::TimePerFrame = sf::seconds(1.f / 60.f);

MenuState::MenuState(Context * context)
: m_context(context)
, m_exitFlag({ false, State::Exit })
, m_cursor(context->textures.get("Cursor"))
, m_gui(context->window)
{
    m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(context->window)));
    buildGui();
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
        m_gui.handleEvent(event);
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
        }
    }
}

void MenuState::update(sf::Time dt)
{
    m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_context->window)));
}

void MenuState::render()
{
    auto& window = m_context->window;

    window.clear();
    m_gui.draw();
    window.draw(m_cursor);
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

void MenuState::buildOptions()
{
    auto& videoMode = sf::VideoMode::getFullscreenModes()[0];

    auto widthLabel = tgui::Label::create("Width: " + std::to_string(videoMode.width));
    widthLabel->setPosition("(parent.width - width) / 2", "0.2 * parent.height");

    auto heightLabel = tgui::Label::create("Height: " + std::to_string(videoMode.height));
    heightLabel->setPosition("(parent.width - width) / 2", "0.3 * parent.height");

    auto bppLabel = tgui::Label::create("BPP: " + std::to_string(videoMode.bitsPerPixel));
    bppLabel->setPosition("(parent.width - width) / 2", "0.4 * parent.height");

    auto slider = tgui::Slider::create(0, sf::VideoMode::getFullscreenModes().size() - 1);
    slider->setPosition("(parent.width - width) / 2", "0.1 * parent.height");
    slider->connect("valueChanged", 
        [=](int value) {
        auto& videoMode = sf::VideoMode::getFullscreenModes()[value];
        widthLabel->setText("Width: " + std::to_string(videoMode.width));
        heightLabel->setText("Height: " + std::to_string(videoMode.height));
        bppLabel->setText("BPP: " + std::to_string(videoMode.bitsPerPixel));
        });

    auto& window = m_context->window;
    auto applyButton = tgui::Button::create("Apply");
    applyButton->setPosition("(parent.width - width) / 2", "0.5 * parent.height");
    applyButton->connect("pressed", [&window,slider]() {
        window.create(sf::VideoMode::getFullscreenModes()[slider->getValue()], Game::Config.windowTitle);
        window.setMouseCursorVisible(false);
        window.setKeyRepeatEnabled(Game::Config.keyRepeatEnabled);
        window.setVerticalSyncEnabled(Game::Config.verticalSyncEnabled);
    });

    m_gui.add(widthLabel);
    m_gui.add(heightLabel);
    m_gui.add(bppLabel);
    m_gui.add(slider);
    m_gui.add(applyButton);
}
