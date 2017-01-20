//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "IRenderComponent.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include <SFML/Graphics/Text.hpp>
#include "TGUI\TGUI.hpp"

class RegistrationState : public GameState
{
public:
	using GameState::GameState;

	RegistrationState(GameStateManager* gameStateManager, Game* game, std::string id);

	virtual void VInit() override;
	
	virtual void VUpdate(float delta) override;
	virtual void VExit() override;
	virtual void VDestroy() override;

private:
	void BindInput() override;
	void UnbindInput() override;

	InputManager& m_inputManager = InputManager::getInstance();
	GameObjectManager& m_gameObjectManager = GameObjectManager::GetInstance();

	std::unique_ptr<GameObject> m_description;
	std::map<int, tgui::Button::Ptr> m_buttons;

	sf::View m_view;
	bool m_isInit = false;

	const std::string m_loginText = "press ps\nbutton\nto join";
	const std::string m_logoutText = "press ps\nbutton\nto leave";
};