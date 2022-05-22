#include "MainMenuScreen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "AssetManager.h"

MainMenuScreen::MainMenuScreen()
{
    _titleText = std::make_shared<sf::Text>();
    _titleText->setFont(*AssetManager::LoadMainFont());
    _titleText->setString("Tick Tack Toe Puzzle");
    _titleText->setCharacterSize(60);
    _titleText->setPosition(23.5, 100);
}

void MainMenuScreen::Update(const GameTime& iGameTime, const sf::Event& iEvent)
{
}

void MainMenuScreen::draw(sf::RenderTarget& iTarget, sf::RenderStates iStates) const
{
    iTarget.draw(*_titleText, iStates);
}