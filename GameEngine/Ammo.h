#pragma once

#include "Component.h"

class Ammo : public Component
{
public:
	Ammo();
	~Ammo();

	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
	//void HandleEvent(Event* pEvent);
public:
	int mBullets;
	int mGrenades;
	int mCoins;
};