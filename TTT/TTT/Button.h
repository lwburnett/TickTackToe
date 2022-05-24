#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <functional>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include "GameTime.h"
#include "IUiElement.h"

namespace sf
{
	class Text;
	class Sprite;
}

class Button : public IUiElement
{
public:
	Button(std::function<void(const GameTime&)> iOnClickCallback, std::shared_ptr<sf::Text> iContent = nullptr);
	Button(std::function<void(const GameTime&)> iOnClickCallback, std::shared_ptr<sf::Sprite> iContent = nullptr);
	~Button() override = default;

	void Update(const GameTime& iGameTime) override;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	enum PressState
	{
		Default,
		Hover,
		Pressed
	};

	std::function<void(const GameTime&)> _onClickCallback;
	std::shared_ptr<sf::Text> _contentText;
	std::shared_ptr<sf::Sprite> _contentSprite;
	bool _lastIterationPressedState;

	bool _isOverlapped;
	bool _isPressed;

	sf::RectangleShape _backgroundRect;
	sf::Time _lastPressTime;

	bool IsOverlappingWithMouse(const sf::Event::MouseMoveEvent& iMouseMove) const;
	void OnOverlap();
	void OnNotOverlap();
	void OnPressed();
	void OnReleased(const GameTime& iGameTime);
	void Reset();

	static float Lerp(float iLowerBound, float iUpperBound, float iNum);
};
