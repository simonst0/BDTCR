//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TGUI\TGUI.hpp"

class GameOverState : public GameState
{
public:
	using GameState::GameState;

	GameOverState(GameStateManager* gameStateManager, Game* game, std::string id);
	~GameOverState();

	virtual void VInit() override;
	virtual void VUpdate(float delta) override;
	virtual void VExit() override;

private:	
	void BindInput() override;
	void UnbindInput() override;

	void InitButtons();
	void SetButtonFocus();
	void SetButtonTexts();

	InputManager& m_inputManager = InputManager::getInstance();

	std::list<GameObject::Ptr> m_gameObjectList;
	sf::View m_view;
	bool m_isInit = false;

	tgui::Layout2d m_standardButtonSize;
	tgui::Layout2d m_focusedButtonSize;
	std::map<int, tgui::Button::Ptr> m_buttons;
	const std::string m_buttonNextRound = "next round";
	const std::string m_buttonNewGame = "new game";
	const std::string m_buttonMenu = "back to menu";
	std::string m_usedButtonTexts[2];
	int m_focusedButton;
};