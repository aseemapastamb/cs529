#pragma once

#include "Component.h"

class GameObject;

class Spawner : public Component
{
public:
	Spawner();
	~Spawner();

	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
	void HandleEvent(Event* pEvent);
	void Initialize();
public:
	int numType1Enemies;
	int numType2Enemies;
	int numPickupLife;
	int numPickupFastShooting;
	int numPickupGrenade;
	int numPickupCoin;
	int level;
};