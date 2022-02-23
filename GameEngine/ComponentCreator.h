#pragma once

#include "Body.h"
#include "Controller.h"
#include "Sprite.h"
#include "Transform.h"
#include "UpDown.h"
#include "Health.h"
#include "Ammo.h"
#include "Button.h"
#include "AI.h"
#include "Spawner.h"

class ComponentCreator
{
public:
	ComponentCreator();
	~ComponentCreator();

	Body* CreateBody();
	Controller* CreateController();
	Sprite* CreateSprite();
	Transform* CreateTransform();
	UpDown* CreateUpDown();
	Health* CreateHealth();
	Ammo* CreateAmmo();
	Button* CreateButton();
	AI* CreateAI();
	Spawner* CreateSpawner();
};