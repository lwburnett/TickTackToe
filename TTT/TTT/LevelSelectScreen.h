#pragma once
#include <functional>
#include <memory>
#include "IScreen.h"
#include <SFML/Graphics/RenderTarget.hpp>

class Button;

namespace sf
{
	class Text;
}

class LevelSelectScreen : public IScreen
{
public:
	LevelSelectScreen(
		const std::function<void(const GameTime&)>& iOnLevel1,
		const std::function<void(const GameTime&)>& iOnLevel2,
		const std::function<void(const GameTime&)>& iOnLevel3,
		const std::function<void(const GameTime&)>& iOnLevel4,
		const std::function<void(const GameTime&)>& iOnLevel5,
		const std::function<void(const GameTime&)>& iOnLevel6,
		const std::function<void(const GameTime&)>& iOnLevel7,
		const std::function<void(const GameTime&)>& iOnLevel8,
		const std::function<void(const GameTime&)>& iOnLevel9,
		const std::function<void(const GameTime&)>& iOnMainMenu);

	~LevelSelectScreen() override = default;

	void Update(const GameTime& iGameTime) override;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::shared_ptr<sf::Text> _titleText;
	std::shared_ptr<Button> _level1Button;
	std::shared_ptr<Button> _level2Button;
	std::shared_ptr<Button> _level3Button;
	std::shared_ptr<Button> _level4Button;
	std::shared_ptr<Button> _level5Button;
	std::shared_ptr<Button> _level6Button;
	std::shared_ptr<Button> _level7Button;
	std::shared_ptr<Button> _level8Button;
	std::shared_ptr<Button> _level9Button;
	std::shared_ptr<Button> _mainMenuButton;
};
