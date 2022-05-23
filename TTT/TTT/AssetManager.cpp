#include "AssetManager.h"

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include "Windows.h"

std::shared_ptr<sf::Font> AssetManager::sFont = nullptr;
std::shared_ptr<sf::Texture> AssetManager::sCross = nullptr;
std::shared_ptr<sf::Texture> AssetManager::sCircle = nullptr;
std::shared_ptr<sf::Texture> AssetManager::sTriangle = nullptr;
std::shared_ptr<sf::Texture> AssetManager::sTranslate = nullptr;
//std::shared_ptr<sf::Texture> AssetManager::sRotate = nullptr;

std::shared_ptr<sf::Font> AssetManager::LoadMainFont()
{
	if (!sFont)
	{
		const auto assetPath = GetAssetPath("TimesNewRoman.ttf");

		const auto font = std::make_shared<sf::Font>();
		if (!font->loadFromFile(assetPath))
			std::cout << "wtf" << std::endl;

		sFont = font;
	}
	
	return sFont;
}

std::shared_ptr<sf::Texture> AssetManager::LoadCrossTexture()
{
	if (!sCross)
	{
		sCross = LoadTexture("Cross.png");
	}
	return sCross;
}

std::shared_ptr<sf::Texture> AssetManager::LoadCircleTexture()
{
	if (!sCircle)
	{
		sCircle = LoadTexture("Circle.png");
	}
	return sCircle;
}

std::shared_ptr<sf::Texture> AssetManager::LoadTriangleTexture()
{
	if (!sTriangle)
	{
		sTriangle = LoadTexture("Triangle.png");
	}
	return sTriangle;
}

std::shared_ptr<sf::Texture> AssetManager::LoadTranslate()
{
	if (!sTranslate)
	{
		sTranslate = LoadTexture("Translate.png");
	}
	return sTranslate;
}

std::shared_ptr<sf::Texture> AssetManager::LoadTexture(const std::string& iFileName)
{
	const auto assetPath = GetAssetPath(iFileName);

	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile(assetPath);

	texture->setSmooth(true);

	return texture;
}

std::string AssetManager::GetAssetPath(const std::string& iAssetFileName)
{
	char exePath[_MAX_PATH];
	GetModuleFileNameA(nullptr, exePath, _MAX_PATH);

	const std::string exePathStr{ exePath };
	const auto exeParentDirectory = exePathStr.substr(0, exePathStr.find_last_of('\\'));
	auto assetPathStr = exeParentDirectory + "\\" + iAssetFileName;
	
	return assetPathStr;
}
