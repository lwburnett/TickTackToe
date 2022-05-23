#pragma once
#include <memory>

#include "IScreen.h"
#include "LevelManager.h"

namespace sf
{
	class Text;
}

class LevelScreen : public IScreen
{
public:
	LevelScreen(const LevelInfo& iInfo);
	~LevelScreen() override = default;

	void Update(const GameTime& iGameTime) override;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	LevelInfo _levelInfo;
	
	std::shared_ptr<sf::Text> _titleText;
};
