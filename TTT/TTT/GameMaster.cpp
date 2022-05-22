#include "GameMaster.h"
#include "IScreen.h"
#include "LevelSelectScreen.h"
#include "MainMenuScreen.h"
#include "WindowManager.h"

GameMaster::GameMaster(std::shared_ptr<sf::RenderWindow> iWindow) :
	_window(std::move(iWindow)),
	_isQuitPressed(false)
{
}

void GameMaster::Run()
{
    Init();

    while (_window->isOpen())
    {
        WindowManager::Update(_window);

        if (WindowManager::GetIsWindowClosed() || _isQuitPressed)
            break;

        auto totalTime = _clock.getElapsedTime();
        auto dTime = totalTime - _lastIterationTime;
        auto thisIterationGameTime = GameTime(totalTime, dTime);

        _lastIterationTime = totalTime;

        _currentScreen->Update(thisIterationGameTime);

        if (_previousScreen)
        {
            _currentScreen->Update(thisIterationGameTime);
            _previousScreen.reset();
        }

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

    _currentScreen = std::make_shared<MainMenuScreen>(
        [this](const GameTime& iGameTime) { OnPlayGame(iGameTime); },
        [this](const GameTime& iGameTime) { OnInstructions(iGameTime); },
        [this](const GameTime& iGameTime) { OnQuit(iGameTime); });
}

void GameMaster::OnMainMenu(const GameTime& iGameTime)
{
    _previousScreen = _currentScreen;
    _currentScreen = std::make_shared<MainMenuScreen>(
        [this](const GameTime& iGameTime) { OnPlayGame(iGameTime); },
        [this](const GameTime& iGameTime) { OnInstructions(iGameTime); },
        [this](const GameTime& iGameTime) { OnQuit(iGameTime); });
}

void GameMaster::OnPlayGame(const GameTime& iGameTime)
{
    _previousScreen = _currentScreen;
    _currentScreen = std::make_shared<LevelSelectScreen>(
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {},
        [this](const GameTime& iGameTime) {OnMainMenu(iGameTime); });
}

void GameMaster::OnInstructions(const GameTime& iGameTime)
{
    //_currentScreen = std::make_shared<InstructionsScreen>();
}

void GameMaster::OnQuit(const GameTime& iGameTime)
{
    _isQuitPressed = true;
}
