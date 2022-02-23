#pragma once

#include <string>

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

class GameObject;
class Event;

class Component {
public:
	Component(std::string type);
	virtual ~Component();

	virtual void Update() = 0;
	virtual void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
	virtual void HandleEvent(Event* pEvent);
	std::string GetType();
public:
	GameObject* mpOwner;

private:
private:
	std::string mType;
};