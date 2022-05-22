#pragma once
#include <SFML/Graphics.hpp>
#include "GameTime.h"

class IScreen;

class GameMaster
{
public:
	explicit GameMaster(std::shared_ptr<sf::RenderWindow> iWindow);
	~GameMaster() = default;

	void Run();

private:
	std::shared_ptr<sf::RenderWindow> _window;

	sf::Clock _clock;
	sf::Time _lastIterationTime;

	std::shared_ptr<IScreen> _currentScreen;
	std::shared_ptr<IScreen> _previousScreen;

	bool _isQuitPressed;

	void Init();
	void OnMainMenu(const GameTime& iGameTime);
	void OnPlayGame(const GameTime& iGameTime);
	void OnInstructions(const GameTime& iGameTime);
	void OnQuit(const GameTime& iGameTime);
};
