#include "Controller.h"

#include "Transform.h"
#include "Body.h"
#include "Ammo.h"
#include "Health.h"
#include "GameObject.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "EventManager.h"
#include "GameObjectFactory.h"
#include <SDL.h>
#include <iostream>

extern InputManager* gpInputManager;
extern FrameRateController* gpFrameRateController;
extern EventManager* gpEventManager;
extern GameObjectFactory* gpGameObjectFactory;
extern int width;
extern int height;

Controller::Controller() :
	Component("Controller"),
	mVelH(0.0f),
	mVelV(0.0f),
	mFast(0),
	mSpeed(100.0f),
	mMouseX(0),
	mMouseY(0),
	mBulletSpawnTimer(0.5f),
	mFastFire(false)
{

}

Controller::~Controller() {

}

void Controller::Update() {
	Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));

	mFast = 0;
	if (gpInputManager->isKeyPressed(SDL_SCANCODE_LSHIFT)) {
		mFast = 1;
	}

	if (gpInputManager->isKeyPressed(SDL_SCANCODE_UP) || gpInputManager->isKeyPressed(SDL_SCANCODE_W)) {
		pTransform->mPositionY -= (mSpeed + mSpeed * mFast) * gpFrameRateController->getDeltaTime();
	}
	if (gpInputManager->isKeyPressed(SDL_SCANCODE_DOWN) || gpInputManager->isKeyPressed(SDL_SCANCODE_S)) {
		pTransform->mPositionY += (mSpeed + mSpeed * mFast) * gpFrameRateController->getDeltaTime();
	}
	if (gpInputManager->isKeyPressed(SDL_SCANCODE_LEFT) || gpInputManager->isKeyPressed(SDL_SCANCODE_A)) {
		pTransform->mPositionX -= (mSpeed + mSpeed * mFast) * gpFrameRateController->getDeltaTime();
	}
	if (gpInputManager->isKeyPressed(SDL_SCANCODE_RIGHT) || gpInputManager->isKeyPressed(SDL_SCANCODE_D)) {
		pTransform->mPositionX += (mSpeed + mSpeed * mFast) * gpFrameRateController->getDeltaTime();
	}

	SDL_PumpEvents();
	SDL_GetMouseState(&mMouseX, &mMouseY);

	pTransform->mAngle = atan2f(mMouseY - pTransform->mPositionY, mMouseX - pTransform->mPositionX);
	pTransform->mAngle = pTransform->mAngle * 180 / 3.14f;

	mBulletSpawnTimer -= gpFrameRateController->getDeltaTime();
	if (gpInputManager->isKeyPressed(SDL_SCANCODE_SPACE)) {

		if (mBulletSpawnTimer <= 0.0f) {

			Ammo* pAmmo = (Ammo*)(mpOwner->GetComponent("Ammo"));
			if (pAmmo->mBullets > 0) {

				Transform* pPlayerTr = (Transform*)(mpOwner->GetComponent("Transform"));

				GameObject* pBullet = gpGameObjectFactory->BuildGameObject("bullet.json");
				pBullet->mLabel += std::to_string(pAmmo->mBullets);
				gpEventManager->Subscribe("Destroy " + pBullet->mLabel, pBullet);

				Transform* pBulletTr = (Transform*)(pBullet->GetComponent("Transform"));

				pBulletTr->mPositionX = pPlayerTr->mPositionX;
				pBulletTr->mPositionY = pPlayerTr->mPositionY;
				pBulletTr->mAngle = pPlayerTr->mAngle;

				--pAmmo->mBullets;

				if (mFastFire) {
					mBulletSpawnTimer = 0.25f;
				}
				else {
					mBulletSpawnTimer = 0.5f;
				}
			}
		}

	}

	if (gpInputManager->isKeyTriggered(SDL_SCANCODE_G)) {

		Ammo* pAmmo = (Ammo*)(mpOwner->GetComponent("Ammo"));
		if (pAmmo->mGrenades > 0) {

			Transform* pPlayerTr = (Transform*)(mpOwner->GetComponent("Transform"));

			GameObject* pGrenade = gpGameObjectFactory->BuildGameObject("grenade.json");
			pGrenade->mLabel += std::to_string(pAmmo->mGrenades);
			gpEventManager->Subscribe("Explode " + pGrenade->mLabel, pGrenade);
			gpEventManager->Subscribe("Destroy " + pGrenade->mLabel, pGrenade);

			Transform* pGrenadeTr = (Transform*)(pGrenade->GetComponent("Transform"));
			Body* pBody = (Body*)(pGrenade->GetComponent("Body"));

			pGrenadeTr->mPositionX = pPlayerTr->mPositionX;
			pGrenadeTr->mPositionY = pPlayerTr->mPositionY;
			pGrenadeTr->mAngle = pPlayerTr->mAngle;

			pBody->mVelX = 500.0f * cosf(pGrenadeTr->mAngle * 3.14f / 180.0f);
			pBody->mVelY = 500.0f * sinf(pGrenadeTr->mAngle * 3.14f / 180.0f);

			Event* pEvent = new Event("Explode " + pGrenade->mLabel);
			pEvent->mTimer = 2.0f;
			gpEventManager->AddTimedEvent(pEvent);

			--pAmmo->mGrenades;
		}

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
}

void Controller::HandleEvent(Event* pEvent) {
	if (pEvent->mEventType == "Player Hit") {
		Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
		--pHealth->mHealth;

		std::cout << "Player Hit. Health: " << pHealth->mHealth << "Lives: " << pHealth->mLives << std::endl;

		if (pHealth->mHealth <= 0) {
			Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));
			pTransform->mPositionX = width / 2.0f;
			pTransform->mPositionY = height / 2.0f;
		}
	}
	if (pEvent->mEventType == "Player Hit by Type2Enemy") {
		Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
		pHealth->mHealth -= 4;

		std::cout << "Player Hit. Health: " << pHealth->mHealth << "Lives: " << pHealth->mLives << std::endl;

		if (pHealth->mHealth <= 0) {
			Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));
			pTransform->mPositionX = 0.0f;
			pTransform->mPositionY = 0.0f;
		}
	}
	if (pEvent->mEventType == "Collision: Player, Bullet") {
		Event* pHitEvent = new Event("Player Hit");
		gpEventManager->BroadcastToSubscribers(pHitEvent);
		delete pHitEvent;

		CollideEvent* event = (CollideEvent*)pEvent;

		Event* pDestroyEvent = new Event("Destroy " + event->pObject2->mLabel);
		gpEventManager->BroadcastToSubscribers(pDestroyEvent);
		delete pDestroyEvent;
	}
	if (pEvent->mEventType == "Collision: Player, PickupLife") {
		Health* pHealth = (Health*)(mpOwner->GetComponent("Health"));
		pHealth->mHealth = pHealth->mHealthMax;
		++pHealth->mLives;

		std::cout << "PickupLife. Health: " << pHealth->mHealth << "Lives: " << pHealth->mLives << std::endl;

		CollideEvent* event = (CollideEvent*)pEvent;

		Event* pDestroyEvent = new Event("Destroy " + event->pObject2->mLabel);
		gpEventManager->BroadcastToSubscribers(pDestroyEvent);
		delete pDestroyEvent;
	}
	if (pEvent->mEventType == "Collision: Player, PickupFastShooting") {
		mFastFire = true;

		std::cout << "PickupFastShooting" << std::endl;

		Event* pTimedEvent = new Event("Fast Shooting Over");
		pTimedEvent->mTimer = 5.0f;
		gpEventManager->AddTimedEvent(pTimedEvent);

		CollideEvent* event = (CollideEvent*)pEvent;

		Event* pDestroyEvent = new Event("Destroy " + event->pObject2->mLabel);
		gpEventManager->BroadcastToSubscribers(pDestroyEvent);
		delete pDestroyEvent;
	}
	if (pEvent->mEventType == "Collision: Player, PickupCoin") {
		Ammo* pAmmo = (Ammo*)(mpOwner->GetComponent("Ammo"));
		++pAmmo->mCoins;

		std::cout << "PickupCoin. Coins: " << pAmmo->mCoins << std::endl;

		CollideEvent* event = (CollideEvent*)pEvent;

		Event* pDestroyEvent = new Event("Destroy " + event->pObject2->mLabel);
		gpEventManager->BroadcastToSubscribers(pDestroyEvent);
		delete pDestroyEvent;
	}
	if (pEvent->mEventType == "Collision: Player, PickupGrenade") {
		Ammo* pAmmo = (Ammo*)(mpOwner->GetComponent("Ammo"));
		pAmmo->mGrenades = 3;

		std::cout << "PickupGrenade. Grenades: " << pAmmo->mGrenades << std::endl;

		CollideEvent* event = (CollideEvent*)pEvent;

		Event* pDestroyEvent = new Event("Destroy " + event->pObject2->mLabel);
		gpEventManager->BroadcastToSubscribers(pDestroyEvent);
		delete pDestroyEvent;
	}
	if (pEvent->mEventType == "Fast Shooting Over") {
		mFastFire = false;

		std::cout << "Fast Shooting Over" << std::endl;
	}
}
