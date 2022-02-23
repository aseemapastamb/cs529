#pragma once
#include <string>

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Update();
	void Initialize(std::string initialLevel);
	void ChangeLevel(std::string newLevel);
	void SetNextLevel(std::string newLevel);
	void Quit();

public:
	std::string mInitialLevel, mNextLevel, mCurrentLevel, mPreviousLevel;
};