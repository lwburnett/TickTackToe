#pragma once
#include <functional>
#include <memory>

#include "IScreen.h"
#include "LevelManager.h"

class Button;

namespace sf
{
	class Sprite;
	class RectangleShape;
	class Text;
}

class LevelScreen : public IScreen
{
public:
	LevelScreen(const LevelInfo& iInfo, const std::function<void(const GameTime&)>& iOnBack);
	~LevelScreen() override = default;

	void Update(const GameTime& iGameTime) override;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	LevelInfo _levelInfo;
	
	std::shared_ptr<sf::Text> _titleText;
	std::shared_ptr<Button> _backButton;

	std::shared_ptr<sf::RectangleShape> _wall1;
	std::shared_ptr<sf::RectangleShape> _wall2;
	std::shared_ptr<sf::RectangleShape> _wall3;
	std::shared_ptr<sf::RectangleShape> _wall4;
	std::vector<std::shared_ptr<sf::RectangleShape>> _verticalSubWalls;
	std::vector<std::shared_ptr<sf::RectangleShape>> _horizontalSubWalls;
	
	std::vector<std::shared_ptr<sf::RectangleShape>> _verticalButtons;
	std::vector<std::shared_ptr<sf::RectangleShape>> _horizontalButtons;

	std::vector<std::vector<std::shared_ptr<sf::Sprite>>> _symbols;
};
