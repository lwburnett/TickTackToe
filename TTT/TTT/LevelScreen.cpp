#include "LevelScreen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "AssetManager.h"
#include "Button.h"
#include "WindowManager.h"

LevelScreen::LevelScreen(const LevelInfo& iInfo, const std::function<void(const GameTime&)>& iOnBack) :
	_playState(PlayState::Play),
	_levelInfo(iInfo),
	_resultStrike(nullptr)
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

	auto resetText = std::make_shared<sf::Text>("Reset", *font, 20);
	_resetButton = std::make_shared<Button>([this](const GameTime& iGameTime) { LoadSymbolsFromConfig(); }, resetText);
	_resetButton->setScale(80, 30);
	_resetButton->setPosition(260, 550);

	auto selectLevelText = std::make_shared<sf::Text>("Select Level", *font, 20);
	_levelSelectButton = std::make_shared<Button>(iOnBack, selectLevelText);
	_levelSelectButton->setScale(120, 30);
	_levelSelectButton->setPosition(150, 550);

	auto playAgainText = std::make_shared<sf::Text>("Play Again", *font, 20);
	_playAgainButton = std::make_shared<Button>([this](const GameTime iGameTime) { OnPlayAgain(); }, playAgainText);
	_playAgainButton->setScale(120, 30);
	_playAgainButton->setPosition(330, 550);

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
		thisWall->setFillColor(sf::Color(128, 128, 128));
		thisWall->setPosition(238 + (40 * jj), 127 + (41 * ii));
		_verticalSubWalls.push_back(thisWall);
	}

	_horizontalSubWalls = std::vector<std::shared_ptr<sf::RectangleShape>>();
	for (int ii = 0; ii < 4; ii++)
	for (int jj = 0; jj < 9; jj++)
	{
		const auto thisWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(19, 1));
		thisWall->setFillColor(sf::Color(128, 128, 128));
		thisWall->setPosition(129 + (40 * jj), 237 + (41 * ii));
		_horizontalSubWalls.push_back(thisWall);
	}

	_symbols = std::vector<std::vector<std::shared_ptr<Symbol>>>();
	LoadSymbolsFromConfig();

	_translateButtons = std::vector<std::shared_ptr<Button>>();
	CreateTranslateButtons();
}

void LevelScreen::Update(const GameTime& iGameTime)
{
	if (_playState == PlayState::Play)
	{
		_backButton->Update(iGameTime);
		_resetButton->Update(iGameTime);
		for (const auto& transformButton : _translateButtons)
		{
			transformButton->Update(iGameTime);
		}
	}
	else
	{
		_backButton->Update(iGameTime);
		_levelSelectButton->Update(iGameTime);
		_playAgainButton->Update(iGameTime);
	}
}

void LevelScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_titleText, states);
	target.draw(*_backButton, states);

	if (_playState == PlayState::Play)
	{
		target.draw(*_resetButton, states);
	}
	else
	{
		target.draw(*_levelSelectButton, states);
		target.draw(*_playAgainButton, states);
	}

	for (const auto& verticalSubWall : _verticalSubWalls)
	{
		target.draw(*verticalSubWall, states);
	}

	for (const auto& horizontalSubWall : _horizontalSubWalls)
	{
		target.draw(*horizontalSubWall, states);
	}

	target.draw(*_wall1, states);
	target.draw(*_wall2, states);
	target.draw(*_wall3, states);
	target.draw(*_wall4, states);

	for (const auto& symbolRow : _symbols)
		for (const auto& symbol : symbolRow)
		{
			if (symbol)
				target.draw(*(symbol->Sprite), states);
		}

	for (const auto& transformButton : _translateButtons)
	{
		target.draw(*transformButton, states);
	}

	if (_resultStrike)
		target.draw(*_resultStrike, states);
}

void LevelScreen::OnPlayAgain()
{
	_playState = PlayState::Play;
	LoadSymbolsFromConfig();
	_resultStrike.reset();
}

void LevelScreen::LoadSymbolsFromConfig()
{
	_symbols.clear();

	for (int ii = 0; ii < 9; ii++)
	for (int jj = 0; jj < 9; jj++)
	{
		if (jj == 0)
			_symbols.emplace_back();

		const auto thisSymbolChar = _levelInfo.Config[ii][jj];

		std::shared_ptr<sf::Sprite> thisSymbolPtr = nullptr;
		SymbolId thisSymbolId = SymbolId::Cross;
		switch (thisSymbolChar)
		{
		case 'x':
			thisSymbolPtr = std::make_shared<sf::Sprite>(*AssetManager::LoadCrossTexture());
			thisSymbolPtr->setColor(sf::Color::Green);
			thisSymbolId = SymbolId::Cross;
			break;
		case 'o':
			thisSymbolPtr = std::make_shared<sf::Sprite>(*AssetManager::LoadCircleTexture());
			thisSymbolPtr->setColor(sf::Color::Cyan);
			thisSymbolId = SymbolId::Circle;
			break;
		case 't':
			thisSymbolPtr = std::make_shared<sf::Sprite>(*AssetManager::LoadTriangleTexture());
			thisSymbolPtr->setColor(sf::Color::Red);
			thisSymbolId = SymbolId::Triangle;
			break;
		case '_':
		default:
			break;
		}

		if (thisSymbolPtr)
		{
			thisSymbolPtr->setPosition(122 + (jj * 41), 121 + (ii * 41));
		}

		const auto thisSymbol = thisSymbolPtr ? 
			std::make_shared<Symbol>(thisSymbolId, thisSymbolPtr) :
			nullptr;

		_symbols[ii].push_back(thisSymbol);
	}
}

void LevelScreen::CreateTranslateButtons()
{
	const auto arrowTexture = AssetManager::LoadTranslate();

	for (int ii = 3; ii < 6; ii++)
	{
		auto numSymbolsInRow = 0;
		auto numSymbolsInCol = 0;

		for (int jj = 0; jj < 9; jj++)
		{
			if (_symbols[ii][jj])
				numSymbolsInRow++;
			if (_symbols[jj][ii])
				numSymbolsInCol++;
		}

		if (numSymbolsInRow > 3)
		{
			const auto arrowLeft = std::make_shared<sf::Sprite>(*arrowTexture);
			arrowLeft->setOrigin(12.5, 12.5);
			arrowLeft->setRotation(270);
			const auto leftButton = std::make_shared<Button>(
				[=](const GameTime& iGameTime) { TranslateSymbols(ii, true, false); },
				arrowLeft);
			leftButton->setPosition(75, 75 + (41 * (ii + 1)));
			leftButton->setScale(38, 38);
			_translateButtons.push_back(leftButton);
			
			const auto arrowRight = std::make_shared<sf::Sprite>(*arrowTexture);
			arrowRight->setOrigin(12.5, 12.5);
			arrowRight->setRotation(90);
			const auto rightButton = std::make_shared<Button>(
				[=](const GameTime& iGameTime) { TranslateSymbols(ii, true, true); },
				arrowRight);
			rightButton->setPosition(487, 75 + (41 * (ii + 1)));
			rightButton->setScale(38, 38);
			_translateButtons.push_back(rightButton);
		}

		if (numSymbolsInCol > 3)
		{
			const auto arrowUp = std::make_shared<sf::Sprite>(*arrowTexture);
			const auto upButton = std::make_shared<Button>(
				[=](const GameTime& iGameTime) { TranslateSymbols(ii, false, false); },
				arrowUp);
			upButton->setPosition(75 + (41 * (ii + 1)), 75);
			upButton->setScale(38, 38);
			_translateButtons.push_back(upButton);
			
			const auto arrowDown = std::make_shared<sf::Sprite>(*arrowTexture);
			arrowDown->setOrigin(12.5, 12.5);
			arrowDown->setRotation(180);
			const auto downButton = std::make_shared<Button>(
				[=](const GameTime& iGameTime) { TranslateSymbols(ii, false, true); },
				arrowDown);
			downButton->setPosition(75 + (41 * (ii + 1)), 487);
			downButton->setScale(38, 38);
			_translateButtons.push_back(downButton);
		}
	}
}

void LevelScreen::TranslateSymbols(const int iIndex, const bool iIsRow, const bool iForwards)
{
	if (iIsRow)
	{
		if (iForwards)
		{
			if (_symbols[iIndex][8] || !_symbols[iIndex][2])
				return;

			for (int ii = 8; ii > 0; ii--)
			{
				_symbols[iIndex][ii] = _symbols[iIndex][ii - 1];
				if (_symbols[iIndex][ii])
				{
					const auto currentPos = _symbols[iIndex][ii]->Sprite->getPosition();
					_symbols[iIndex][ii]->Sprite->setPosition(currentPos.x + 41, currentPos.y);
				}
			}

			_symbols[iIndex][0] = nullptr;
		}
		if (!iForwards)
		{
			if (_symbols[iIndex][0] || !_symbols[iIndex][6])
				return;

			for (int ii = 0; ii < 8; ii++)
			{
				_symbols[iIndex][ii] = _symbols[iIndex][ii + 1];
				if (_symbols[iIndex][ii])
				{
					const auto currentPos = _symbols[iIndex][ii]->Sprite->getPosition();
					_symbols[iIndex][ii]->Sprite->setPosition(currentPos.x - 41, currentPos.y);
				}
			}

			_symbols[iIndex][8] = nullptr;
		}
	}
	else
	{
		if (iForwards)
		{
			if (_symbols[8][iIndex] || !_symbols[2][iIndex])
				return;

			for (int ii = 8; ii > 0; ii--)
			{
				_symbols[ii][iIndex] = _symbols[ii - 1][iIndex];
				if (_symbols[ii][iIndex])
				{
					const auto currentPos = _symbols[ii][iIndex]->Sprite->getPosition();
					_symbols[ii][iIndex]->Sprite->setPosition(currentPos.x, currentPos.y + 41);
				}
			}

			_symbols[0][iIndex] = nullptr;
		}
		if (!iForwards)
		{
			if (_symbols[0][iIndex] || !_symbols[6][iIndex])
				return;

			for (int ii = 0; ii < 8; ii++)
			{
				_symbols[ii][iIndex] = _symbols[ii + 1][iIndex];
				if (_symbols[ii][iIndex])
				{
					const auto currentPos = _symbols[ii][iIndex]->Sprite->getPosition();
					_symbols[ii][iIndex]->Sprite->setPosition(currentPos.x, currentPos.y - 41);
				}
			}

			_symbols[8][iIndex] = nullptr;
		}
	}

	ValidatePlayState();
}

void LevelScreen::ValidatePlayState()
{
	bool inWinningState = false;
	bool inLosingState = false;

	for (int ii = 3; ii < 6; ii++)
	{
		if (_symbols[ii][3]->Id == _symbols[ii][4]->Id && _symbols[ii][3]->Id == _symbols[ii][5]->Id)
		{
			if (_symbols[ii][3]->Id == SymbolId::Cross)
			{
				inWinningState = true;
				if (!inLosingState)
				{
					_resultStrike = std::make_shared<sf::RectangleShape>(sf::Vector2f(120, 1));
					_resultStrike->setPosition(239, 135 + (ii * 41));
					_resultStrike->setFillColor(sf::Color::Yellow);
				}
			}
			else
			{
				inLosingState = true;
				_resultStrike = std::make_shared<sf::RectangleShape>(sf::Vector2f(120, 1));
				_resultStrike->setPosition(239, 135 + (ii * 41));
				_resultStrike->setFillColor(sf::Color::Yellow);
			}
		}

		if (_symbols[3][ii]->Id == _symbols[4][ii]->Id && _symbols[3][ii]->Id == _symbols[5][ii]->Id)
		{
			if (_symbols[3][ii]->Id == SymbolId::Cross)
			{
				inWinningState = true;
				if (!inLosingState)
				{
					_resultStrike = std::make_shared<sf::RectangleShape>(sf::Vector2f(1, 120));
					_resultStrike->setPosition(135 + (ii * 41), 239);
					_resultStrike->setFillColor(sf::Color::Yellow);
				}
			}
			else
			{
				inLosingState = true;
				_resultStrike = std::make_shared<sf::RectangleShape>(sf::Vector2f(1, 120));
				_resultStrike->setPosition(135 + (ii * 41), 239);
				_resultStrike->setFillColor(sf::Color::Yellow);
			}
		}
	}

	if (inLosingState)
	{
		_playState = PlayState::Lose;

		_titleText->setString("Failure!");
		const auto xPos = (WindowManager::GetWindowSize().x - _titleText->getLocalBounds().width) / 2;
		_titleText->setPosition(xPos, 20);
	}
	else if (inWinningState)
	{
		_playState = PlayState::Win;
		_titleText->setString("Success!");
		const auto xPos = (WindowManager::GetWindowSize().x - _titleText->getLocalBounds().width) / 2;
		_titleText->setPosition(xPos, 20);
	}
}
