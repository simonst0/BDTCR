//////////////////////////////////////////////////////
// Game Development			- Assignment 2			//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IComponent.h"
#include "ScoreComponent.h"

class Player{
public:
	Player(int gamepadID)
		: m_gamepadID(gamepadID)
	{}

	void AddScore(ScoreComponent* score) { m_score = score; }
	int GetScore() { return m_score->GetScore(); }
	ScoreComponent* GetScoreComponent() { return m_score; }

private:
	int m_gamepadID;
	ScoreComponent* m_score;
};
