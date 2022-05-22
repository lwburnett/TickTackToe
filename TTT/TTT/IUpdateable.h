#pragma once
#include <SFML/Window/Event.hpp>
#include "GameTime.h"


class IUpdateable
{
public:
	virtual ~IUpdateable() = default;
	virtual void Update(const GameTime& iGameTime, const sf::Event& iEvent) = 0;
};
