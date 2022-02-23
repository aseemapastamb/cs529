#include "AI.h"

#include "GameObject.h"
#include "Transform.h"
#include "Body.h"
#include "FrameRateController.h"
#include "GameObjectFactory.h"
#include "EventManager.h"

extern FrameRateController* gpFrameRateController;
extern GameObjectFactory* gpGameObjectFactory;
extern EventManager* gpEventManager;

AI::AI():
	Component("AI"),
	mAimAngle(0.0f),
	mBulletSpawnTimer(2.0f),
	mBulletID(0)
{
}

AI::~AI() {

}

void AI::Update() {
	mBulletSpawnTimer -= gpFrameRateController->getDeltaTime();
	if (mBulletSpawnTimer <= 0.0f) {
		Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));

		GameObject* pBullet = gpGameObjectFactory->BuildGameObject("bullet.json");
		pBullet->mLabel = mpOwner->mLabel + pBullet->mLabel + std::to_string(++mBulletID);
		gpEventManager->Subscribe("Destroy " + pBullet->mLabel, pBullet);

		Transform* pBulletTr = (Transform*)(pBullet->GetComponent("Transform"));

		pBulletTr->mPositionX = pTransform->mPositionX;
		pBulletTr->mPositionY = pTransform->mPositionY;
		pBulletTr->mAngle = mAimAngle;

		Body* pBulletBody = (Body*)(pBullet->GetComponent("Body"));
		pBulletBody->mSpeed /= 4.0f;

		mBulletSpawnTimer = 2.0f + static_cast<float> (rand()) / RAND_MAX;
	}
}

//void AI::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {
//
//}
