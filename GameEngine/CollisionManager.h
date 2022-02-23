#pragma once

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Update();
	bool CollisionAABBAABB(float posX1, float posY1, float scaleX1, float scaleY1, float posX2, float posY2, float scaleX2, float scaleY2);
	bool CollisionPointAABB(float posX1, float posY1, float posX2, float posY2, float scaleX2, float scaleY2);
};