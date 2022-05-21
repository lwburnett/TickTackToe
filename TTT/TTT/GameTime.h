#pragma once
#include <SFML/System/Time.hpp>

class GameTime
{
public:
	GameTime(const sf::Time& iTotalElapsedTime, const sf::Time& iDeltaTime);
	GameTime(const GameTime& iRhs) = default;
	~GameTime() = default;

	sf::Time GetTotalElapsedTime() const;
	sf::Time GetDeltaTime() const;

private:
	sf::Time _totalElapsedTime;
	sf::Time _deltaTime;
};
