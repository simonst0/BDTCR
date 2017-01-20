//////////////////////////////////////////////////////
// Game Development			- Assignment 2			//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include <array>

#include "MenuState.h"

#include "Game.h"
#include "GameStateManager.h"
#include "GameObjectManager.h"

#include "InputManager.h"
#include "RenderManager.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace std;
using namespace sf;

template <typename T, unsigned S>
unsigned arraysize(const T(&v)[S]) { return S; }

MenuState::MenuState(GameStateManager* gameStateManager, Game* game, std::string id) : GameState(gameStateManager, game, id)
{
	InitButtons();
}

void MenuState::VInit()
{
	if (m_isInit)
		return;

	m_gameObjectManager.RemoveAllPlayers();

	for (int i = 0; i < m_buttons.size(); i++) {
		Game::GUI.add(m_buttons[i]);
	}

	m_view = m_game->getWindow().getView();

	sf::Vector2f titlePosition(m_view.getSize().x / 2, 150);

	m_title = make_unique<GameObject>("MenuText");
	auto renderComp = make_unique<TextComponent>(*m_title,
		m_game->getWindow(),
		StaticStrings::ResourcePathFonts + StaticStrings::TitleFont,
		StaticStrings::Title,
		titlePosition,
		45);

	RenderManager::getInstance().Bind(m_title->GetId(), 0, renderComp.get());
	m_title->AddComponent(move(renderComp));

	m_isInit = m_title->Init();
	
	BindInput();
}

void MenuState::InitButtons() {

	auto theme = make_shared<tgui::Theme>(StaticStrings::ResourcePathGui + StaticStrings::GuiTheme);

	string buttonTexts[] = { StaticStrings::MenuStartGame, StaticStrings::MenuQuitGame, StaticStrings::MenuCredits };

	m_buttonCount = arraysize(buttonTexts);
	int yDivision = m_buttonCount + 1;

	m_standardButtonSize.x = tgui::bindWidth(Game::GUI) / 3;
	m_standardButtonSize.y = tgui::bindHeight(Game::GUI) / (yDivision * 2);
	m_focusedButtonSize = m_standardButtonSize*1.05f;

	for (int i = 0; i < m_buttonCount; i++) {
		tgui::Button::Ptr button = theme->load(StaticStrings::GuiButton);
		button->setFont(StaticStrings::ResourcePathFonts + StaticStrings::TextFont);
		button->setText(buttonTexts[i]);
		button->setPosition(tgui::bindWidth(Game::GUI) / 2 - tgui::bindWidth(button) / 2,
			tgui::bindTop(Game::GUI) + tgui::bindHeight(Game::GUI) / 4 + tgui::bindHeight(Game::GUI) * (i + 1) * 3 / (yDivision * 4) - tgui::bindHeight(button) / 2);
		button->connect("SizeChanged", [&](tgui::Button::Ptr button, tgui::Layout2d focusedButtonSize)
		{
			if (button->getSize() == focusedButtonSize.getValue())
				button->setOpacity(1.0f);
			else
				button->setOpacity(0.75f);
		}
			, button
			, m_focusedButtonSize);
		m_buttons[i] = button;
	}

	m_focusedButton = 0;
	SetButtonFocus();
}

void MenuState::VUpdate(float delta)
{
	m_game->getWindow().setView(m_view);
	
	if (InputManager::getInstance().IsKeyPressed(StaticStrings::Select))
	{
		m_gameStateManager->SetState(StaticStrings::StateMain);
		return;
	}

	if (m_inputManager.IsButtonPressed(StaticStrings::Select, false))
	{
		auto text = m_buttons[m_focusedButton]->getText().toAnsiString();
		if (text == StaticStrings::MenuStartGame) 
		{
			m_gameStateManager->SetState(StaticStrings::StateRegistration);
			return;
		}

		if (text == StaticStrings::MenuQuitGame) 
		{
			Game::QuitGame();
		}

		if (text == StaticStrings::MenuCredits) 
		{
			m_gameStateManager->SetState(StaticStrings::StateCredits);
			return;
		}
	}
	
	if (m_inputManager.IsButtonPressed(StaticStrings::Down, false)) 
	{
		m_focusedButton++;
		m_focusedButton %= m_buttonCount;

		SetButtonFocus();
	}
	else if(m_inputManager.IsButtonPressed(StaticStrings::Up, false)) 
	{
		if (m_focusedButton == 0)
			m_focusedButton = m_buttonCount;
		m_focusedButton--;
		m_focusedButton %= m_buttonCount;

		SetButtonFocus();
	}
}

void MenuState::SetButtonFocus() {
	for (int i = 0; i < m_buttonCount; i++) {
		if (i == m_focusedButton)
			m_buttons[i]->setSize(m_focusedButtonSize);
		else
			m_buttons[i]->setSize(m_standardButtonSize);
	}
}

void MenuState::VExit()
{
	for (auto& it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		Game::GUI.remove(it->second);
	}

	RenderManager::getInstance().Unbind(m_title->GetId());
	
	UnbindInput();

	m_isInit = false;
}

void MenuState::VDestroy() 
{
	m_buttons.clear();
}

void MenuState::BindInput() {
	m_inputManager.Bind(StaticStrings::Down, GamepadButtons::R2);
	m_inputManager.Bind(StaticStrings::Up, GamepadButtons::L2);
	m_inputManager.Bind(StaticStrings::Select, GamepadButtons::X);
}

void MenuState::UnbindInput() {
	m_inputManager.Unbind(StaticStrings::Down);
	m_inputManager.Unbind(StaticStrings::Up);
	m_inputManager.Unbind(StaticStrings::Select);
}