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

	auto backText = std::make_shared<sf::Text>("Back", *font, 20);
	_backButton = std::make_shared<Button>(iOnBack, backText);
	_backButton->setScale(80, 30);
	_backButton->setPosition(40, 50);

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
}
