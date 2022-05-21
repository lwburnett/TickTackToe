#include <memory>
#include "GameMaster.h"

int main()
{
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(600, 600), "Tick Tack Toe");

	const auto game = std::make_shared<GameMaster>(window);
	game->Run();
	return 0;
}