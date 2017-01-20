//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IComponent.h"
#include "IObserverPattern.h"
#include "IEvent.h"

class EventBus {
public:
	static EventBus& GetInstance() {
		static EventBus instance;
		return instance;
	}

	void RegisterToEvent(EventIDs e, IObserver* component);
	void Deregister(IObserver* component);
	void DeregisterEverything();
	void FireEvent(IEvent* e);

private:
	EventBus() = default;
	~EventBus() = default;

	std::map<EventIDs, std::vector<IObserver*>> m_listener;
};