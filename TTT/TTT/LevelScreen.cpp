#include "LevelScreen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include "AssetManager.h"
#include "Button.h"
#include "WindowManager.h"

LevelScreen::LevelScreen(const LevelInfo& iInfo, const std::function<void(const GameTime&)>& iOnBack) :
	_levelInfo(iInfo)
{
	const auto font = AssetManager::LoadMainFont();

	_titleText = std::make_shared<sf::Text>();
	_titleText->setFont(*font);
	_titleText->setString(_levelInfo.Name);
	_titleText->setCharacterSize(50);
	const auto xPos = (WindowManager::GetWindowSize().x - _titleText->getLocalBounds().width) / 2;
	_titleText->setPosition(xPos, 20);

	auto backText = std::make_shared<sf::Text>("Back", *font, 20);
	_backButton = std::make_shared<Button>(iOnBack, backText);
	_backButton->setScale(80, 30);
	_backButton->setPosition(40, 40);

	_wall1 = std::make_shared<sf::RectangleShape>(sf::Vector2f(3, 120));
	_wall1->setPosition(277, 239);
	_wall1->setFillColor(sf::Color::White);

	_wall2 = std::make_shared<sf::RectangleShape>(sf::Vector2f(3, 120));
	_wall2->setPosition(318, 239);
	_wall2->setFillColor(sf::Color::White);

	_wall3 = std::make_shared<sf::RectangleShape>(sf::Vector2f(120, 3));
	_wall3->setPosition(239, 277);
	_wall3->setFillColor(sf::Color::White);

	_wall4 = std::make_shared<sf::RectangleShape>(sf::Vector2f(120, 3));
	_wall4->setPosition(239, 318);
	_wall4->setFillColor(sf::Color::White);
	
	_verticalSubWalls = std::vector<std::shared_ptr<sf::RectangleShape>>();
	for (int ii = 0; ii < 9; ii++)
	for (int jj = 0; jj < 4; jj++)
	{
		const auto thisWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(1, 19));
		thisWall->setFillColor(sf::Color::White);
		thisWall->setPosition(238 + (40 * jj), 127 + (41 * ii));
		_verticalSubWalls.push_back(thisWall);
	}

	_horizontalSubWalls = std::vector<std::shared_ptr<sf::RectangleShape>>();
	for (int ii = 0; ii < 4; ii++)
	for (int jj = 0; jj < 9; jj++)
	{
		const auto thisWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(19, 1));
		thisWall->setFillColor(sf::Color::White);
		thisWall->setPosition(129 + (40 * jj), 237 + (41 * ii));
		_horizontalSubWalls.push_back(thisWall);
	}

	_symbols = std::vector<std::vector<std::shared_ptr<sf::Text>>>();

	for (int ii = 0; ii < 9; ii++)
	for (int jj = 0; jj < 9; jj++)
	{
		if (jj == 0)
			_symbols.emplace_back();

		const auto thisSymbolChar = _levelInfo.Config[ii][jj];

		std::shared_ptr<sf::Text> thisSymbolPtr = nullptr;
		switch (thisSymbolChar)
		{
		case 'x':
			thisSymbolPtr = std::make_shared<sf::Text>("x", *font, 25);
			break;
		case 'o':
			thisSymbolPtr = std::make_shared<sf::Text>("o", *font, 25);
			break;
		case 't':
			thisSymbolPtr = std::make_shared<sf::Text>("t", *font, 25);
			break;
		case '_':
		default:
			break;
		}

		if (thisSymbolPtr)
			thisSymbolPtr->setPosition(127 + (jj * 41), 118 + (ii * 41));

		_symbols[ii].push_back(thisSymbolPtr);
	}
}

void LevelScreen::Update(const GameTime& iGameTime)
{
	_backButton->Update(iGameTime);
}

void LevelScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_titleText, states);
	target.draw(*_backButton, states);
	target.draw(*_wall1, states);
	target.draw(*_wall2, states);
	target.draw(*_wall3, states);
	target.draw(*_wall4, states);

	for (const auto& verticalSubWall : _verticalSubWalls)
	{
		target.draw(*verticalSubWall, states);
	}

	for (const auto& horizontalSubWall : _horizontalSubWalls)
	{
		target.draw(*horizontalSubWall, states);
	}

	for (const auto& symbolRow : _symbols)
	for (const auto& symbol : symbolRow)
	{
		if (symbol)
			target.draw(*symbol, states);
	}
}
