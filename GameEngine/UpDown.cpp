#include "UpDown.h"

#include "Transform.h"
#include "Health.h"
#include "Body.h"
#include "AI.h"
#include "GameObject.h"
#include "FrameRateController.h"
#include "EventManager.h"
#include "GameObjectManager.h"

extern FrameRateController* gpFrameRateController;
extern EventManager* gpEventManager;
extern GameObjectManager* gpGameObjectManager;
extern int width;
extern int height;

UpDown::UpDown():
	Component("UpDown"),
	mGoingUp(false),
	mTimerLimit(1000),
	pPlayer(nullptr)
{
	mTimer = mTimerLimit;
}

UpDown::~UpDown() {

}

void UpDown::Update() {
	mTimer -= gpFrameRateController->getFrameTime();

	if (mTimer <= 0) {
		mGoingUp = !mGoingUp;
		mTimer = mTimerLimit;
	}

	Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));

	if (pTransform != nullptr) {
		if (mGoingUp) {
			pTransform->mPositionY -= 100.0f * gpFrameRateController->getDeltaTime();
		}
		else {
			pTransform->mPositionY += 100.0f * gpFrameRateController->getDeltaTime();
		}

		if (pTransform->mPositionX < 0) {
			pTransform->mPositionX = 0.0f;
		}
		if (pTransform->mPositionX > width) {
			pTransform->mPositionX = (float)width;
		}
		if (pTransform->mPositionY < 0) {
			pTransform->mPositionY = 0.0f;
		}
		if (pTransform->mPositionY > height) {
			pTransform->mPositionY = (float)height;
		}

		if (pPlayer == nullptr) {
			findTarget();
		}
		if (pPlayer != nullptr) {
			Transform* pPlayerTr = (Transform*)(pPlayer->GetComponent("Transform"));
			AI* pAI = (AI*)(mpOwner->GetComponent("AI"));

			if (pPlayerTr != nullptr) {
				pTransform->mAngle = atan2f(pPlayerTr->mPositionY - pTransform->mPositionY, pPlayerTr->mPositionX - pTransform->mPositionX);
				pTransform->mAngle = pTransform->mAngle * 180 / 3.14f;

				float den = static_cast<float> (RAND_MAX / (5.0f - (-5.0f)));
				float randomVal = -5.0f + static_cast<float> (rand()) / den;
				pAI->mAimAngle = pTransform->mAngle + randomVal;
			}
		}

	}
}

void UpDown::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {
	if (jsonObject.HasMember("goingUp")) {
		mGoingUp = jsonObject["goingUp"].GetBool();
	}
	if (jsonObject.HasMember("timerLimit")) {
		mTimerLimit = jsonObject["timerLimit"].GetInt();
	}
	findTarget();
}

void UpDown::HandleEvent(Event* pEvent) {
	if (pEvent->mEventType == "Collision: Enemy, Player") {
		CollideEvent* collideEvent = (CollideEvent*)pEvent;

		if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
			Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));
			pTransform->mPositionX += 50.0f;

			Event* pEvent = new Event("Player Hit");
			gpEventManager->BroadcastToSubscribers(pEvent);
			delete pEvent;
		}
	}
	if (pEvent->mEventType == "Collision: Enemy, Bullet") {
		CollideEvent* collideEvent = (CollideEvent*)pEvent;

		if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
			Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
			--pHealth->mHealth;

			Event* pEvent = new Event("Destroy " + collideEvent->pObject2->mLabel);
			gpEventManager->BroadcastToSubscribers(pEvent);
			delete pEvent;
		}
	}
	if (pEvent->mEventType == "Collision: Enemy, Grenade") {
		CollideEvent* collideEvent = (CollideEvent*)pEvent;

		if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
			Body* pBody = (Body*)(collideEvent->pObject2->GetComponent("Body"));

			if (pBody->mGrenadeExploding) {
				Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
				pHealth->mHealth -= 2;

				pBody->mGrenadeExploding = false;
			}
			else {
				pBody->mVelX *= -1;
				pBody->mVelY *= -1;
			}
		}
	}
}

void UpDown::findTarget() {
	for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i) {
		if (gpGameObjectManager->mGameObjects[i]->mType == "Player") {
			pPlayer = gpGameObjectManager->mGameObjects[i];
		}
	}
}