#include "Transform.h"

#include "EventManager.h"

Transform::Transform():
	Component("Transform"),
	mPositionX(0.0f),
	mPositionY(0.0f),
	mScaleX(0.0f),
	mScaleY(0.0f),
	mAngle(0.0f) {

}

Transform::~Transform() {

}

void Transform::Sprite() {

}

void Transform::Update() {

}

void Transform::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {
	if (jsonObject.HasMember("positionX")) {
		mPositionX = jsonObject["positionX"].GetFloat();
	}
	if (jsonObject.HasMember("positionY")) {
		mPositionY = jsonObject["positionY"].GetFloat();
	}
	if (jsonObject.HasMember("scaleX")) {
		mScaleX = jsonObject["scaleX"].GetFloat();
	}
	if (jsonObject.HasMember("scaleY")) {
		mScaleY = jsonObject["scaleY"].GetFloat();
	}
	if (jsonObject.HasMember("angle")) {
		mAngle = jsonObject["angle"].GetFloat();
	}
}