#pragma once
#include <memory>
#include "MouseState.h"

namespace sf
{
	class RenderWindow;
}

class WindowManager
{
public:
	static void Update(const std::shared_ptr<sf::RenderWindow>& iWindow);

	static MouseState GetMouseState();
	static bool GetIsWindowClosed();
	static sf::Vector2u GetWindowSize();

private:
	static MouseState sMouseState;
	static bool sIsWindowClosed;
	static sf::Vector2u sWindowSize;
};
