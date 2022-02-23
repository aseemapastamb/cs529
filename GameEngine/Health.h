#pragma once

#include "Component.h"

class Health : public Component
{
public:
	Health();
	~Health();

	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
	void HandleEvent(Event* pEvent);
public:
	int mHealthMax, mHealth;
	int mLives;
};