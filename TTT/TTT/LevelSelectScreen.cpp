#include "LevelSelectScreen.h"
#include "Button.h"
#include <SFML/Graphics/Text.hpp>
#include "AssetManager.h"

LevelSelectScreen::LevelSelectScreen(
	const std::function<void(const GameTime&)>& iOnLevel1,
	const std::function<void(const GameTime&)>& iOnLevel2,
	const std::function<void(const GameTime&)>& iOnLevel3,
	const std::function<void(const GameTime&)>& iOnLevel4,
	const std::function<void(const GameTime&)>& iOnLevel5,
	const std::function<void(const GameTime&)>& iOnLevel6,
	const std::function<void(const GameTime&)>& iOnLevel7,
	const std::function<void(const GameTime&)>& iOnLevel8,
	const std::function<void(const GameTime&)>& iOnLevel9,
	const std::function<void(const GameTime&)>& iOnMainMenu)
{
	const auto font = AssetManager::LoadMainFont();

	_titleText = std::make_shared<sf::Text>();
	_titleText->setFont(*font);
	_titleText->setString("Select a level");
	_titleText->setCharacterSize(60);
	_titleText->setPosition(141, 25);

	auto level1Text = std::make_shared<sf::Text>("Level 1", *font, 30);
	_level1Button = std::make_shared<Button>(iOnLevel1, level1Text);
	_level1Button->setScale(133, 50);
	_level1Button->setPosition(50, 175);

	auto level2Text = std::make_shared<sf::Text>("Level 2", *font, 30);
	_level2Button = std::make_shared<Button>(iOnLevel2, level2Text);
	_level2Button->setScale(133, 50);
	_level2Button->setPosition(223, 175);

	auto level3Text = std::make_shared<sf::Text>("Level 3", *font, 30);
	_level3Button = std::make_shared<Button>(iOnLevel3, level3Text);
	_level3Button->setScale(133, 50);
	_level3Button->setPosition(406, 175);

	auto level4Text = std::make_shared<sf::Text>("Level 4", *font, 30);
	_level4Button = std::make_shared<Button>(iOnLevel4, level4Text);
	_level4Button->setScale(133, 50);
	_level4Button->setPosition(50, 275);

	auto level5Text = std::make_shared<sf::Text>("Level 5", *font, 30);
	_level5Button = std::make_shared<Button>(iOnLevel5, level5Text);
	_level5Button->setScale(133, 50);
	_level5Button->setPosition(223, 275);

	auto level6Text = std::make_shared<sf::Text>("Level 6", *font, 30);
	_level6Button = std::make_shared<Button>(iOnLevel6, level6Text);
	_level6Button->setScale(133, 50);
	_level6Button->setPosition(406, 275);

	auto level7Text = std::make_shared<sf::Text>("Level 7", *font, 30);
	_level7Button = std::make_shared<Button>(iOnLevel7, level7Text);
	_level7Button->setScale(133, 50);
	_level7Button->setPosition(50, 375);

	auto level8Text = std::make_shared<sf::Text>("Level 8", *font, 30);
	_level8Button = std::make_shared<Button>(iOnLevel8, level8Text);
	_level8Button->setScale(133, 50);
	_level8Button->setPosition(223, 375);

	auto level9Text = std::make_shared<sf::Text>("Level 9", *font, 30);
	_level9Button = std::make_shared<Button>(iOnLevel9, level9Text);
	_level9Button->setScale(133, 50);
	_level9Button->setPosition(406, 375);

	auto mainMenuText = std::make_shared<sf::Text>("Main Menu", *font, 30);
	_mainMenuButton = std::make_shared<Button>(iOnMainMenu, mainMenuText);
	_mainMenuButton->setScale(200, 50);
	_mainMenuButton->setPosition(200, 475);
}

void LevelSelectScreen::Update(const GameTime& iGameTime)
{
	_level1Button->Update(iGameTime);
	_level2Button->Update(iGameTime);
	_level3Button->Update(iGameTime);
	_level4Button->Update(iGameTime);
	_level5Button->Update(iGameTime);
	_level6Button->Update(iGameTime);
	_level7Button->Update(iGameTime);
	_level8Button->Update(iGameTime);
	_level9Button->Update(iGameTime);
	_mainMenuButton->Update(iGameTime);
}

void LevelSelectScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_titleText, states);
	target.draw(*_level1Button, states);
	target.draw(*_level2Button, states);
	target.draw(*_level3Button, states);
	target.draw(*_level4Button, states);
	target.draw(*_level5Button, states);
	target.draw(*_level6Button, states);
	target.draw(*_level7Button, states);
	target.draw(*_level8Button, states);
	target.draw(*_level9Button, states);
	target.draw(*_mainMenuButton, states);
}
