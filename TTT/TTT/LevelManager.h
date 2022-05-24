#pragma once
#include <string>
#include <vector>

class LevelInfo
{
public:
	LevelInfo(std::string iName, std::vector<std::vector<char>> iConfig) :
		Name(std::move(iName)),
		Config(std::move(iConfig))
	{		
	}
	LevelInfo(const LevelInfo& iRhs) = default;
	~LevelInfo() = default;

	std::string Name;
	std::vector<std::vector<char>> Config;
};

class LevelManager
{
public:
	static LevelInfo Level1;
	static LevelInfo Level2;
	static LevelInfo Level3;
	static LevelInfo Level4;
	static LevelInfo Level5;
	static LevelInfo Level6;
	static LevelInfo Level7;
	static LevelInfo Level8;
	// const static LevelInfo Level9;
};