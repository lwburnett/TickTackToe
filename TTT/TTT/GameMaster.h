#pragma once
#include <SFML/Graphics.hpp>

class GameMaster
{
public:
	explicit GameMaster(std::shared_ptr<sf::RenderWindow> iWindow);
	~GameMaster() = default;

	void Run();

private:
	std::shared_ptr<sf::RenderWindow> _window;
};