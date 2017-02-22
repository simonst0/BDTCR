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
#include "AudioManager.h"

using namespace std;
using namespace sf;

template <typename T, unsigned S>
unsigned arraysize(const T(&v)[S]) { return S; }

GameOverState::GameOverState(GameStateManager* gameStateManager, Game* game, std::string id) : GameState(gameStateManager, game, id)
{
	InitButtons();
	InitScoreLabels();
}

GameOverState::~GameOverState()
{
	m_buttons.clear();
}

void GameOverState::VInit()
{
	if (m_isInit)
		return;

	AudioManager::GetInstance().stopAudioById(StaticStrings::MainMusic);

	auto position = m_game->getWindow().getView().getCenter();

	auto text = make_unique<GameObject>("GameOverTitle");
	auto renderComp = make_unique<TextComponent>(*text,
		m_game->getWindow(), 
		StaticStrings::ResourcePathFonts + StaticStrings::TitleFont, 
		"GAME OVER",
		Vector2f(position.x, position.y - 250),
		85);
	RenderManager::getInstance().Bind(text->GetId(), 0, renderComp.get());

	text->AddComponent(move(renderComp));

	m_isInit = text->Init();
	m_gameObjectList.push_back(move(text));

	auto scores = GameObjectManager::GetInstance().GetPlayerScores();

	int i = 0;
	for (auto score : scores)
	{
		m_scores[i]->setText(score.first + " - " + to_string(score.second) + " Points\n");
		Game::GUI.add(m_scores[i], "score");
		i++;
	}

	m_view = m_game->getWindow().getView();
	BindInput();

	// if the maximum rounds are reached, the game should restart from the beginning
	// so the score is reseted and the music starts with the original pitch
	if (Game::ROUND_COUNT == Game::MAXIMUM_ROUND_COUNT)
		m_usedButtonTexts[0] = m_buttonNewGame;
	else
		m_usedButtonTexts[0] = m_buttonNextRound;

	m_usedButtonTexts[1] = m_buttonMenu;

	SetButtonTexts();
	m_focusedButton = 0;
	SetButtonFocus();

	for (auto button : m_buttons)
	{
		Game::GUI.add(button.second);
	}
}

void GameOverState::InitScoreLabels()
{
	auto position = sf::Vector2f(tgui::bindWidth(Game::GUI).getValue() * 3 / 8, tgui::bindHeight(Game::GUI).getValue() * 3 / 8);
	float padding = 40;

	for (int i = 0; i < 4; i++)
	{
		auto score = std::make_shared<tgui::Label>();
		score = std::make_shared<tgui::Label>();
		score->setFont(StaticStrings::ResourcePathFonts + StaticStrings::TextFont);
		score->setTextColor(PlayerColors::ColorsOpaque[i]);
		score->setOpacity(1);
		score->setTextSize(35);
		score->setAutoSize(true);
		score->setPosition(position.x, position.y + i * padding);
		m_scores[i] = score;
	}
}

void GameOverState::InitButtons()
{
	auto theme = make_shared<tgui::Theme>(StaticStrings::ResourcePathGui + StaticStrings::GuiTheme);
	
	float yPadding = 30;
	float xPadding = 50;

	m_standardButtonSize.x = tgui::bindWidth(Game::GUI) / 3;
	m_standardButtonSize.y = tgui::bindHeight(Game::GUI) / 8;
	m_focusedButtonSize = m_standardButtonSize*1.05f;
	
	for (int i = 0; i < arraysize(m_usedButtonTexts); i++)
	{
		tgui::Button::Ptr button = theme->load(StaticStrings::GuiButton);
		button->setFont(StaticStrings::ResourcePathFonts + StaticStrings::TextFont);
		button->setTextSize(55);
		button->connect("SizeChanged", [&](tgui::Button::Ptr button, tgui::Layout2d focusedButtonSize)
		{
			if (button->getSize() == focusedButtonSize.getValue())
				button->setOpacity(1.0f);
			else
				button->setOpacity(0.75f);
		}
			, button
			, m_focusedButtonSize); 
		button->setPosition(tgui::bindWidth(Game::GUI) / 2 - tgui::bindWidth(button) / 2, tgui::bindHeight(Game::GUI) * 3 / 5 + i * tgui::bindHeight(button) + i * yPadding);
		m_buttons[i] = button;
	}

	m_focusedButton = 0;
	SetButtonFocus();
}

void GameOverState::VUpdate(float delta)
{
	m_game->getWindow().setView(m_view);

	if (m_inputManager.IsButtonPressed(StaticStrings::Select, false))
	{
		auto text = m_buttons[m_focusedButton]->getText().toAnsiString();
		if (text == m_usedButtonTexts[0])
		{
			if (Game::ROUND_COUNT == Game::MAXIMUM_ROUND_COUNT)
				Game::ROUND_COUNT = 0;
			else
				Game::ROUND_COUNT++;

			m_gameStateManager->SetState(StaticStrings::StateMain);
			return;
		}

		if (text == m_usedButtonTexts[1])
		{
			m_gameStateManager->SetState(StaticStrings::StateMenu);
			return;
		}
	}

	if (m_inputManager.IsButtonPressed(StaticStrings::Down, false))
	{
		m_focusedButton++;
		m_focusedButton %= m_buttons.size();
		AudioManager::GetInstance().PlayAudioById(StaticStrings::MenuTick);
		SetButtonFocus();
	}
	else if (m_inputManager.IsButtonPressed(StaticStrings::Up, false))
	{
		if (m_focusedButton == 0)
			m_focusedButton = m_buttons.size();
		m_focusedButton--;
		m_focusedButton %= m_buttons.size();
		AudioManager::GetInstance().PlayAudioById(StaticStrings::MenuTick);
		SetButtonFocus();
	}
}

void GameOverState::VExit()
{
	for (auto& gameObject : m_gameObjectList) {
		RenderManager::getInstance().Unbind(gameObject->GetId());
	}

	m_gameObjectList.clear();

	UnbindInput();

	m_isInit = false;
	
	for (auto button : m_buttons)
	{
		Game::GUI.remove(button.second);
	}

	while(Game::GUI.get("score"))
		Game::GUI.remove(Game::GUI.get("score"));
}

void GameOverState::BindInput()
{
	m_inputManager.Bind(StaticStrings::Down, GamepadButtons::R2);
	m_inputManager.Bind(StaticStrings::Up, GamepadButtons::L2);
	m_inputManager.Bind(StaticStrings::Select, GamepadButtons::X);
}

void GameOverState::UnbindInput()
{
	m_inputManager.Unbind(StaticStrings::Down);
	m_inputManager.Unbind(StaticStrings::Up);
	m_inputManager.Unbind(StaticStrings::Select);
}

void GameOverState::SetButtonTexts()
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->setText(m_usedButtonTexts[i]);
	}
}

void GameOverState::SetButtonFocus()
{
	for (int i = 0; i < m_buttons.size(); i++) 
	{
		if (i == m_focusedButton)
			m_buttons[i]->setSize(m_focusedButtonSize);
		else
			m_buttons[i]->setSize(m_standardButtonSize);
	}
}