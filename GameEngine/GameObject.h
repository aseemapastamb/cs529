#pragma once

#include <unordered_map>

class Component;
class Event;

class GameObject {
public:
	GameObject();
	~GameObject();

	void Update();
	void AddComponent(Component* pComponent);
	Component* GetComponent(std::string componentType);
	void HandleEvent(Event* pEvent);
public:
	std::string mType;
	std::unordered_map<std::string, Component*> mComponents;
	std::string mLabel;
	bool mDestroyed;

private:
private:
};

