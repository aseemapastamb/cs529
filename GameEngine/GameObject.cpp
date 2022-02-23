#include "GameObject.h"

#include "Transform.h"
#include "Sprite.h"
#include "Controller.h"
#include "UpDown.h"
#include "Body.h"
#include "Health.h"
#include "Ammo.h"
#include "Button.h"
#include "AI.h"
#include "Spawner.h"
#include "EventManager.h"

#include <cassert>

GameObject::GameObject():
	mDestroyed(false)
{

}

GameObject::~GameObject() {
	for (auto i = mComponents.begin(); i != mComponents.end(); ++i) {
		delete i->second;
	}
	mComponents.clear();
}

void GameObject::Update() {
	for (auto i = mComponents.begin(); i != mComponents.end(); ++i) {
		assert(i->second);
		i->second->Update();
	}
}

void GameObject::AddComponent(Component* pComponent) {
	if (pComponent->GetType() == "Transform") {
		mComponents["Transform"] = pComponent;
	}
	if (pComponent->GetType() == "Sprite") {
		mComponents["Sprite"] = pComponent;
	}
	if (pComponent->GetType() == "Controller") {
		mComponents["Controller"] = pComponent;
	}
	if (pComponent->GetType() == "UpDown") {
		mComponents["UpDown"] = pComponent;
	}
	if (pComponent->GetType() == "Body") {
		mComponents["Body"] = pComponent;
	}
	if (pComponent->GetType() == "Health") {
		mComponents["Health"] = pComponent;
	}
	if (pComponent->GetType() == "Ammo") {
		mComponents["Ammo"] = pComponent;
	}
	if (pComponent->GetType() == "Button") {
		mComponents["Button"] = pComponent;
	}
	if (pComponent->GetType() == "AI") {
		mComponents["AI"] = pComponent;
	}
	if (pComponent->GetType() == "Spawner") {
		mComponents["Spawner"] = pComponent;
	}
	pComponent->mpOwner = this;
}

Component* GameObject::GetComponent(std::string componentType) {
	if (mComponents.find(componentType) == mComponents.end()) {
		return nullptr;
	}
	return mComponents[componentType];
}

void GameObject::HandleEvent(Event* pEvent) {
	for (auto i = mComponents.begin(); i != mComponents.end(); ++i) {
		i->second->HandleEvent(pEvent);
	}
}
