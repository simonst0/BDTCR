//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "IEvent.h"

class IObserver
{
public:
	virtual void notify(IEvent* event) = 0;
};

class IObservableSubject
{
public:
	virtual void addObserver(IObserver* observer); 
	virtual bool removeObserver(IObserver* observer);

protected:
	std::vector<IObserver*> m_observers;
	virtual void notifyObservers(IEvent* event);
};