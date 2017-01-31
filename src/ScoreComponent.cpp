//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScoreComponent.h"
#include "GameObjectManager.h"
#include "SFML\Graphics.hpp"
#include <iostream>

using namespace sf;

static std::map<std::string, int> m_fullRounds;

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
				vector<string> ids = { c->m_bodyId1, c->m_bodyId2 };
				if (Util::AnyIDContainsString(ids, "Goal"))
				{
					actCheckpointID = 0;
				}
				else if (Util::StringContainsString(c->m_bodyId1, "Checkpoint"))
				{
					actCheckpointID = c->m_bodyId1[c->m_bodyId1.length() - 1] - '0';
				}
				else if (Util::StringContainsString(c->m_bodyId2, "Checkpoint"))
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
					{
						int numPlayers = m_fullRounds.size();
						int countPlayersWithMoreRounds = 0;

						for (auto it = m_fullRounds.begin(); it != m_fullRounds.end(); it++)
						{
							if (it->second > m_fullRounds[m_id])
								countPlayersWithMoreRounds++;
						}
						int points = (1000 / numPlayers)*(numPlayers - countPlayersWithMoreRounds);
						IncreasePoints(points);
						m_fullRounds[m_id]++;
					}
						
				}
			}
		}
		else if (e->ID == EventIDs::PlayerDeath)
		{
			PlayerDeathEvent* p = static_cast<PlayerDeathEvent*>(e);

			if (p->m_playerID != m_playerID)
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
	m_label->setText("Score: " + std::to_string(m_scoreCounter));
	std::cout << m_id << " - score: " << m_scoreCounter << std::endl;
}

bool ScoreComponent::VInit()
{
	m_label = std::make_shared<tgui::Label>();
	m_label->setFont(StaticStrings::ResourcePathFonts + StaticStrings::TextFont);
	m_label->setTextColor(tgui::Color(255, 255, 255));
	m_label->setText("Score: " + std::to_string(m_scoreCounter));
	m_label->setTextSize(30);
	m_label->setAutoSize(true);

	float yPadding = 265;
	float xPadding = 28;
	float right = tgui::bindWidth(Game::GUI).getValue();
	float bottom = tgui::bindHeight(Game::GUI).getValue();
	Vector2f size(tgui::bindWidth(m_label).getValue(), tgui::bindHeight(m_label).getValue());

	Vector2f position;
	if (m_playerID == 1)
		position = Vector2f(xPadding, yPadding);
	else if (m_playerID == 2)
		position = Vector2f(right - (size.x + 3 * xPadding), yPadding);
	else if (m_playerID == 3)
		position = Vector2f(xPadding, bottom - (size.y + yPadding));
	else
		position = Vector2f(right - (size.x + 3 * xPadding), bottom - (size.y + yPadding));

	m_label->setPosition(position);
	Reset();

	return true;
}

void ScoreComponent::Reset()
{
	m_fullRounds[m_id] = 0;
	ActivateGUI();
	m_lastCheckPoint = 0;
}

void ScoreComponent::DeactivateGUI()
{
	Game::GUI.remove(Game::GUI.get("score"));
}

void ScoreComponent::ActivateGUI()
{
	Game::GUI.add(m_label, "score");
}