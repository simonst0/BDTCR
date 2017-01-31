//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "GameState.h"
#include "InputManager.h"
#include "GameObject.h"

class CreditsState : public GameState
{
public:
	using GameState::GameState;

	virtual void VInit() override;

	virtual void VUpdate(float delta) override;
	virtual void VExit() override;

private:
	void BindInput() override;
	void UnbindInput() override;

	void InitText(std::string id, std::string text, std::string font, sf::Vector2f position, int size = 30, sf::Color color = sf::Color::White);
	void InitLogo(std::string id, std::string path, sf::Vector2f position, float scale);

	InputManager& m_inputManager = InputManager::getInstance();

	std::vector<std::unique_ptr<GameObject>> m_items;

	bool m_isInit;
};