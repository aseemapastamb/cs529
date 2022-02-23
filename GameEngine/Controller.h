#pragma once

#include "Component.h"

class GameObject;

class Controller: public Component {
public:
	Controller();
	~Controller();

	void Update();
	void HandleEvent(Event* pEvent);
public:

private:
private:
	float mVelH, mVelV;
	int mFast;
	float mSpeed;
	int mMouseX, mMouseY;
	float mBulletSpawnTimer;
	bool mFastFire;
};