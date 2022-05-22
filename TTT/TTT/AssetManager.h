#pragma once
#include <memory>
#include <string>

namespace sf
{
	class Font;
}

class AssetManager
{
public:
	static std::shared_ptr<sf::Font> LoadMainFont();

private:
	static std::string GetAssetPath(const std::string& iAssetFileName);

	static std::shared_ptr<sf::Font> sFont;
};
