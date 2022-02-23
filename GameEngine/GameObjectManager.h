#pragma once

#include <vector>

class GameObject;

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();

	void AddObject(GameObject* pNewGameObject);
	void RemoveObject(GameObject* pNewGameObject);
	void RemoveDestroyed();
	void Update();
public:
	std::vector<GameObject*> mGameObjects;

private:
private:
};