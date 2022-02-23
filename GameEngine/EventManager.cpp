#include "EventManager.h"

#include "GameObjectManager.h"
#include "GameObject.h"

extern GameObjectManager* gpGameObjectManager;

Event::Event(std::string eventType):
	mEventType(eventType),
	mTimer(0.0f)
{
}

Event::~Event()
{
}

CollideEvent::CollideEvent(GameObject* _pObject1, GameObject* _pObject2):
	Event("Collision: " + _pObject1->mType + ", " + _pObject2->mType),
	pObject1(_pObject1),
	pObject2(_pObject2)
{

}

CollideEvent::~CollideEvent() {

}

ButtonPressEvent::ButtonPressEvent(GameObject* _pObject1):
	Event("Button Pressed"),
	pObject1(_pObject1)
{

}

ButtonPressEvent::~ButtonPressEvent() {

}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::Subscribe(std::string eventType, GameObject* pGameObject) {
	for (auto pGameObjectInList : mSubscriptions[eventType]) {
		if (pGameObjectInList == pGameObject) {
			return;
		}
	}
	mSubscriptions[eventType].push_back(pGameObject);
}

void EventManager::Unsubscribe(std::string eventType, GameObject* pGameObject) {
	auto i = std::find(mSubscriptions[eventType].begin(), mSubscriptions[eventType].end(), pGameObject);
	if (i == mSubscriptions[eventType].end()) {
		return;
	}
	mSubscriptions[eventType].erase(i);
}

void EventManager::Initialize() {
	for (auto i : gpGameObjectManager->mGameObjects) {
		if (i->mType == "Button") {
			Subscribe("Button Pressed", i);
		}
		if (i->mType == "Player") {
			Subscribe("Player Hit", i);
			Subscribe("Player Hit by Type2Enemy", i);
			Subscribe("Collision: Player, Bullet", i);
			Subscribe("Collision: Player, PickupLife", i);
			Subscribe("Collision: Player, PickupFastShooting", i);
			Subscribe("Collision: Player, PickupCoin", i);
			Subscribe("Collision: Player, PickupGrenade", i);
		}
		if (i->mType == "Spawner") {
			Subscribe("Collision: Player, PickupCoin", i);
			Subscribe("Type1Enemy Died", i);
			Subscribe("Type2Enemy Died", i);
		}
	}
}

void EventManager::BroadcastToAll(Event* pEvent) {
	for (auto pGameObject : gpGameObjectManager->mGameObjects) {
		pGameObject->HandleEvent(pEvent);
	}
}

void EventManager::BroadcastToSubscribers(Event* pEvent) {
	for (auto pGameObjectInList : mSubscriptions[pEvent->mEventType]) {
		pGameObjectInList->HandleEvent(pEvent);
	}
}

void EventManager::AddTimedEvent(Event* pEvent) {
	mTimedEvents.push_back(pEvent);
}

void EventManager::Update(float frameTime) {
	unsigned int i = 0;
	while (i < mTimedEvents.size()) {
		Event* pEvent = mTimedEvents[i];
		pEvent->mTimer -= frameTime;
		if (pEvent->mTimer <= 0.0f) {
			BroadcastToSubscribers(pEvent);
			delete pEvent;
			mTimedEvents.erase(std::find(mTimedEvents.begin(), mTimedEvents.end(), mTimedEvents[i]));
		}
		else {
			++i;
		}
	}
}