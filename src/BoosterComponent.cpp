//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////


#include "stdafx.h"
#include "BoosterComponent.h"
#include "Box2DPhysicsManager.h"

bool BoosterComponent::VInit()
{
	return true;
}
void BoosterComponent::VUpdate(float fDeltaTime)
{
}
void BoosterComponent::notify(IEvent* e)
{
	try
	{
		if (e->ID == EventIDs::CollisionStart)
		{
			CollisionStartEvent* c = static_cast<CollisionStartEvent*>(e);

			if (c->m_bodyId1 == m_id || c->m_bodyId2 == m_id)
			{
				if ((c->m_bodyId1.find("Player") != string::npos || c->m_bodyId2.find("Player") != string::npos)
					&& (c->m_bodyId1.find("ArrowWhiteDown") != string::npos || c->m_bodyId2.find("ArrowWhiteDown") != string::npos))
				{
					std::string arrowId;
					if (c->m_bodyId1.find("ArrowWhiteDown") != string::npos)
						arrowId = c->m_bodyId1;
					else
						arrowId = c->m_bodyId2;
					float arrowDirection = Box2DPhysicsManager::GetInstance().GetAngleById(arrowId);
					b2Vec2 force;
					force.x = cos(arrowDirection + deg90) / 6;
					force.y = sin(arrowDirection + deg90) / 6;
					Box2DPhysicsManager::GetInstance().ApplyForce(m_id, force);
				}
			}
		}
	}
	catch (const std::bad_cast&)
	{
		return;
	}
}