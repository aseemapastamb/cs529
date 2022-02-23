#include "Component.h"

Component::Component(std::string type):
	mType(type),
	mpOwner(nullptr) {

}

Component::~Component() {

}

void Component::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {

}

void Component::HandleEvent(Event* pEvent) {

}

std::string Component::GetType() {
	return mType;
}
