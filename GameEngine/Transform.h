#pragma once

#include "Component.h"

class Transform: public Component {
public:
	Transform();
	~Transform();

	void Sprite();
	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
public:
	float mPositionX;
	float mPositionY;
	float mScaleX;
	float mScaleY;
	float mAngle;

private:
private:
};