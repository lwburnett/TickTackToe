#include "GameTime.h"

GameTime::GameTime(const sf::Time& iTotalElapsedTime, const sf::Time& iDeltaTime) :
	_totalElapsedTime(iTotalElapsedTime),
	_deltaTime(iDeltaTime)
{
}

sf::Time GameTime::GetTotalElapsedTime() const
{
	return _totalElapsedTime;
}

sf::Time GameTime::GetDeltaTime() const
{
	return _deltaTime;
}
