//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "GameState.h"

class GameStateManager
{
public:
	/// registers a new GameState with the given name.
	void RegisterState(const std::string& name, GameState::Ptr state);

	/// Changes to the given state
	void SetState(const std::string& stateName);

	void Update(float delta);

	void ShutdownStates();

private:
	GameState* findState(const std::string& stateName);
	void changeState(GameState* stateName);

	std::unordered_map<std::string, GameState::Ptr> states;
	GameState* previousState = nullptr;
	GameState* currentState = nullptr;
	GameState* futureState = nullptr;
};