#include "Ammo.h"

Ammo::Ammo():
	Component("Ammo"),
	mBullets(0),
	mGrenades(0),
	mCoins(0)
{
}

Ammo::~Ammo()
{
}

void Ammo::Update()
{
}

void Ammo::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {
	if (jsonObject.HasMember("bullets")) {
		mBullets = jsonObject["bullets"].GetInt();
	}
	if (jsonObject.HasMember("grenades")) {
		mGrenades = jsonObject["grenades"].GetInt();
	}
}
