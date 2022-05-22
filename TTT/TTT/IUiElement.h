#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "IUpdateable.h"

class IUiElement : public IUpdateable, public sf::Drawable, public sf::Transformable
{
public:
	~IUiElement() override = default;
};
