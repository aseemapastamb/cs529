#include "Health.h"

#include "GameObject.h"
#include "EventManager.h"
#include "GameStateManager.h"
#include <iostream>

extern EventManager* gpEventManager;
extern GameStateManager* gpGameStateManager;

Health::Health():
	Component("Health"),
	mHealthMax(0),
	mHealth(mHealthMax),
	mLives(0)
{
}

Health::~Health() {

}

void Health::Update() {
	if (mHealth <= 0) {
		--mLives;
		mHealth = mHealthMax;
	}
	if (mLives == 0) {
		if (mpOwner->mType == "Player") {
			std::cout << "Player Died" << std::endl;
			gpGameStateManager->SetNextLevel("gameover.json");
			return;
		}
		if (mpOwner->mType == "Type1Enemy") {
			Event* pEvent = new Event("Type1Enemy Died");
			gpEventManager->BroadcastToSubscribers(pEvent);
			delete pEvent;
			mpOwner->mDestroyed = true;
		}
		if (mpOwner->mType == "Type2Enemy") {
			Event* pEvent = new Event("Type2Enemy Died");
			gpEventManager->BroadcastToSubscribers(pEvent);
			delete pEvent;
			mpOwner->mDestroyed = true;
		}
	}
}

void Health::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {
	if (jsonObject.HasMember("health")) {
		mHealthMax = jsonObject["health"].GetInt();
		mHealth = mHealthMax;
	}
	if (jsonObject.HasMember("lives")) {
		mLives = jsonObject["lives"].GetInt();
	}
}

void Health::HandleEvent(Event* pEvent) {
	if (pEvent->mEventType == "Destroy " + mpOwner->mLabel) {
		Event* pEvent = new Event("Type2Enemy Died");
		gpEventManager->BroadcastToSubscribers(pEvent);
		delete pEvent;
		mpOwner->mDestroyed = true;
	}
}
