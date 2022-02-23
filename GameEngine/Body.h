#pragma once

#include "Component.h"

class Body : public Component
{
public:
	Body();
	~Body();

	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
	void HandleEvent(Event* pEvent);
	void findTarget();
public:
	float mPosX, mPosY;
	float mAngle, mSpeed;
	float mVelX, mVelY;
	bool mGrenadeExploding;
	bool mType2Colliding;
	GameObject* mpPlayer;
};