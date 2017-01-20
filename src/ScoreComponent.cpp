//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScoreComponent.h"
#include "GameObjectManager.h"
#include <iostream>

void ScoreComponent::notify(IEvent* e)
{
	try
	{
		if (e->ID == EventIDs::CollisionStart)
		{
			CollisionStartEvent* c = static_cast<CollisionStartEvent*>(e);

			if (c->m_bodyId1 == m_id || c->m_bodyId2 == m_id)
			{
				int actCheckpointID = -1;
				if (c->m_bodyId1.find("Goal") != string::npos || c->m_bodyId2.find("Goal") != string::npos)
				{
					actCheckpointID = 0;
				}
				else if (c->m_bodyId1.find("Checkpoint") != string::npos)
				{
					actCheckpointID = c->m_bodyId1[c->m_bodyId1.length() - 1] - '0';
				}
				else if (c->m_bodyId2.find("Checkpoint") != string::npos)
				{
					actCheckpointID = c->m_bodyId2[c->m_bodyId2.length() - 1] - '0';
				}

				if (actCheckpointID < 0 || actCheckpointID >= m_checkpointCount)
					return;

				if ((m_lastCheckPoint + 1) % m_checkpointCount == actCheckpointID)
				{
					m_lastCheckPoint++;
					m_lastCheckPoint = m_lastCheckPoint%m_checkpointCount;

					if (m_lastCheckPoint == 0)
						IncreasePoints();
				}
			}
		}
		else if (e->ID == EventIDs::PlayerDeath)
		{
			PlayerDeathEvent* p = static_cast<PlayerDeathEvent*>(e);

			if (p->m_playerID != m_id)
				IncreasePoints();
		}

	}
	catch (const std::bad_cast&)
	{
		return;
	}
}

void ScoreComponent::IncreasePoints(int points) 
{
	m_scoreCounter += points;
	std::cout << m_id << " - score: " << m_scoreCounter << std::endl;
}