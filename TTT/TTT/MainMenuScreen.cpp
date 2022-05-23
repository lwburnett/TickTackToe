#include "MainMenuScreen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.h"
#include "AssetManager.h"

MainMenuScreen::MainMenuScreen(
    const std::function<void(const GameTime&)>& iOnPlay,
    const std::function<void(const GameTime&)>& iOnInstructions,
    const std::function<void(const GameTime&)>& iOnQuit)
{
	const auto font = AssetManager::LoadMainFont();

    _titleText = std::make_shared<sf::Text>();
    _titleText->setFont(*font);
    _titleText->setString("Tick Tack Toe Puzzle");
    _titleText->setCharacterSize(60);
    _titleText->setPosition(23.5, 25);

    auto playText = std::make_shared<sf::Text>("Play", *font, 40);
    _playButton = std::make_shared<Button>(iOnPlay, playText);
    _playButton->setScale(250, 75);
    _playButton->setPosition(175, 200);

    auto instructionsText = std::make_shared<sf::Text>("Instructions", *font, 40);
    _instructionsButton = std::make_shared<Button>(iOnInstructions, instructionsText);
    _instructionsButton->setScale(250, 75);
    _instructionsButton->setPosition(175, 300);

    auto quitText = std::make_shared<sf::Text>("Quit", *font, 40);
    _quitButton = std::make_shared<Button>(iOnQuit, quitText);
    _quitButton->setScale(250, 75);
    _quitButton->setPosition(175, 400);
}

void MainMenuScreen::Update(const GameTime& iGameTime)
{
    _playButton->Update(iGameTime);
    _instructionsButton->Update(iGameTime);
    _quitButton->Update(iGameTime);
}

void MainMenuScreen::draw(sf::RenderTarget& iTarget, sf::RenderStates iStates) const
{
    iTarget.draw(*_titleText, iStates);
    iTarget.draw(*_playButton, iStates);
    iTarget.draw(*_instructionsButton, iStates);
    iTarget.draw(*_quitButton, iStates);
}