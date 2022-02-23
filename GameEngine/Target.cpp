#include "Target.h"

#include "FrameRateController.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Body.h"

extern GameObjectManager* gpGameObjectManager;
extern FrameRateController* gpFrameRateController;
extern int height, width;

Target::Target():
	Component("Target"),
	pos(0.0f, 0.0f),
	vel(0.0f, 0.0f),
	dir(0.0f, 0.0f),
	velInv(0.0f, 0.0f),
	posPlayerWRTEnemy(0.0f, 0.0f),
	radAng(0.0f),
	mpPlayer(nullptr)
{
}

Target::~Target()
{
}

void Target::Update() {
	if (mpPlayer == nullptr) {
		Initialize();
	}
	else {
		Transform* pTransform = (Transform*)mpOwner->GetComponent("Transform");
		pos.x = pTransform->mPositionX;
		pos.y = pTransform->mPositionY;
		radAng = glm::radians(pTransform->mAngle);

		Transform* pPlayerTr = (Transform*)mpPlayer->GetComponent("Transform");

		glm::vec2 points[5];
		points[0].x = pPlayerTr->mPositionX;
		points[0].y = pPlayerTr->mPositionY;
		points[1].x = points[0].x - width;
		points[1].y = points[0].y;
		points[2].x = points[0].x;
		points[2].y = points[0].y - height;
		points[3].x = points[0].x + width;
		points[3].y = points[0].y;
		points[4].x = points[0].x;
		points[4].y = points[0].y + height;

		float distSq[5];
		for (int i = 0; i < 5; ++i) {
			distSq[i] = ( (pos.x - points[i].x) * (pos.x - points[i].x) ) + ( (pos.y - points[i].y) * (pos.y - points[i].y) );
		}

		float minD = FLT_MAX;
		int min = 0;
		for (int i = 0; i < 5; ++i) {
			if (distSq[i] < minD) {
				minD = distSq[i];
				min = i;
			}
		}

		velInv.x = -vel.y;
		velInv.y = vel.x;

		posPlayerWRTEnemy = points[min] - pos;

		Body* pBody = (Body*)mpOwner->GetComponent("Body");
		if (pBody) {

			if (glm::dot(velInv, posPlayerWRTEnemy) > 0) {
				radAng += 3.14f / 2.0f * gpFrameRateController->getDeltaTime();
			}
			else {
				radAng -= 3.14f / 2.0f * gpFrameRateController->getDeltaTime();
			}
			radAng = glm::clamp(radAng, -3.14f, 3.14f);
			pBody->mAngle = radAng;
			pTransform->mAngle = glm::degrees(radAng);

			dir.x = cosf(radAng);
			dir.y = sinf(radAng);

			vel = dir * pBody->mSpeed;

			pBody->mVelX = vel.x;
			pBody->mVelY = vel.y;
		}
	}
}

void Target::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {

}

void Target::HandleEvent(Event* pEvent) {

}

void Target::Initialize() {
	for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i) {
		if (gpGameObjectManager->mGameObjects[i]->mType == "Player") {
			mpPlayer = gpGameObjectManager->mGameObjects[i];
		}
	}
	Transform* pTransform = (Transform*)mpOwner->GetComponent("Transform");
	if (pTransform) {
		pos.x = pTransform->mPositionX;
		pos.y = pTransform->mPositionY;
		radAng = glm::radians(pTransform->mAngle);
		dir.x = cosf(radAng);
		dir.y = sinf(radAng);
	}
	Body* pBody = (Body*)mpOwner->GetComponent("Body");
	if (pBody) {
		vel = dir * pBody->mSpeed;
		//vel.x = pBody->mSpeed * dir.x;
		//vel.y = pBody->mSpeed * dir.y;
	}
}