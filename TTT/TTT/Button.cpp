#include "Button.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "WindowManager.h"

Button::Button(std::function<void(const GameTime&)> iOnClickCallback, std::shared_ptr<sf::Text> iContent /*= nullptr*/) :
	_onClickCallback(std::move(iOnClickCallback)),
	_contentText(std::move(iContent)),
	_contentSprite(nullptr),
	_lastIterationPressedState(false),
	_isOverlapped(false),
	_isPressed(false)
{
}

Button::Button(std::function<void(const GameTime&)> iOnClickCallback, std::shared_ptr<sf::Sprite> iContent) :
	_onClickCallback(std::move(iOnClickCallback)),
	_contentText(nullptr),
	_contentSprite(std::move(iContent)),
	_lastIterationPressedState(false),
	_isOverlapped(false),
	_isPressed(false)
{
}

void Button::Update(const GameTime& iGameTime)
{
	const auto mouseState = WindowManager::GetMouseState();

	if (IsOverlappingWithMouse(mouseState.Position))
	{
		OnOverlap();

		if (mouseState.Pressed)
		{
			if (!_lastIterationPressedState)
				OnPressed();
		}
		else
			OnReleased(iGameTime);
	}
	else
	{
		if (mouseState.Pressed)
			OnNotOverlap();
		else
			Reset();
	}

	_lastIterationPressedState = mouseState.Pressed;

	_backgroundRect.setPosition(getPosition());
	_backgroundRect.setSize(getScale());

	if (!_isOverlapped && !_isPressed)
	{
		_backgroundRect.setFillColor(sf::Color(200, 200, 200));
	}
	else if (_isOverlapped && !_isPressed)
	{
		_backgroundRect.setFillColor(sf::Color(169, 169, 169));
	}
	else
	{
		_backgroundRect.setFillColor(sf::Color(128, 128, 128));
	}

	if (_contentText)
	{
		const auto contentBounds = _contentText->getLocalBounds();
		const auto posX = getPosition().x + (getScale().x - contentBounds.width) / 2;
		const auto posY = (getPosition().y + (getScale().y - contentBounds.height) / 2) - (10 * Lerp(0, 60, getScale().y));

		const auto origin = _contentText->getOrigin();
		_contentText->setPosition(posX + origin.x, posY + origin.y);
	}

	if (_contentSprite)
	{
		const auto contentBounds = _contentSprite->getLocalBounds();
		const auto posX = getPosition().x + (getScale().x - contentBounds.width) / 2;
		const auto posY = (getPosition().y + (getScale().y - contentBounds.height) / 2);

		const auto origin = _contentSprite->getOrigin();
		_contentSprite->setPosition(posX + origin.x, posY + origin.y);
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_backgroundRect, states);

	if(_contentText)
		target.draw(*_contentText, states);

	if (_contentSprite)
		target.draw(*_contentSprite, states);
}

bool Button::IsOverlappingWithMouse(const sf::Event::MouseMoveEvent& iMouseMove) const
{
	const auto thisPosition = getPosition();
	const auto thisDimensions = getScale();

	return iMouseMove.x > thisPosition.x &&
		iMouseMove.x < thisPosition.x + thisDimensions.x &&
		iMouseMove.y > thisPosition.y &&
		iMouseMove.y < thisPosition.y + thisDimensions.y;
}

void Button::OnOverlap()
{
	_isOverlapped = true;
}

void Button::OnNotOverlap()
{
	_isOverlapped = false;
}

void Button::OnPressed()
{
	_isPressed = true;
}

void Button::OnReleased(const GameTime& iGameTime)
{
	if (_isPressed && _isOverlapped)
	{
		_onClickCallback(iGameTime);
	}

	_isPressed = false;
}

void Button::Reset()
{
	_isPressed = false;
	_isOverlapped = false;
}

float Button::Lerp(const float iLowerBound, const float iUpperBound, const float iNum)
{
	if (iNum <= iLowerBound)
		return 0.0f;
	if (iNum >= iUpperBound)
		return 1.0f;

	return (iNum - iLowerBound) / (iUpperBound - iLowerBound);
}
