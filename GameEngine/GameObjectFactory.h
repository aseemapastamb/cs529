#pragma once

#include <unordered_map>

class GameObject;
class ComponentCreator;

class GameObjectFactory {
public:
	GameObjectFactory();
	~GameObjectFactory();

	void BuildLevel(const char* pFileName);
	GameObject* BuildGameObject(const char* pFileName);
	void Update();

	//void ChangeLevel(const char* pFileName);
public:

private:
private:
	ComponentCreator* mComponentCreator;
};