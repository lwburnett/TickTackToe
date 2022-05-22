#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "IUpdateable.h"

class IScreen : public sf::Drawable, public IUpdateable
{
public:
	~IScreen() override = default;
};
