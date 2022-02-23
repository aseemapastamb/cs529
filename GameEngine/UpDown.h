#pragma once

#include "Component.h"

class GameObject;

class UpDown: public Component {
public:
	UpDown();
	~UpDown();

	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
	void HandleEvent(Event* pEvent);
	void findTarget();
public:

private:
private:
	bool mGoingUp;
	int mTimer;
	int mTimerLimit;
	GameObject* pPlayer;
};