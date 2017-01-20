//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "GameStateManager.h"
#include "GameState.h"
#include "Debug.h"
#include "MainState.h"

using namespace sf;

void GameStateManager::RegisterState(const std::string& name, GameState::Ptr state)
{
	states[name] = move(state);
}

void GameStateManager::SetState(const std::string& stateName)
{
	GameState* state = findState(stateName);
	//ASSERT_MSG(state != nullptr, "State could not be found");

	futureState = state;
}

void GameStateManager::changeState(GameState* state)
{
	if (state != currentState)
	{
		if(state != nullptr && state->GetID() == StaticStrings::StatePause)
		{}
		else if (currentState != nullptr)
			currentState->VExit();

		if (currentState != nullptr && currentState->GetID() == StaticStrings::StatePause)
		{
			// if user switched from pause to menu, the main state has to be shut down
			if (state != nullptr && state->GetID() == StaticStrings::StateMenu)
				previousState->VExit();

			previousState = currentState;
			currentState = state;

			// if user switched from pause to menu, the menu state has to be initialized
			if(currentState != nullptr && currentState->GetID() == StaticStrings::StateMenu)
				currentState->VInit();
		}
		else
		{
			previousState = currentState;
			currentState = state;
			if (currentState != nullptr)
				currentState->VInit();
		}
	}
}

void GameStateManager::Update(float delta)
{
	if (futureState != nullptr)
	{
		changeState(futureState);
		futureState = nullptr;
	}

	if (currentState != nullptr)
		currentState->VUpdate(delta);
}

GameState* GameStateManager::findState(const std::string& stateName)
{
	auto state = states.find(stateName);
	if (state != states.end())
		return state->second.get();
	return nullptr;
}

void GameStateManager::ShutdownStates() {
	for (auto it = states.begin(); it != states.end(); it++)
	{
		it->second->VDestroy();
	}

	states.clear();
}