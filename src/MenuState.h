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

class MenuState : public GameState
{
public:
	using GameState::GameState;

	MenuState(GameStateManager* gameStateManager, Game* game, std::string id);

	virtual void VInit() override;	
	virtual void VUpdate(float delta) override;
	virtual void VExit() override;
	virtual void VDestroy() override;
	
private:
	void BindInput() override;
	void UnbindInput() override;

	void InitButtons();

	GameObjectManager& m_gameObjectManager = GameObjectManager::GetInstance();
	InputManager& m_inputManager = InputManager::getInstance();
	
	std::unique_ptr<GameObject> m_title;
	std::map<int, tgui::Button::Ptr> m_buttons;
	int m_buttonCount;
	int m_focusedButton;

	tgui::Layout2d m_standardButtonSize;
	tgui::Layout2d m_focusedButtonSize;

	void SetButtonFocus();

	sf::View m_view;
	bool m_isInit = false;
};