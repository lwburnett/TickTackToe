#pragma once
#include <functional>
#include <memory>

#include "IScreen.h"
#include "LevelManager.h"

class Button;

namespace sf
{
	class Font;
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
	enum PlayState
	{
		Play,
		Win,
		Lose
	};

	enum SymbolId
	{
		Cross,
		Circle,
		Triangle,
		Square		
	};


	class Symbol
	{
	public:
		Symbol(const SymbolId iId, std::shared_ptr<sf::Sprite> iSprite) :
			Id(iId),
			Sprite(std::move(iSprite))
		{  }
		~Symbol() = default;

		SymbolId Id;
		std::shared_ptr<sf::Sprite> Sprite;
	};

	PlayState _playState;
	LevelInfo _levelInfo;
	
	std::shared_ptr<sf::Text> _titleText;
	std::shared_ptr<Button> _backButton;
	std::shared_ptr<Button> _resetButton;

	std::shared_ptr<Button> _levelSelectButton;
	std::shared_ptr<Button> _playAgainButton;

	std::shared_ptr<sf::RectangleShape> _wall1;
	std::shared_ptr<sf::RectangleShape> _wall2;
	std::shared_ptr<sf::RectangleShape> _wall3;
	std::shared_ptr<sf::RectangleShape> _wall4;
	std::vector<std::shared_ptr<sf::RectangleShape>> _verticalSubWalls;
	std::vector<std::shared_ptr<sf::RectangleShape>> _horizontalSubWalls;
	
	std::shared_ptr<sf::RectangleShape> _resultStrike;
	
	std::vector<std::shared_ptr<Button>> _translateButtons;
	std::vector<std::vector<std::shared_ptr<Symbol>>> _symbols;

	void OnPlayAgain();
	void LoadSymbolsFromConfig();
	void CreateTranslateButtons();
	void TranslateSymbols(int iIndex, bool iIsRow, bool iForwards);
	void ValidatePlayState();
};
