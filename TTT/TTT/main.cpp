#include <memory>
#include "GameMaster.h"

int main()
{
	const auto game = std::make_shared<GameMaster>();
	game->Run();
	return 0;
}