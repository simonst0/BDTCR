//////////////////////////////////////////////////////
// Game Development			- Assignment 2			//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IComponent.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"

class Player{
public:
	Player(int gamepadID)
		: m_gamepadID(gamepadID)
		, m_isAlive(true)
	{}

	void AddScore(std::unique_ptr<ScoreComponent> score) { m_score = move(score); }
	int GetScore() { return m_score->GetScore(); }
	ScoreComponent* GetScoreComponent() { return m_score.get(); }
	
	void AddHealth(std::unique_ptr<HealthComponent> health) { m_health = move(health); }
	void Reset() { m_health->VInit(); m_score->Reset(); }
	void DeactivateGUI() { m_health->DeactivateGUI(); m_score->DeactivateGUI(); }
	bool IsAlive() { return m_isAlive; }
	HealthComponent* GetHealthComponent() { return m_health.get(); }

	void Die() { m_isAlive = false; }
	void Live() { m_isAlive = true; }

	void Update(float deltaTime) { m_health->VUpdate(deltaTime); m_score->VUpdate(deltaTime); }

private:
	int m_gamepadID;
	bool m_isAlive;
	std::unique_ptr<ScoreComponent> m_score;
	std::unique_ptr<HealthComponent> m_health;
};
