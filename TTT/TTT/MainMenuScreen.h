#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "IScreen.h"

class MainMenuScreen : public IScreen
{
public:
	MainMenuScreen();
	void Update(const GameTime& iGameTime) override;

protected:
	void draw(sf::RenderTarget& iTarget, sf::RenderStates iStates) const override;

private:
	sf::CircleShape _circle;
};
