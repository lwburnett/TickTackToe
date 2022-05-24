#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "IScreen.h"

namespace sf
{
	class Text;
}

class Button;

class InstructionsScreen : public IScreen
{
public:
	InstructionsScreen(const std::function<void(const GameTime&)>& iOnBack);
	~InstructionsScreen() override = default;

	void Update(const GameTime& iGameTime) override;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::shared_ptr<sf::Text> _titleText;
	std::vector<std::shared_ptr<sf::Text>> _instructionTextLines;
	std::shared_ptr<Button> _backButton;
};
