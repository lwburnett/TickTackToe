#pragma once
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include "IScreen.h"

namespace sf
{
	class Text;
}

class MainMenuScreen : public IScreen
{
public:
	MainMenuScreen();
	void Update(const GameTime& iGameTime) override;

protected:
	void draw(sf::RenderTarget& iTarget, sf::RenderStates iStates) const override;

private:
	std::shared_ptr<sf::Text> _titleText;
};
