#include "AssetManager.h"

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include "Windows.h"

std::shared_ptr<sf::Font> AssetManager::sFont = nullptr;

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

std::string AssetManager::GetAssetPath(const std::string& iAssetFileName)
{
	char exePath[_MAX_PATH];
	GetModuleFileNameA(nullptr, exePath, _MAX_PATH);

	const std::string exePathStr{ exePath };
	const auto exeParentDirectory = exePathStr.substr(0, exePathStr.find_last_of('\\'));
	auto assetPathStr = exeParentDirectory + "\\" + iAssetFileName;
	
	return assetPathStr;
}
