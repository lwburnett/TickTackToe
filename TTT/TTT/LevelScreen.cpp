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
	_titleText->setCharacterSize(60);
	const auto xPos = (WindowManager::GetWindowSize().x - _titleText->getLocalBounds().width) / 2;
	_titleText->setPosition(xPos, 25);

	auto backText = std::make_shared<sf::Text>("< Back", *font, 25);
	_backButton = std::make_shared<Button>(iOnBack, backText);
	_backButton->setScale(90, 40);
	_backButton->setPosition(40, 33);
}

void LevelScreen::Update(const GameTime& iGameTime)
{
	_backButton->Update(iGameTime);
}

void LevelScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_titleText, states);
	target.draw(*_backButton, states);
}
