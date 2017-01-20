//////////////////////////////////////////////////////
// Game Development			- Assignment 2			//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "GameObject.h"
#include "GameState.h"
#include "InputManager.h"


class PauseState : public GameState 
{
public:
	using GameState::GameState;

	PauseState(GameStateManager* gameStateManager, Game* game, std::string id);

	virtual void VInit() override;
	virtual void VUpdate(float delta) override;
	virtual void VExit() override;

private:

	virtual void BindInput() override;
	virtual void UnbindInput() override;

	InputManager& m_inputManager = InputManager::getInstance();
	void InitButtons();
	void SetButtonFocus();

	tgui::Layout2d m_standardButtonSize;
	tgui::Layout2d m_focusedButtonSize;
	std::map<int, tgui::Button::Ptr> m_buttons;
	int m_focusedButton;
	const std::string buttonTexts[2] = { "continue game", "back to menu" };
	const int m_buttonCount = 2;

	tgui::Panel::Ptr m_panel;
	bool m_isInit = false;
};
