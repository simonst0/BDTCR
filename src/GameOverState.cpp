//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "GameOverState.h"

#include "Game.h"
#include "GameStateManager.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "RenderManager.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace std;
using namespace sf;

void GameOverState::VInit()
{
	if (m_isInit)
		return;
	
	auto position = m_game->getWindow().getView().getCenter();

	auto text = make_unique<GameObject>("GameOverTitle");
	auto renderComp = make_unique<TextComponent>(*text,
		m_game->getWindow(), 
		StaticStrings::ResourcePathFonts + StaticStrings::TitleFont, 
		"GAME OVER",
		Vector2f(position.x, position.y - 70),
		55);

	RenderManager::getInstance().Bind(text->GetId(), 0, renderComp.get());

	text->AddComponent(move(renderComp));

	m_isInit = text->Init();
	m_gameObjectList.push_back(move(text));

	auto scores = GameObjectManager::GetInstance().GetPlayerScores();
	string scoreText = "";

	for (auto score : scores)
	{
		scoreText += score.first + " - " + to_string(score.second) + " Points\n";
	}

	text = make_unique<GameObject>("GameOverText");
	renderComp = make_unique<TextComponent>(*text,
		m_game->getWindow(),
		StaticStrings::ResourcePathFonts + StaticStrings::TextFont,
		scoreText,
		Vector2f(position.x, position.y + 70),
		35);

	RenderManager::getInstance().Bind(text->GetId(), 0, renderComp.get());
	text->AddComponent(move(renderComp));

	m_isInit |= text->Init();
	m_gameObjectList.push_back(move(text));

	m_view = m_game->getWindow().getView();
	BindInput();
}

void GameOverState::VUpdate(float delta)
{
	m_game->getWindow().setView(m_view);

	if (m_inputManager.IsButtonPressed(StaticStrings::Start, false))
		m_gameStateManager->SetState(StaticStrings::StateMenu);
}

void GameOverState::VExit()
{
	for (auto& gameObject : m_gameObjectList) {
		RenderManager::getInstance().Unbind(gameObject->GetId());
	}

	m_gameObjectList.clear();

	UnbindInput();

	m_isInit = false;
}

void GameOverState::BindInput()
{
	m_inputManager.Bind(StaticStrings::Start, GamepadButtons::X);
}

void GameOverState::UnbindInput()
{
	m_inputManager.Unbind(StaticStrings::Start);
}