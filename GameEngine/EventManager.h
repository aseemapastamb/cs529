#pragma once
#include <string>
#include <unordered_map>

class GameObject;

class Event
{
public:
	Event(std::string eventType);
	virtual ~Event();

public:
	std::string mEventType;
	float mTimer;
};

class CollideEvent : public Event
{
public:
	CollideEvent(GameObject* _pObject1, GameObject* _pObject2);
	~CollideEvent();

public:
	GameObject* pObject1;
	GameObject* pObject2;
};

class ButtonPressEvent : public Event
{
public:
	ButtonPressEvent(GameObject* _pObject1);
	~ButtonPressEvent();

public:
	GameObject* pObject1;
};

class EventManager
{
public:
	EventManager();
	~EventManager();

	void Subscribe(std::string eventType, GameObject* pGameObject);
	void Unsubscribe(std::string eventType, GameObject* pGameObject);
	void Initialize();
	void BroadcastToAll(Event* pEvent);
	void BroadcastToSubscribers(Event* pEvent);
	void AddTimedEvent(Event* pEvent);
	void Update(float frameTime);

private:
	std::vector <Event*> mTimedEvents;
	std::unordered_map <std::string, std::vector<GameObject*>> mSubscriptions;
};