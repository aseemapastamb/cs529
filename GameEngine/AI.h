#pragma once

#include "Component.h"

class GameObject;

class AI : public Component
{
public:
	AI();
	~AI();

	void Update();
	//void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
	//void HandleEvent(Event* pEvent);
public:
	float mAimAngle;
	float mBulletSpawnTimer;
	int mBulletID;
};