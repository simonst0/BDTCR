//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"
#include "IComponent.h"
#include "IObserverPattern.h"

class BoosterComponent : public IComponent, public IObserver
{
public:
	BoosterComponent(GameObject& gameObject, std::string id)
		:IComponent(gameObject)
		, m_id(id)
	{}

	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override;
	virtual void notify(IEvent* event);
private:
	std::string m_id;
	const float deg90 = 1.5708f;
};