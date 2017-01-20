//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "HealthComponent.h"
#include "Game.h"
#include <iostream>

using namespace sf;
using namespace std;

bool HealthComponent::VInit()
{
	auto id = std::to_string(m_playerID);
	auto png = ".png";
	LoadTexture(StaticStrings::ResourcePathBrains + "brainBackground" + id + png, m_circleTexture);
	LoadTexture(StaticStrings::ResourcePathBrains + "brain" + id + png, m_brainTexture);

	auto brainSize = m_brainTexture.getSize();
	m_actScale = 0.4f;
	float padding = 20;
	float right = tgui::bindWidth(Game::GUI).getValue();
	float bottom = tgui::bindHeight(Game::GUI).getValue();

	Vector2f position;
	if(m_playerID == 1)
		position = Vector2f(padding, padding);
	else if (m_playerID == 2)
		position = Vector2f(right - (brainSize.x * m_actScale + padding), padding);
	else if (m_playerID == 3)
		position = Vector2f(padding, bottom - (brainSize.y * m_actScale + padding));
	else
		position = Vector2f(right - (brainSize.x * m_actScale + padding), bottom - (brainSize.y * m_actScale + padding));
	
	m_circle = std::make_shared<tgui::Picture>();
	m_circle->setTexture(m_circleTexture);
	m_circle->setSize(tgui::Layout2d(brainSize.x*m_actScale + 2, brainSize.y*m_actScale + 2));
	m_circle->setPosition(position.x - 1, position.y - 1);
	m_circle->setOpacity(0.7f);
	Game::GUI.add(m_circle);

	m_brain = std::make_shared<tgui::Picture>();
	m_brain->setTexture(m_brainTexture);
	m_brain->setSize(tgui::Layout2d(brainSize.x*m_actScale, brainSize.y*m_actScale));
	m_brain->setPosition(position);
	Game::GUI.add(m_brain);

	return true;
}

HealthComponent::~HealthComponent()
{
	if(!m_alreadyDead)
		Die();

	Game::GUI.remove(m_circle);
}

bool HealthComponent::LoadTexture(string path, Texture& texture)
{
	Image image;
	if (!image.loadFromFile(path))
	{
		err() << "Could not load texture from " << path << std::endl;
		return false;
	}

	image.createMaskFromColor(Color::Black);
	texture.loadFromImage(image);
}

void HealthComponent::VUpdate(float fDeltaTime)
{
	if (m_hasCollided)
		m_currentCooldown -= fDeltaTime;

	if (m_currentCooldown <= 0)
	{
		m_currentCooldown = m_collisionCooldown;
		m_hasCollided = false;
	}
}

void HealthComponent::notify(IEvent* e)
{
	if (!m_hasCollided)
	{
		try
		{
			if (e->ID == EventIDs::CollisionEnd)
			{
				CollisionEndEvent* c = static_cast<CollisionEndEvent*>(e);

				if (c->m_bodyId1 == m_id || c->m_bodyId2 == m_id)
				{
					if ((c->m_bodyId1.find("Goal") != string::npos || c->m_bodyId2.find("Goal") != string::npos)
						|| (c->m_bodyId1.find("Checkpoint") != string::npos || c->m_bodyId2.find("Checkpoint") != string::npos)
						|| c->m_bodyId1.find("ArrowWhiteDown") != string::npos || c->m_bodyId2.find("ArrowWhiteDown") != string::npos)
						return;

					if (c->m_bodyId1.find("Player") != string::npos && c->m_bodyId2.find("Player") != string::npos)
						m_currentHealth -= 10;
					else
						m_currentHealth -= 5;

					ShrinkBrain();
					if (isDestroyed() && !m_alreadyDead)
					{
						PlayerDeathEvent* e = new PlayerDeathEvent(m_id);
						EventBus::GetInstance().FireEvent(e);
						delete e;
						Die();
					}

					std::cout << m_id << " - health : " << m_currentHealth << std::endl;
					m_hasCollided = true;
				}
			}
		}
		catch (const std::bad_cast&)
		{
			return;
		}
	}
}

void HealthComponent::ShrinkBrain()
{
	if (m_currentHealth >= m_previousHealth)
		return;

	auto size = m_brainTexture.getSize();
	auto position = m_brain->getPosition();
	m_actScale *= m_shrinkingScale;
	m_brain->setSize(size.x*m_actScale, size.y*m_actScale);
	m_brain->setPosition(position.x + (1 - m_shrinkingScale)*size.x*m_actScale / 2, position.y + (1 - m_shrinkingScale)*size.y*m_actScale / 2);
	m_previousHealth = m_currentHealth;

}

void HealthComponent::Die() 
{
	m_alreadyDead = true;
	Game::GUI.remove(m_brain);
}