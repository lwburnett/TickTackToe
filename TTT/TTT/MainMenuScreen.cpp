#include "MainMenuScreen.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


MainMenuScreen::MainMenuScreen()
{
    _circle = sf::CircleShape(100.f);
    _circle.setFillColor(sf::Color::Green);
}

void MainMenuScreen::Update(const GameTime& iGameTime)
{
}

void MainMenuScreen::draw(sf::RenderTarget& iTarget, sf::RenderStates iStates) const
{
    iTarget.draw(_circle);
}