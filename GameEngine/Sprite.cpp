#include "Sprite.h"
#include "Transform.h"
#include "GameObject.h"

#include "ResourceManager.h"
#include "SDL_surface.h"

extern ResourceManager* gpResourceManager;
//extern SDL_Window* gpWindow;

Sprite::Sprite():
	Component("Sprite"),
	mpSurface(nullptr),
	mpTexture(nullptr),
	mColor("") {

}

Sprite::~Sprite() {

}

void Sprite::Update() {
	//SDL_Rect posRect{};
	//SDL_Surface* pWindowSurface = SDL_GetWindowSurface(gpWindow);
	//Transform* pTransform = (Transform*)(mpOwner->GetComponent("Transform"));

	/*if (pTransform) {
		posRect.x = pTransform->mPositionX;
		posRect.y = pTransform->mPositionY;

		SDL_BlitSurface(mpSurface, NULL, pWindowSurface, &posRect);
	}
	else {
		SDL_BlitSurface(mpSurface, NULL, pWindowSurface, NULL);
	}
	SDL_UpdateWindowSurface(gpWindow);*/
}

void Sprite::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject) {
	if (jsonObject.HasMember("surface")) {
		mpSurface = gpResourceManager->loadSurface(jsonObject["surface"].GetString());
		mpTexture = gpResourceManager->loadTexture(jsonObject["surface"].GetString());
	}
	if (jsonObject.HasMember("color")) {
		mColor = jsonObject["color"].GetString();
	}
	/*
	if (jsonObject.HasMember("width")) {
		mImgWidth = jsonObject["width"].GetInt();
	}
	if (jsonObject.HasMember("surface")) {
		mImgHeight = jsonObject["height"].GetInt();
	}*/
}