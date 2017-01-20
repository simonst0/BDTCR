//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "InputManager.h"

class GameOverState : public GameState
{
public:
	using GameState::GameState;
	virtual void VInit() override;
	virtual void VUpdate(float delta) override;
	virtual void VExit() override;

private:	
	void BindInput() override;
	void UnbindInput() override;

	InputManager& m_inputManager = InputManager::getInstance();

	std::list<GameObject::Ptr> m_gameObjectList;
	sf::View m_view;
	bool m_isInit = false;
};