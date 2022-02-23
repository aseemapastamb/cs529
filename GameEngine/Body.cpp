#include "Body.h"
#include "Transform.h"
#include "GameObject.h"
#include "FrameRateController.h"
#include "EventManager.h"
#include "GameObjectManager.h"
#include "Health.h"
#include "AI.h"

extern int width;
extern int height;
extern FrameRateController* gpFrameRateController;
extern EventManager* gpEventManager;
extern GameObjectManager* gpGameObjectManager;

Body::Body():
	Component("Body"),
	mPosX(0.0f), mPosY(0.0f),
	mAngle(0.0f), mSpeed(0.0f),
	mVelX(0.0f), mVelY(0.0f),
	mGrenadeExploding(false),
	mType2Colliding(false),
	mpPlayer(nullptr)
{
}

Body::~Body() {

}

void Body::Update() {
	Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));

	if (pTransform != nullptr) {

		mPosX = pTransform->mPositionX;
		mPosY = pTransform->mPositionY;
		mAngle = pTransform->mAngle;

		if (mpOwner->mType == "Bullet") {

			mVelX = mSpeed * cosf(mAngle * 3.14f / 180.0f);
			mVelY = mSpeed * sinf(mAngle * 3.14f / 180.0f);

			mPosX += mVelX * gpFrameRateController->getDeltaTime();
			mPosY += mVelY * gpFrameRateController->getDeltaTime();

			pTransform->mPositionX = mPosX;
			pTransform->mPositionY = mPosY;

			if (pTransform->mPositionX < 0 ||
				pTransform->mPositionX > width ||
				pTransform->mPositionY < 0 ||
				pTransform->mPositionY > height)
			{
				gpEventManager->Unsubscribe("Destroy " + mpOwner->mLabel, mpOwner);
				mpOwner->mDestroyed = true;
			}
		}

		if (mpOwner->mType == "Grenade") {

			mVelX *= 0.98f;
			mVelY *= 0.98f;

			mPosX += mVelX * gpFrameRateController->getDeltaTime();
			mPosY += mVelY * gpFrameRateController->getDeltaTime();

			pTransform->mPositionX = mPosX;
			pTransform->mPositionY = mPosY;

			if (pTransform->mPositionX < 0) {
				pTransform->mPositionX = (float)width;
			}
			if (pTransform->mPositionX > width) {
				pTransform->mPositionX = 0.0f;
			}
			if (pTransform->mPositionY < 0) {
				pTransform->mPositionY = (float)height;
			}
			if (pTransform->mPositionY > height) {
				pTransform->mPositionY = 0.0f;
			}
		}

		if (mpOwner->mType == "Type1Enemy") {

			mPosX += mVelX * gpFrameRateController->getDeltaTime();
			mPosY += mVelY * gpFrameRateController->getDeltaTime();

			pTransform->mPositionX = mPosX;
			pTransform->mPositionY = mPosY;

			if (mpPlayer == nullptr) {
				findTarget();
			}
			if (mpPlayer != nullptr) {
				Transform* pPlayerTr = (Transform*)(mpPlayer->GetComponent("Transform"));
				AI* pAI = (AI*)(mpOwner->GetComponent("AI"));

				if (pPlayerTr != nullptr && pAI != nullptr) {
					pTransform->mAngle = atan2f(pPlayerTr->mPositionY - pTransform->mPositionY, pPlayerTr->mPositionX - pTransform->mPositionX);
					pTransform->mAngle = pTransform->mAngle * 180 / 3.14f;

					float den = static_cast<float> (RAND_MAX / (5.0f - (-5.0f)));
					float randomVal = -5.0f + static_cast<float> (rand()) / den;
					pAI->mAimAngle = pTransform->mAngle + randomVal;
				}
			}

			if (pTransform->mPositionX < 0) {
				pTransform->mPositionX = (float)width;
			}
			if (pTransform->mPositionX > width) {
				pTransform->mPositionX = 0.0f;
			}
			if (pTransform->mPositionY < 0) {
				pTransform->mPositionY = (float)height;
			}
			if (pTransform->mPositionY > height) {
				pTransform->mPositionY = 0.0f;
			}

		}

		if (mpOwner->mType == "Type2Enemy") {

			if (mpPlayer == nullptr) {
				findTarget();
			}
			if (mpPlayer != nullptr) {
				Transform* pPlayerTr = (Transform*)(mpPlayer->GetComponent("Transform"));

				if (pPlayerTr != nullptr) {
					pTransform->mAngle = atan2f(pPlayerTr->mPositionY - pTransform->mPositionY, pPlayerTr->mPositionX - pTransform->mPositionX);
					pTransform->mAngle = pTransform->mAngle * 180 / 3.14f;
				}
			}

			mVelX = mSpeed * cosf(mAngle * 3.14f / 180.0f);
			mVelY = mSpeed * sinf(mAngle * 3.14f / 180.0f);

			mPosX += mVelX * gpFrameRateController->getDeltaTime();
			mPosY += mVelY * gpFrameRateController->getDeltaTime();

			pTransform->mPositionX = mPosX;
			pTransform->mPositionY = mPosY;

			if (pTransform->mPositionX < 0) {
				pTransform->mPositionX = (float)width;
			}
			if (pTransform->mPositionX > width) {
				pTransform->mPositionX = 0.0f;
			}
			if (pTransform->mPositionY < 0) {
				pTransform->mPositionY = (float)height;
			}
			if (pTransform->mPositionY > height) {
				pTransform->mPositionY = 0.0f;
			}

		}

		if (mpOwner->mType == "PickupLife" ||
			mpOwner->mType == "PickupFastShooting" ||
			mpOwner->mType == "PickupCoin" ||
			mpOwner->mType == "PickupGrenade") {

			mPosX += mVelX * gpFrameRateController->getDeltaTime();
			mPosY += mVelY * gpFrameRateController->getDeltaTime();

			pTransform->mPositionX = mPosX;
			pTransform->mPositionY = mPosY;

			if (pTransform->mPositionX < 0) {
				pTransform->mPositionX = (float)width;
			}
			if (pTransform->mPositionX > width) {
				pTransform->mPositionX = 0.0f;
			}
			if (pTransform->mPositionY < 0) {
				pTransform->mPositionY = (float)height;
			}
			if (pTransform->mPositionY > height) {
				pTransform->mPositionY = 0.0f;
			}

		}

	}
}

void Body::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {
	if (jsonObject.HasMember("speed")) {
		mSpeed = jsonObject["speed"].GetFloat();
	}
}

void Body::HandleEvent(Event* pEvent) {
	if (mpOwner->mType == "Bullet" ||
		mpOwner->mType == "Grenade" ||
		mpOwner->mType == "PickupLife" ||
		mpOwner->mType == "PickupFastShooting" ||
		mpOwner->mType == "PickupCoin" ||
		mpOwner->mType == "PickupGrenade")
	{
		if (pEvent->mEventType == "Destroy " + mpOwner->mLabel) {
			gpEventManager->Unsubscribe("Destroy " + mpOwner->mLabel, mpOwner);
			mpOwner->mDestroyed = true;
		}
		if (pEvent->mEventType == "Explode " + mpOwner->mLabel) {
			Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));
			pTransform->mScaleX *= 3.0f;
			pTransform->mScaleY *= 3.0f;
			mGrenadeExploding = true;

			gpEventManager->Unsubscribe("Explode " + mpOwner->mLabel, mpOwner);
			Event* pEvent = new Event("Destroy " + mpOwner->mLabel);
			pEvent->mTimer = 0.5f;
			gpEventManager->AddTimedEvent(pEvent);
		}
	}

	if (mpOwner->mType == "Type1Enemy") {
		if (pEvent->mEventType == "Collision: Type1Enemy, Player") {
			CollideEvent* collideEvent = (CollideEvent*)pEvent;

			if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
				Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));
				pTransform->mPositionX += 50.0f;

				Event* pEvent = new Event("Player Hit");
				gpEventManager->BroadcastToSubscribers(pEvent);
				delete pEvent;
			}
		}
		if (pEvent->mEventType == "Collision: Type1Enemy, Bullet") {
			CollideEvent* collideEvent = (CollideEvent*)pEvent;

			if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
				Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
				--pHealth->mHealth;

				Event* pEvent = new Event("Destroy " + collideEvent->pObject2->mLabel);
				gpEventManager->BroadcastToSubscribers(pEvent);
				delete pEvent;
			}
		}
		if (pEvent->mEventType == "Collision: Type1Enemy, Grenade") {
			CollideEvent* collideEvent = (CollideEvent*)pEvent;

			if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
				Body* pObjectBody = (Body*)(collideEvent->pObject2->GetComponent("Body"));

				if (pObjectBody->mGrenadeExploding) {
					Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
					pHealth->mHealth -= 2;

					pObjectBody->mGrenadeExploding = false;
				}
				else {
					pObjectBody->mVelX *= -1;
					pObjectBody->mVelY *= -1;
				}
			}
		}
	}

	if (mpOwner->mType == "Type2Enemy") {
		if (pEvent->mEventType == "Collision: Type2Enemy, Player") {
			CollideEvent* collideEvent = (CollideEvent*)pEvent;

			if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
				if (mType2Colliding == false) {
					Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));
					pTransform->mScaleX *= 3.0f;
					pTransform->mScaleY *= 3.0f;
					mType2Colliding = true;
				}

				Event* pEvent1 = new Event("Destroy " + mpOwner->mLabel);
				pEvent1->mTimer = 0.1f;
				gpEventManager->AddTimedEvent(pEvent1);

				Event* pEvent2 = new Event("Player Hit by Type2Enemy");
				gpEventManager->BroadcastToSubscribers(pEvent2);
				delete pEvent2;
			}
		}
		if (pEvent->mEventType == "Collision: Type2Enemy, Bullet") {
			CollideEvent* collideEvent = (CollideEvent*)pEvent;

			if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
				Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
				--pHealth->mHealth;

				Event* pEvent = new Event("Destroy " + collideEvent->pObject2->mLabel);
				gpEventManager->BroadcastToSubscribers(pEvent);
				delete pEvent;
			}
		}
		if (pEvent->mEventType == "Collision: Type2Enemy, Grenade") {
			CollideEvent* collideEvent = (CollideEvent*)pEvent;

			if (collideEvent->pObject1->mLabel == mpOwner->mLabel) {
				Body* pObjectBody = (Body*)(collideEvent->pObject2->GetComponent("Body"));

				if (pObjectBody->mGrenadeExploding) {
					Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
					pHealth->mHealth -= 2;

					pObjectBody->mGrenadeExploding = false;
				}
				else {
					pObjectBody->mVelX *= -1;
					pObjectBody->mVelY *= -1;
				}
			}
		}
	}
}

void Body::findTarget() {
	for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i) {
		if (gpGameObjectManager->mGameObjects[i]->mType == "Player") {
			mpPlayer = gpGameObjectManager->mGameObjects[i];
		}
	}
}