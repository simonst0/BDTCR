//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "IComponent.h"
#include "IObserverPattern.h"
#include "GameObject.h"

class ScoreComponent : public IComponent, public IObserver
{
public:
	ScoreComponent(GameObject& gameObject, std::string gameObjectID)
		:IComponent(gameObject)
		,m_id(gameObjectID)
		,m_scoreCounter(0)
		,m_lastCheckPoint(0)
	{}

	virtual void notify(IEvent* event);
	virtual bool VInit() override { return true; }
	virtual void VUpdate(float fDeltaTime) override {}
	std::string GetGameObjectID() { return m_id; }
	int GetScore() { return m_scoreCounter; }

private: 
	void IncreasePoints(int points = 1000);

	const std::string m_id;
	int m_scoreCounter = 0;
	int m_lastCheckPoint;
	const int m_checkpointCount = 3;
};
