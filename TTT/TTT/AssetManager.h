#pragma once
#include <memory>
#include <string>

namespace sf
{
	class Texture;
	class Font;
}

class AssetManager
{
public:
	static std::shared_ptr<sf::Font> LoadMainFont();
	static std::shared_ptr<sf::Texture> LoadCrossTexture();
	static std::shared_ptr<sf::Texture> LoadCircleTexture();
	static std::shared_ptr<sf::Texture> LoadTriangleTexture();
	static std::shared_ptr<sf::Texture> LoadTranslate();

private:
	static std::shared_ptr<sf::Texture> LoadTexture(const std::string& iFileName);
	static std::string GetAssetPath(const std::string& iAssetFileName);

	static std::shared_ptr<sf::Font> sFont;
	static std::shared_ptr<sf::Texture> sCross;
	static std::shared_ptr<sf::Texture> sCircle;
	static std::shared_ptr<sf::Texture> sTriangle;
	static std::shared_ptr<sf::Texture> sTranslate;
};