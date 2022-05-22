#pragma once
#include <functional>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include "IScreen.h"

class Button;

namespace sf
{
	class Text;
}

class MainMenuScreen : public IScreen
{
public:
	MainMenuScreen(const std::function<void(const GameTime&)>& iOnPlay);
	~MainMenuScreen() override = default;
	void Update(const GameTime& iGameTime) override;

protected:
	void draw(sf::RenderTarget& iTarget, sf::RenderStates iStates) const override;

private:
	std::shared_ptr<sf::Text> _titleText;
	std::shared_ptr<Button> _playButton;
};
