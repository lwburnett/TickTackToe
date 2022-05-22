#include "WindowManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

MouseState WindowManager::sMouseState = MouseState();
bool WindowManager::sIsWindowClosed = false;
sf::Vector2u WindowManager::sWindowSize = sf::Vector2u();

void WindowManager::Update(const std::shared_ptr<sf::RenderWindow>& iWindow)
{
    sf::Event event{};
    while (iWindow->pollEvent(event))
    {
	    switch (event.type)  // NOLINT(clang-diagnostic-switch-enum)
	    {
		    case sf::Event::Closed:
			    {
				    iWindow->close();
				    sIsWindowClosed = true;
			    }
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					sMouseState.Pressed = true;
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					sMouseState.Pressed = false;
				break;
			}
		    case sf::Event::MouseMoved:
			    {
					sMouseState.Position = event.mouseMove;
					break;
			    }
		    default: break;
	    }
    }

	sWindowSize = iWindow->getSize();
}

MouseState WindowManager::GetMouseState()
{
	return sMouseState;
}

bool WindowManager::GetIsWindowClosed()
{
    return sIsWindowClosed;
}

sf::Vector2u WindowManager::GetWindowSize()
{
	return sWindowSize;
}
