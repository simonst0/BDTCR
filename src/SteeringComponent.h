//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IComponent.h"
#include "IControlComponent.h"
#include "IObserverPattern.h"

class SteeringComponent : public IComponent, public IObserver
{
public:
	SteeringComponent(GameObject& gameObject, std::unique_ptr<IControlComponent> controlBehaviour, std::string id)
		: IComponent(gameObject)
		, m_controlBehaviour(move(controlBehaviour))
		, m_id(id)
	{}

	virtual bool VInit();
	virtual void VUpdate(float fDeltaTime);
	virtual void notify(IEvent* event);

private:
	std::unique_ptr<IControlComponent> m_controlBehaviour;
	std::string m_id;
	float m_timeout = 0.7f;
	bool m_timeoutActive = false;
	float GetTimeout();
};