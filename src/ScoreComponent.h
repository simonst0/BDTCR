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
#include "TGUI\TGUI.hpp"

class ScoreComponent : public IComponent, public IObserver
{
public:
	ScoreComponent(GameObject& gameObject, std::string gameObjectID, const int playerID)
		:IComponent(gameObject)
		,m_id(gameObjectID)
		,m_scoreCounter(0)
		,m_lastCheckPoint(0)
		,m_playerID(playerID)
	{}

	void Reset();
	void DeactivateGUI();

	virtual void notify(IEvent* event);
	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override {}
	std::string GetGameObjectID() { return m_id; }
	int GetScore() { return m_scoreCounter; }
	void SetScore(int score) { m_scoreCounter = score; }

private: 
	void IncreasePoints(int points = 1000);
	void ActivateGUI();

	const std::string m_id;
	int m_scoreCounter = 0;
	int m_lastCheckPoint;
	const int m_checkpointCount = 3;
	
	const int m_playerID;

	tgui::Label::Ptr m_label;
};
