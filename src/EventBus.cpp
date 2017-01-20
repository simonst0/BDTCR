//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "EventBus.h"

void EventBus::RegisterToEvent(EventIDs e, IObserver* observer)
{
	m_listener[e].push_back(observer);
}

void EventBus::FireEvent(IEvent* e) {
	auto listener = m_listener[e->ID];
	for (auto it = listener.begin(); it != listener.end(); it++) {
		(*it)->notify(e);
	}
}

void EventBus::Deregister(IObserver* observer)
{
	for (auto e = m_listener.begin(); e != m_listener.end(); e++)
	{
		for (auto it = e->second.begin(); it != e->second.end();)
		{
			if (*it == observer)
			{
				it = e->second.erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void EventBus::DeregisterEverything() {
	for (auto e = m_listener.begin(); e != m_listener.end(); e++)
	{
		e->second.clear();
	}

	m_listener.clear();
}