#include "GameObjectManager.h"
#include "GameObject.h"
#include "EventManager.h"

extern EventManager* gpEventManager;

#include <cassert>

GameObjectManager::GameObjectManager() {

}

GameObjectManager::~GameObjectManager() {
	for (auto pGameObject : mGameObjects) {
		RemoveObject(pGameObject);
	}
	mGameObjects.clear();
}

void GameObjectManager::AddObject(GameObject* pNewGameObject) {
	mGameObjects.push_back(pNewGameObject);
}

void GameObjectManager::RemoveObject(GameObject* pNewGameObject) {
	for (unsigned int i = 0; i < mGameObjects.size(); ++i) {
		if (mGameObjects[i] == pNewGameObject) {
			GameObject* temp = mGameObjects[i];
			mGameObjects.erase(std::find(mGameObjects.begin(), mGameObjects.end(), mGameObjects[i]));
			delete temp;
			break;
		}
	}
}

void GameObjectManager::RemoveDestroyed() {
	for (unsigned int i = 0; i < mGameObjects.size(); ++i) {
		if (mGameObjects[i]->mDestroyed) {
			if (mGameObjects[i]->mType == "Button") {
				gpEventManager->Unsubscribe("Button Pressed", mGameObjects[i]);
			}
			if (mGameObjects[i]->mType == "Player") {
				gpEventManager->Unsubscribe("Player Hit", mGameObjects[i]);
				gpEventManager->Unsubscribe("Player Hit by Type2Enemy", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Player, Bullet", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Player, PickupLife", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Player, PickupFastShooting", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Player, PickupCoin", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Player, PickupGrenade", mGameObjects[i]);
			}
			if (mGameObjects[i]->mType == "Bullet" ||
				mGameObjects[i]->mType == "Grenade" ||
				mGameObjects[i]->mType == "PickupLife" ||
				mGameObjects[i]->mType == "PickupFastShooting" ||
				mGameObjects[i]->mType == "PickupCoin" ||
				mGameObjects[i]->mType == "PickupGrenade") {
				gpEventManager->Unsubscribe("Destroy " + mGameObjects[i]->mLabel, mGameObjects[i]);
				gpEventManager->Unsubscribe("Explode " + mGameObjects[i]->mLabel, mGameObjects[i]);
			}
			if (mGameObjects[i]->mType == "Type1Enemy") {
				gpEventManager->Unsubscribe("Collision: Type1Enemy, Player", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Type1Enemy, Bullet", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Type1Enemy, Grenade", mGameObjects[i]);
			}
			if (mGameObjects[i]->mType == "Type2Enemy") {
				gpEventManager->Unsubscribe("Collision: Type2Enemy, Player", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Type2Enemy, Bullet", mGameObjects[i]);
				gpEventManager->Unsubscribe("Collision: Type2Enemy, Grenade", mGameObjects[i]);
				gpEventManager->Unsubscribe("Destroy " + mGameObjects[i]->mLabel, mGameObjects[i]);
			}
			if (mGameObjects[i]->mType == "Spawner") {
				gpEventManager->Unsubscribe("Collision: Player, PickupCoin", mGameObjects[i]);
				gpEventManager->Unsubscribe("Type1Enemy Died", mGameObjects[i]);
				gpEventManager->Unsubscribe("Type2Enemy Died", mGameObjects[i]);
			}
			RemoveObject(mGameObjects[i--]);
		}
	}
}

void GameObjectManager::Update() {
	for (unsigned int i = 0; i < mGameObjects.size(); ++i) {
		assert(mGameObjects[i]);
		mGameObjects[i]->Update();
	}
}