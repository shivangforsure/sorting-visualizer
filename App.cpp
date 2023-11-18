#include "stdafx.h"
#include "App.h"

// init methods:
void App::initVariables()
{
    this->delay = 0.f;
    this->timer = 0.f;
    this->endApp = false;
    this->videoMode = sf::VideoMode::getDesktopMode();
    this->videoMode.width = 1600;
    this->videoMode.height = 900;
    this->font.loadFromFile("Resources\\Fonts\\Hetika.otf");
}

void App::initWindow()
{
    this->window = new sf::RenderWindow(this->videoMode, "Sorting Visualier", sf::Style::Close);
    this->window->setVerticalSyncEnabled(false);
    this->window->setKeyRepeatEnabled(false);

    sf::VideoMode temp = sf::VideoMode::getDesktopMode();
    this->window->setPosition(
        sf::Vector2i(
            temp.width / 2 - this->videoMode.width / 2,
            temp.height / 2 - this->videoMode.height / 2
        )
    );

    // ikonka okna:
    sf::Image image;
    image.loadFromFile("Resources\\Textures\\windowIcon.png");
    this->window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

void App::initSet()
{
    delete this->set;
    this->set = new Set(
        100,
        sf::Vector2u(this->videoMode.width, this->videoMode.height),
        sf::Color(0, 170, 255, 255)
    );
}

void App::initButtons()
{
    this->leftSwitches["STOP"] = new Switch(
        60.f, 150.f,
        225.f, 90.f,
        sf::Color(0, 170, 255, 255), sf::Color(125, 210, 255, 255), sf::Color(160, 160, 160, 255), sf::Color(200, 200, 200, 255),
        sf::Color(0, 150, 225, 255), sf::Color(100, 100, 100, 255), 4.f,
        this->font, "STOP", 50, sf::Color::White, true
    );

    this->leftButtons["RESTART"] = new Button(
        60.f, 290.f,
        230.f, 90.f,
        sf::Color(50, 200, 50, 255), sf::Color(50, 250, 50, 255), sf::Color(50, 150, 50, 255),
        sf::Color(0, 150, 0, 255), 4.f,
        this->font, "RESTART", 50, sf::Color::White
    );

    this->leftButtons["NEW SET"] = new Button(
        60.f, 430.f,
        230.f, 90.f,
        sf::Color(50, 200, 50, 255), sf::Color(50, 250, 50, 255), sf::Color(50, 150, 50, 255),
        sf::Color(0, 150, 0, 255), 4.f,
        this->font, "NEW SET", 50, sf::Color::White
    );

    this->leftButtons["EXIT"] = new Button(
        60.f, 570.f,
        230.f, 90.f,
        sf::Color(50, 200, 50, 255), sf::Color(50, 250, 50, 255), sf::Color(50, 150, 50, 255),
        sf::Color(0, 150, 0, 255), 4.f,
        this->font, "EXIT", 50, sf::Color::White
    );

    this->rightSwitches["BUBBLE"] = new Switch(
        1310.f, 150.f,
        230.f, 90.f,
        sf::Color(0, 170, 255, 255), sf::Color(125, 210, 255, 255), sf::Color(160, 160, 160, 255), sf::Color(200, 200, 200, 255),
        sf::Color(0, 150, 225, 255), sf::Color(100, 100, 100, 255), 4.f,
        this->font, "BUBBLE", 50, sf::Color::White, false
    );

    this->rightSwitches["SELECTION"] = new Switch(
        1310.f, 290.f,
        230.f, 90.f,
        sf::Color(0, 170, 255, 255), sf::Color(125, 210, 255, 255), sf::Color(160, 160, 160, 255), sf::Color(200, 200, 200, 255),
        sf::Color(0, 150, 225, 255), sf::Color(100, 100, 100, 255), 4.f,
        this->font, "SELECTION", 50, sf::Color::White, false
    );

    this->rightSwitches["HEAP"] = new Switch(
        1310.f, 430.f,
        230.f, 90.f,
        sf::Color(0, 170, 255, 255), sf::Color(125, 210, 255, 255), sf::Color(160, 160, 160, 255), sf::Color(200, 200, 200, 255),
        sf::Color(0, 150, 225, 255), sf::Color(100, 100, 100, 255), 4.f,
        this->font, "HEAP", 50, sf::Color::White, true
    );

    this->rightSwitches["QUICK"] = new Switch(
        1310.f, 570.f,
        230.f, 90.f,
        sf::Color(0, 170, 255, 255), sf::Color(125, 210, 255, 255), sf::Color(160, 160, 160, 255), sf::Color(200, 200, 200, 255),
        sf::Color(0, 150, 225, 255), sf::Color(100, 100, 100, 255), 4.f,
        this->font, "QUICK", 50, sf::Color::White, false
    );
}

void App::initSpeedModifier()
{
    this->speedModifier = new SpeedModifier(
        60.f, 710.f,
        25,
        150.f, true,
        "Resources\\Textures\\axis.png", "Resources\\Textures\\handle.png",
        "Resources\\Textures\\axisHovered.png", "Resources\\Textures\\handleHovered.png",
        "Resources\\Textures\\axisPressed.png", "Resources\\Textures\\handlePressed.png"
    );
}

// constructor / destructor:
App::App()
{
    this->initVariables();
    this->initWindow();
    this->initSet();
    this->initButtons();
    this->initSpeedModifier();
}

App::~App()
{
    for (auto& it : this->leftSwitches)
        delete it.second;
    for (auto& it : this->leftButtons)
        delete it.second;
    for (auto& it : this->rightSwitches)
        delete it.second;

    delete this->set;
    delete this->speedModifier;
    delete this->window;
}

void App::updateDt()
{
    this->timer += this->clock.restart().asMilliseconds();
}

void App::update()
{
    this->updateSfmlEvents();
    this->updateMousePos();
    this->updateSpeedModifier();
    this->updateButtons();
    this->updateSorting();
}

void App::updateSfmlEvents()
{
    sf::Event event;
    while (this->window->pollEvent(event))
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            this->endApp = true;
}

void App::updateMousePos()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void App::updateSpeedModifier()
{
    this->speedModifier->update(this->mousePosWindow);
    this->delay = this->speedModifier->getValue();


    if (this->delay > this->speedModifier->getMaxValue() * 0.9f)
    {

        if (this->set->getStep() != 0)
            this->delay = this->speedModifier->getValue() * 5.f;
    }
}

void App::updateButtons()
{

    for (auto& it : this->leftSwitches)
        it.second->update(this->mousePosWindow);

    for (auto& it : this->leftButtons)
        it.second->update(this->mousePosWindow);

    for (auto& it : this->rightSwitches)
        it.second->update(this->mousePosWindow);

    if (this->leftButtons["RESTART"]->isClicked())
        this->set->restart();

    if (this->leftButtons["NEW SET"]->isClicked())
        this->initSet();

    if (this->leftButtons["EXIT"]->isClicked())
        this->endApp = true;


    if (this->rightSwitches[this->set->getSortType()]->getChange())
        this->rightSwitches[this->set->getSortType()]->setOn(true);


    for (auto& it : this->rightSwitches)
        if (it.first != this->set->getSortType() && it.second->isTurnedOn())
        {
            this->rightSwitches[this->set->getSortType()]->setOn(false);
            this->set->setSortType(it.first);
            break;
        }
}

void App::updateSorting()
{
    if (this->timer >= this->delay)
    {
        this->timer = 0.f;

        if (!this->leftSwitches["STOP"]->isTurnedOn())
        {

            this->set->update();
            this->set->update();
        }

        if (this->set->isSorted())
            this->leftSwitches["STOP"]->setOn(true);
    }
}

void App::render()
{
    this->window->clear(sf::Color(45, 45, 45, 45));

    for (auto& it : this->leftSwitches)
        it.second->render(*this->window);

    for (auto& it : this->leftButtons)
        it.second->render(*this->window);

    for (auto& it : this->rightSwitches)
        it.second->render(*this->window);

    this->set->render(*this->window);

    this->speedModifier->render(*this->window);

    this->window->display();
}

void App::run()
{
    while (this->window->isOpen() && !this->endApp)
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
