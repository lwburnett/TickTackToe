#include "InstructionsScreen.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include "AssetManager.h"
#include "Button.h"
#include "WindowManager.h"

InstructionsScreen::InstructionsScreen(const std::function<void(const GameTime&)>& iOnBack)
{
    const auto font = AssetManager::LoadMainFont();

	_titleText = std::make_shared<sf::Text>();
	_titleText->setFont(*font);
	_titleText->setString("How To Play");
	_titleText->setCharacterSize(50);
	const auto xPos = (WindowManager::GetWindowSize().x - _titleText->getLocalBounds().width) / 2;
	_titleText->setPosition(xPos, 10);

	_instructionTextLines = std::vector<std::shared_ptr<sf::Text>>
	{
		std::make_shared<sf::Text>("Score a tic tac toe against your own brain", *font, 20),
		std::make_shared<sf::Text>("in this unique puzzle game. Instead of", *font, 20),
		std::make_shared<sf::Text>("placing the symbols yourself, shuffle the", *font, 20),
		std::make_shared<sf::Text>("existing symbols around using the arrow buttons.", *font, 20),
		std::make_shared<sf::Text>("Avoid scoring a tic tac toe for the other", *font, 20),
		std::make_shared<sf::Text>("symbols while you try to score one for the Crosses.", *font, 20),
	};

    for (int ii = 0; ii < _instructionTextLines.size(); ii++)
    {
		const auto thisLine = _instructionTextLines[ii];
		thisLine->setPosition(40, 100 + ii * 30);
    }

	auto backText = std::make_shared<sf::Text>("Back", *font, 20);
	_backButton = std::make_shared<Button>(iOnBack, backText);
	_backButton->setScale(80, 30);
	_backButton->setPosition(40, 560);
}

void InstructionsScreen::Update(const GameTime& iGameTime)
{
	_backButton->Update(iGameTime);
}

void InstructionsScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_titleText, states);
	target.draw(*_backButton, states);

	for (const auto& line : _instructionTextLines)
	{
		target.draw(*line, states);		
	}
}
