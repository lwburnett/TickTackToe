#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "GameTime.h"

class IScreen : public sf::Drawable
{
public:
	virtual void Update(const GameTime& iGameTime) = 0;
};
