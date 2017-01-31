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
	if (e->ID == EventIDs::CollisionStart)
	{
		CollisionStartEvent* c = static_cast<CollisionStartEvent*>(e);

		if (c->m_bodyId1 == m_id || c->m_bodyId2 == m_id)
		{

			vector<string> ids = { c->m_bodyId1, c->m_bodyId2 };
			if (Util::AnyIDContainsString(ids, "Player") && Util::AnyIDContainsString(ids, "Arrow"))
			{
				std::string arrowId, playerId;
				if (Util::StringContainsString(c->m_bodyId1, "Arrow"))
					arrowId = c->m_bodyId1;
				else
					arrowId = c->m_bodyId2;
				float arrowDirection = Box2DPhysicsManager::GetInstance().GetAngleById(arrowId);
				b2Vec2 impulse;
				impulse.x = cos(arrowDirection + deg90*3);
				impulse.y = sin(arrowDirection + deg90*3);
				impulse.Normalize();
				impulse *= 0.0015;
				Box2DPhysicsManager::GetInstance().ApplyImpulse(m_id, impulse);
			}
		}
	}
}