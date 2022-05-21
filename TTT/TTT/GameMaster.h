#pragma once
#include <SFML/Graphics.hpp>

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

	void Init();
};
