#pragma once

#include "Component.h"
#include "Texture.h"

class GameObject;
struct SDL_Surface;

class Sprite: public Component {
public:
	Sprite();
	~Sprite();

	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject);
public:
	SDL_Surface* mpSurface;
	Texture* mpTexture;
	std::string mColor;

private:
private:
};