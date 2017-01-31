//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "IComponent.h"
#include "GameObject.h"
#include "IObserverPattern.h"
#include "IEvent.h"
#include "EventBus.h"
#include "TGUI\TGUI.hpp"

class HealthComponent : public IObserver, public IComponent
{
public:
	HealthComponent(GameObject& gameObject, std::string id, int playerID, float maxHealth = 100)
		: IComponent(gameObject)
		, m_maxHealth(maxHealth)
		, m_id(id)
		, m_playerID(playerID)
		, m_currentHealth(maxHealth)
		, m_previousHealth(maxHealth)
		, m_hasCollided(false)
		, m_isDead(false)
		, m_shrinkingScale(0.95f)
	{}

	virtual void notify(IEvent* event);
	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override;
	bool isDestroyed() { return (m_currentHealth <= 0); }
	std::string GetGameObjectID() { return m_id; }
	int GetPlayerID() { return m_playerID; }
	void Die();

	void DeactivateGUI();

private:

	std::string m_id;
	int m_playerID;
	const float m_maxHealth;
	float m_currentHealth;
	const float m_collisionCooldown = 1.0f;
	float m_currentCooldown = m_collisionCooldown;
	bool m_hasCollided = false;
	bool m_isDead = false;

	float m_actScale;
	float m_previousHealth;
	const float m_shrinkingScale;

	bool LoadTexture(std::string path, sf::Texture& texture);
	void ShrinkBrain();

	sf::Texture m_brainTexture;
	sf::Texture m_circleTexture;
	tgui::Picture::Ptr m_brain;
	tgui::Picture::Ptr m_circle;
};
