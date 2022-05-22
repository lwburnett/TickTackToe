#include "GameMaster.h"
#include "GameTime.h"
#include "IScreen.h"
#include "MainMenuScreen.h"
#include "WindowManager.h"

GameMaster::GameMaster(std::shared_ptr<sf::RenderWindow> iWindow) :
	_window(std::move(iWindow))
{
}

void GameMaster::Run()
{
    Init();

    while (_window->isOpen())
    {
        WindowManager::Update(_window);

        if (WindowManager::GetIsWindowClosed())
            break;

        auto totalTime = _clock.getElapsedTime();
        auto dTime = totalTime - _lastIterationTime;
        auto thisIterationGameTime = GameTime(totalTime, dTime);

        _lastIterationTime = totalTime;

        _currentScreen->Update(thisIterationGameTime);

        _window->clear();
        _window->draw(*_currentScreen);
        _window->display();
    }
}

void GameMaster::Init()
{
    _window->setFramerateLimit(60);

    _clock = sf::Clock();
    _lastIterationTime = sf::Time();

    _currentScreen = std::make_shared<MainMenuScreen>([](const GameTime& iGameTime){});
}
