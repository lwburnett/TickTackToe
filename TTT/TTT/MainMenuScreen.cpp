#include "MainMenuScreen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.h"
#include "AssetManager.h"

MainMenuScreen::MainMenuScreen(const std::function<void(const GameTime&)>& iOnPlay)
{
	const auto font = AssetManager::LoadMainFont();

    _titleText = std::make_shared<sf::Text>();
    _titleText->setFont(*font);
    _titleText->setString("Tick Tack Toe Puzzle");
    _titleText->setCharacterSize(60);
    _titleText->setPosition(23.5, 100);

    auto playText = std::make_shared<sf::Text>("Play", *font, 40);
    _playButton = std::make_shared<Button>(iOnPlay, playText);
    _playButton->setScale(200, 75);
    _playButton->setPosition(200, 300);
}

void MainMenuScreen::Update(const GameTime& iGameTime)
{
    _playButton->Update(iGameTime);
}

void MainMenuScreen::draw(sf::RenderTarget& iTarget, sf::RenderStates iStates) const
{
    iTarget.draw(*_titleText, iStates);
    iTarget.draw(*_playButton, iStates);
}