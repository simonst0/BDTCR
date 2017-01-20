//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "IObserverPattern.h"

void IObservableSubject::addObserver(IObserver* observer)
{
	m_observers.push_back(observer);
}

bool IObservableSubject::removeObserver(IObserver* observer) {
	auto it = std::find(m_observers.begin(), m_observers.end(), observer);

	if (it != m_observers.end())
	{
		m_observers.erase(it);
		return true;
	}
	return false;
}

void IObservableSubject::notifyObservers(IEvent* e)
{
	for (auto observer : m_observers)
	{
		observer->notify(e);
	}
}