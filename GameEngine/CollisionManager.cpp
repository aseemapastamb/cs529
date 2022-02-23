#include "CollisionManager.h"

#include "GameObjectManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"

#include <SDL.h>

extern GameObjectManager* gpGameObjectManager;
extern EventManager* gpEventManager;
extern InputManager* gpInputManager;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update() {
	for (auto pGameObject1 : gpGameObjectManager->mGameObjects) {

		Transform* pTransform1 = (Transform*)pGameObject1->GetComponent("Transform");

		float posX1 = pTransform1->mPositionX;
		float posY1 = pTransform1->mPositionY;
		float scaleX1 = pTransform1->mScaleX;
		float scaleY1 = pTransform1->mScaleY;

		if (pGameObject1->mType == "Button") {

			if (CollisionPointAABB((float)gpInputManager->mMouseX, (float)gpInputManager->mMouseY, posX1, posY1, scaleX1, scaleY1) && gpInputManager->isButtonReleased(SDL_BUTTON_LMASK)) {
				ButtonPressEvent* pEvent = new ButtonPressEvent(pGameObject1);
				gpEventManager->BroadcastToSubscribers((Event*)pEvent);
				delete pEvent;
				break;
			}

		}

		if (pGameObject1->mType == "Type1Enemy" ||
			pGameObject1->mType == "Type2Enemy") {

			for (auto pGameObject2 : gpGameObjectManager->mGameObjects) {

				if (pGameObject2->mType == "Player" ||
					pGameObject2->mType == "Bullet" ||
					pGameObject2->mType == "Grenade") {

					if (pGameObject2->mLabel.find("Enemy") == std::string::npos) {

						Transform* pTransform2 = (Transform*)pGameObject2->GetComponent("Transform");

						float posX2 = pTransform2->mPositionX;
						float posY2 = pTransform2->mPositionY;
						float scaleX2 = pTransform2->mScaleX;
						float scaleY2 = pTransform2->mScaleY;

						if (CollisionAABBAABB(posX1, posY1, scaleX1, scaleY1, posX2, posY2, scaleX2, scaleY2)) {
							CollideEvent* pEvent = new CollideEvent(pGameObject1, pGameObject2);
							gpEventManager->BroadcastToSubscribers((Event*)pEvent);
							delete pEvent;
						}
					}

				}

			}

		}

		if (pGameObject1->mType == "Player") {

			for (auto pGameObject2 : gpGameObjectManager->mGameObjects) {

				if (pGameObject2->mType == "Bullet") {

					if (pGameObject2->mLabel.find("Enemy") != std::string::npos) {

						Transform* pTransform2 = (Transform*)pGameObject2->GetComponent("Transform");

						float posX2 = pTransform2->mPositionX;
						float posY2 = pTransform2->mPositionY;
						float scaleX2 = pTransform2->mScaleX;
						float scaleY2 = pTransform2->mScaleY;

						if (CollisionAABBAABB(posX1, posY1, scaleX1, scaleY1, posX2, posY2, scaleX2, scaleY2)) {
							CollideEvent* pEvent = new CollideEvent(pGameObject1, pGameObject2);
							gpEventManager->BroadcastToSubscribers((Event*)pEvent);
							delete pEvent;
						}
					}

				}

				if (pGameObject2->mType == "PickupLife" ||
					pGameObject2->mType == "PickupFastShooting" ||
					pGameObject2->mType == "PickupCoin" ||
					pGameObject2->mType == "PickupGrenade") {

					Transform* pTransform2 = (Transform*)pGameObject2->GetComponent("Transform");

					float posX2 = pTransform2->mPositionX;
					float posY2 = pTransform2->mPositionY;
					float scaleX2 = pTransform2->mScaleX;
					float scaleY2 = pTransform2->mScaleY;

					if (CollisionAABBAABB(posX1, posY1, scaleX1, scaleY1, posX2, posY2, scaleX2, scaleY2)) {
						CollideEvent* pEvent = new CollideEvent(pGameObject1, pGameObject2);
						gpEventManager->BroadcastToSubscribers((Event*)pEvent);
						delete pEvent;
					}

				}

			}

		}

	}
}

bool CollisionManager::CollisionAABBAABB(float posX1, float posY1, float scaleX1, float scaleY1, float posX2, float posY2, float scaleX2, float scaleY2) {
	if ((posX1 - (scaleX1 / 2.0f)) > (posX2 + (scaleX2 / 2.0f))) {
		return false;
	}
	if ((posX1 + (scaleX1 / 2.0f)) < (posX2 - (scaleX2 / 2.0f))) {
		return false;
	}
	if ((posY1 - (scaleY1 / 2.0f)) > (posY2 + (scaleY2 / 2.0f))) {
		return false;
	}
	if ((posY1 + (scaleY1 / 2.0f)) < (posY2 - (scaleY2 / 2.0f))) {
		return false;
	}

	return true;
}

bool CollisionManager::CollisionPointAABB(float posX1, float posY1, float posX2, float posY2, float scaleX2, float scaleY2)
{
	if (posX1 < (posX2 - (scaleX2 / 2.0f))) {
		return false;
	}
	if (posX1 > (posX2 + (scaleX2 / 2.0f))) {
		return false;
	}
	if (posY1 < (posY2 - (scaleY2 / 2.0f))) {
		return false;
	}
	if (posY1 > (posY2 + (scaleY2 / 2.0f))) {
		return false;
	}
	return true;
}
