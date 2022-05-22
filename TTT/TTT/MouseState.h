#pragma once
#include <SFML/Window/Event.hpp>

#include "MouseState.h"

class MouseState
{
public:
	MouseState() :
		Position(sf::Event::MouseMoveEvent()),
		Pressed(false)
	{		
	}

	MouseState(const MouseState& iRhs) = default;
	~MouseState() = default;
	
	sf::Event::MouseMoveEvent Position;
	bool Pressed;
};
