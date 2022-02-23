#include "GameStateManager.h"

#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "GameObject.h"

extern GameObjectFactory* gpGameObjectFactory;
extern GameObjectManager* gpGameObjectManager;
extern bool appIsRunning;

GameStateManager::GameStateManager():
	mInitialLevel(""),
	mNextLevel(""),
	mCurrentLevel(""),
	mPreviousLevel("")
{
}

GameStateManager::~GameStateManager() {

}

void GameStateManager::Update() {
	if (mInitialLevel != "") {
		mPreviousLevel = mInitialLevel;
		mCurrentLevel = mInitialLevel;
		mNextLevel = mInitialLevel;
		ChangeLevel(mCurrentLevel);
		mInitialLevel = "";
	}
	if (mCurrentLevel != mNextLevel) {
		mPreviousLevel = mCurrentLevel;
		mCurrentLevel = mNextLevel;
		ChangeLevel(mCurrentLevel);
	}
}

void GameStateManager::Initialize(std::string initialLevel) {
	mInitialLevel = initialLevel;
}

void GameStateManager::ChangeLevel(std::string newLevel) {
	for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i) {
		gpGameObjectManager->mGameObjects[i]->mDestroyed = true;
	}
	gpGameObjectFactory->BuildLevel(newLevel.c_str());
}

void GameStateManager::SetNextLevel(std::string newLevel) {
	mNextLevel = newLevel;
}

void GameStateManager::Quit() {
	for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i) {
		gpGameObjectManager->mGameObjects[i]->mDestroyed = true;
	}
	appIsRunning = false;
}