#pragma once

#include "Component.h"

class GameObject;

class Button : public Component
{
public:
	Button();
	~Button();

	void Update();
	void HandleEvent(Event* pEvent);
public:
	bool mPressed;

};