#pragma once

#include "Component.h"
#include <glm.hpp>

class Target : public Component
{
public:
	Target();
	~Target();

	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
	void HandleEvent(Event* pEvent);
	void Initialize();
public:
	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 dir;
	glm::vec2 velInv;
	glm::vec2 posPlayerWRTEnemy;
	float radAng;
	GameObject* mpPlayer;
};