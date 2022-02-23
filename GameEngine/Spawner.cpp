#include "Spawner.h"

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameStateManager.h"
#include "EventManager.h"
#include "Transform.h"
#include "Body.h"
#include "Target.h"

extern GameObjectFactory* gpGameObjectFactory;
extern EventManager* gpEventManager;
extern GameStateManager* gpGameStateManager;

Spawner::Spawner():
	Component("Spawner"),
	numType1Enemies(0),
	numType2Enemies(0),
	numPickupLife(0),
	numPickupFastShooting(0),
	numPickupGrenade(0),
	numPickupCoin(0),
	level(0)
{
}

Spawner::~Spawner()
{
}

void Spawner::Update() {
	if (numType1Enemies <= 0 && numType2Enemies <= 0 && numPickupCoin <= 0) {
		if (level == 1) {
			gpGameStateManager->SetNextLevel("levelcleared.json");
		}
		if (level == 2) {
			gpGameStateManager->SetNextLevel("youwin.json");
		}
	}
}

void Spawner::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {
	if (jsonObject.HasMember("enemy type 1")) {
		numType1Enemies = jsonObject["enemy type 1"].GetInt();
	}
	if (jsonObject.HasMember("enemy type 2")) {
		numType2Enemies = jsonObject["enemy type 2"].GetInt();
	}
	if (jsonObject.HasMember("pickup life")) {
		numPickupLife = jsonObject["pickup life"].GetInt();
	}
	if (jsonObject.HasMember("pickup fastShooting")) {
		numPickupFastShooting = jsonObject["pickup fastShooting"].GetInt();
	}
	if (jsonObject.HasMember("pickup grenade")) {
		numPickupGrenade = jsonObject["pickup grenade"].GetInt();
	}
	if (jsonObject.HasMember("pickup coin")) {
		numPickupCoin = jsonObject["pickup coin"].GetInt();
	}
	if (jsonObject.HasMember("level")) {
		level = jsonObject["level"].GetInt();
	}
	Initialize();
}

void Spawner::HandleEvent(Event* pEvent) {
	if (pEvent->mEventType == "Type1Enemy Died") {
		--numType1Enemies;
	}
	if (pEvent->mEventType == "Type2Enemy Died") {
		--numType2Enemies;
	}
	if (pEvent->mEventType == "Collision: Player, PickupCoin") {
		--numPickupCoin;
	}
}

void Spawner::Initialize() {
	float den = 0.0f;
	float randomVal = 0.0f;
	for (int i = 0; i < numType1Enemies; ++i) {
		GameObject* pObject = gpGameObjectFactory->BuildGameObject("enemy1.json");
		pObject->mLabel = "Level" + std::to_string(level) + "Type1Enemy" + std::to_string(i);

		gpEventManager->Subscribe("Collision: Type1Enemy, Player", pObject);
		gpEventManager->Subscribe("Collision: Type1Enemy, Bullet", pObject);
		gpEventManager->Subscribe("Collision: Type1Enemy, Grenade", pObject);

		Transform* pObjectTr = (Transform*)pObject->GetComponent("Transform");
		den = static_cast<float> (RAND_MAX / (800.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionX = randomVal;
		den = static_cast<float> (RAND_MAX / (600.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionY = randomVal;
		den = static_cast<float> (RAND_MAX / (180.0f - (-180.0f)));
		randomVal = -180.0f + static_cast<float> (rand()) / den;
		pObjectTr->mAngle = randomVal;

		Body* pObjectBody = (Body*)pObject->GetComponent("Body");
		pObjectBody->mVelX = pObjectBody->mSpeed * cosf(pObjectTr->mAngle * 3.14f / 180.0f);
		pObjectBody->mVelY = pObjectBody->mSpeed * sinf(pObjectTr->mAngle * 3.14f / 180.0f);
	}
	for (int i = 0; i < numType2Enemies; ++i) {
		GameObject* pObject = gpGameObjectFactory->BuildGameObject("enemy2.json");
		pObject->mLabel = "Level" + std::to_string(level) + "Type2Enemy" + std::to_string(i);

		gpEventManager->Subscribe("Collision: Type2Enemy, Player", pObject);
		gpEventManager->Subscribe("Collision: Type2Enemy, Bullet", pObject);
		gpEventManager->Subscribe("Collision: Type2Enemy, Grenade", pObject);
		gpEventManager->Subscribe("Destroy " + pObject->mLabel, pObject);

		Transform* pObjectTr = (Transform*)pObject->GetComponent("Transform");
		den = static_cast<float> (RAND_MAX / (800.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionX = randomVal;
		den = static_cast<float> (RAND_MAX / (600.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionY = randomVal;
		den = static_cast<float> (RAND_MAX / (180.0f - (-180.0f)));
		randomVal = -180.0f + static_cast<float> (rand()) / den;
		pObjectTr->mAngle = randomVal;
	}
	for (int i = 0; i < numPickupLife; ++i) {
		GameObject* pObject = gpGameObjectFactory->BuildGameObject("pickuplife.json");
		pObject->mLabel = "Level" + std::to_string(level) + "PickupLife" + std::to_string(i);

		gpEventManager->Subscribe("Destroy " + pObject->mLabel, pObject);

		Transform* pObjectTr = (Transform*)pObject->GetComponent("Transform");
		den = static_cast<float> (RAND_MAX / (800.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionX = randomVal;
		den = static_cast<float> (RAND_MAX / (600.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionY = randomVal;

		Body* pObjectBody = (Body*)pObject->GetComponent("Body");
		den = static_cast<float> (RAND_MAX / (180.0f - (-180.0f)));
		randomVal = -180.0f + static_cast<float> (rand()) / den;
		pObjectBody->mAngle = randomVal;
		pObjectBody->mVelX = pObjectBody->mSpeed * cosf(pObjectBody->mAngle * 3.14f / 180.0f);
		pObjectBody->mVelY = pObjectBody->mSpeed * sinf(pObjectBody->mAngle * 3.14f / 180.0f);
	}
	for (int i = 0; i < numPickupFastShooting; ++i) {
		GameObject* pObject = gpGameObjectFactory->BuildGameObject("pickupfastshooting.json");
		pObject->mLabel = "Level" + std::to_string(level) + "PickupFastShooting" + std::to_string(i);

		gpEventManager->Subscribe("Destroy " + pObject->mLabel, pObject);

		Transform* pObjectTr = (Transform*)pObject->GetComponent("Transform");
		den = static_cast<float> (RAND_MAX / (800.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionX = randomVal;
		den = static_cast<float> (RAND_MAX / (600.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionY = randomVal;

		Body* pObjectBody = (Body*)pObject->GetComponent("Body");
		den = static_cast<float> (RAND_MAX / (180.0f - (-180.0f)));
		randomVal = -180.0f + static_cast<float> (rand()) / den;
		pObjectBody->mAngle = randomVal;
		pObjectBody->mVelX = pObjectBody->mSpeed * cosf(pObjectBody->mAngle * 3.14f / 180.0f);
		pObjectBody->mVelY = pObjectBody->mSpeed * sinf(pObjectBody->mAngle * 3.14f / 180.0f);
	}
	for (int i = 0; i < numPickupGrenade; ++i) {
		GameObject* pObject = gpGameObjectFactory->BuildGameObject("pickupgrenade.json");
		pObject->mLabel = "Level" + std::to_string(level) + "PickupGrenade" + std::to_string(i);

		gpEventManager->Subscribe("Destroy " + pObject->mLabel, pObject);

		Transform* pObjectTr = (Transform*)pObject->GetComponent("Transform");
		den = static_cast<float> (RAND_MAX / (800.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionX = randomVal;
		den = static_cast<float> (RAND_MAX / (600.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionY = randomVal;

		Body* pObjectBody = (Body*)pObject->GetComponent("Body");
		den = static_cast<float> (RAND_MAX / (180.0f - (-180.0f)));
		randomVal = -180.0f + static_cast<float> (rand()) / den;
		pObjectBody->mAngle = randomVal;
		pObjectBody->mVelX = pObjectBody->mSpeed * cosf(pObjectBody->mAngle * 3.14f / 180.0f);
		pObjectBody->mVelY = pObjectBody->mSpeed * sinf(pObjectBody->mAngle * 3.14f / 180.0f);
	}
	for (int i = 0; i < numPickupCoin; ++i) {
		GameObject* pObject = gpGameObjectFactory->BuildGameObject("pickupcoin.json");
		pObject->mLabel = "Level" + std::to_string(level) + "PickupCoin" + std::to_string(i);

		gpEventManager->Subscribe("Destroy " + pObject->mLabel, pObject);

		Transform* pObjectTr = (Transform*)pObject->GetComponent("Transform");
		den = static_cast<float> (RAND_MAX / (800.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionX = randomVal;
		den = static_cast<float> (RAND_MAX / (600.0f));
		randomVal = static_cast<float> (rand()) / den;
		pObjectTr->mPositionY = randomVal;

		Body* pObjectBody = (Body*)pObject->GetComponent("Body");
		den = static_cast<float> (RAND_MAX / (180.0f - (-180.0f)));
		randomVal = -180.0f + static_cast<float> (rand()) / den;
		pObjectBody->mAngle = randomVal;
		pObjectBody->mVelX = pObjectBody->mSpeed * cosf(pObjectBody->mAngle * 3.14f / 180.0f);
		pObjectBody->mVelY = pObjectBody->mSpeed * sinf(pObjectBody->mAngle * 3.14f / 180.0f);
	}
}
