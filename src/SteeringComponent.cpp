//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "SteeringComponent.h"
#include "Box2DPhysicsManager.h"

bool SteeringComponent::VInit() {
	return m_controlBehaviour->VInit();
}

void SteeringComponent::VUpdate(float fDeltaTime) {
	if (!m_timeoutActive)
		m_controlBehaviour->VUpdate(fDeltaTime);
	else
	{
		m_timeout -= fDeltaTime;
		if (m_timeout <= 0)
		{
			m_timeoutActive = false;
		}
	}
}

void SteeringComponent::notify(IEvent* e)
{
	try
	{
		CollisionEndEvent* c = static_cast<CollisionEndEvent*>(e);

		vector<string> ids = { c->m_bodyId1, c->m_bodyId2 };
		if (Util::AnyIdIsTriggerObject(ids))
			return;

		if (c->m_bodyId1 == m_id || c->m_bodyId2 == m_id)
		{
			if (Util::AnyIDContainsString(ids, "environment"))
			{
				m_timeoutActive = true;
				m_timeout = GetTimeout();
			}
		}
	}
	catch (const std::bad_cast&)
	{
		return;
	}
}

float SteeringComponent::GetTimeout()
{
	float velocityLength = Box2DPhysicsManager::GetInstance().GetVelocityById(m_id).Length();
	return velocityLength / 10;
}