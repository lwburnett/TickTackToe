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
	// const static LevelInfo Level3;
	// const static LevelInfo Level4 = LevelInfo(
	// 	"Level 4",
	// 	{
	// 		{'_', '_', '_', '_', 't', '_', '_'},
	// 		{'_', '_', '_', '_', 't', '_', '_'},
	// 		{'_', '_', 'o', 'o', 't', 'x', '_'},
	// 		{'_', '_', 't', 't', 'o', 't', '_'},
	// 		{'_', '_', 'x', 'x', 't', '_', '_'},
	// 		{'_', '_', '_', '_', 'x', '_', '_'},
	// 		{'_', '_', '_', '_', '_', '_', '_'}
	// 	});;
	// const static LevelInfo Level5;
	// const static LevelInfo Level6;
	// const static LevelInfo Level7;
	// const static LevelInfo Level8;
	// const static LevelInfo Level9;
};