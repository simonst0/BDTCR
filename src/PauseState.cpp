//////////////////////////////////////////////////////
// Game Development			- Assignment 2			//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "PauseState.h"

template <typename T, unsigned S>
unsigned arraysize(const T(&v)[S]) { return S; }

PauseState::PauseState(GameStateManager* gameStateManager, Game* game, std::string id) : GameState(gameStateManager, game, id)
{
	InitButtons();
}

void PauseState::VInit() 
{
	if (m_isInit)
		return;
	
	m_focusedButton = 0;
	SetButtonFocus();
	BindInput();
	
	Game::GUI.add(m_panel);
	m_isInit = true;
}

void PauseState::VUpdate(float deltaTime) {

	if (m_inputManager.IsButtonPressed(StaticStrings::Select, false))
	{
		auto text = m_buttons[m_focusedButton]->getText().toAnsiString();
		if (text == buttonTexts[0])
		{
			m_gameStateManager->SetState(StaticStrings::StateMain);
			return;
		}

		if (text == buttonTexts[1])
		{
			m_gameStateManager->SetState(StaticStrings::StateMenu);
			return;
		}
	}

	if (m_inputManager.IsButtonPressed(StaticStrings::Down, false))
	{
		m_focusedButton++;
		m_focusedButton %= m_buttonCount;

		SetButtonFocus();
	}
	else if (m_inputManager.IsButtonPressed(StaticStrings::Up, false))
	{
		if (m_focusedButton == 0)
			m_focusedButton = m_buttonCount;
		m_focusedButton--;
		m_focusedButton %= m_buttonCount;

		SetButtonFocus();
	}
}

void PauseState::SetButtonFocus() {
	for (int i = 0; i < m_buttonCount; i++) {
		if (i == m_focusedButton)
			m_buttons[i]->setSize(m_focusedButtonSize);
		else
			m_buttons[i]->setSize(m_standardButtonSize);
	}
}

void PauseState::VExit()
{
	Game::GUI.remove(m_panel);
	UnbindInput();
	m_isInit = false;
}

void PauseState::InitButtons()
{
	auto theme = make_shared<tgui::Theme>(StaticStrings::ResourcePathGui + StaticStrings::GuiTheme);
	
	tgui::Button::Ptr continueButton = theme->load(StaticStrings::GuiButton);
	tgui::Button::Ptr menuButton = theme->load(StaticStrings::GuiButton);

	float yPadding = 20;
	float xPadding = 50;

	m_standardButtonSize.x = tgui::bindWidth(Game::GUI) / 3;
	m_standardButtonSize.y = tgui::bindHeight(Game::GUI) / 5;
	m_focusedButtonSize = m_standardButtonSize*1.05f;

#pragma region create panel
	
	m_panel = std::make_shared<tgui::Panel>();
	m_panel->setFont(StaticStrings::ResourcePathFonts + StaticStrings::TextFont);
	m_panel->setSize(m_standardButtonSize.x + xPadding, m_standardButtonSize.y * 2 + 3*yPadding);
	m_panel->setPosition(tgui::bindLeft(Game::GUI) + tgui::bindWidth(Game::GUI) / 2 - tgui::bindWidth(m_panel) / 2, tgui::bindTop(Game::GUI) + tgui::bindHeight(Game::GUI) / 2 - tgui::bindHeight(m_panel) / 2);
	m_panel->setBackgroundColor(tgui::Color(0, 0, 0, 0));
#pragma endregion

#pragma region create buttons

	continueButton->setText(buttonTexts[0]);
	continueButton->setPosition(tgui::bindWidth(m_panel) / 2 - tgui::bindWidth(continueButton) / 2, tgui::bindHeight(m_panel) / 2 - tgui::bindHeight(continueButton) - 0.5f * yPadding);
	continueButton->connect("SizeChanged", [&](tgui::Button::Ptr button, tgui::Layout2d focusedButtonSize)
	{
		if (button->getSize() == focusedButtonSize.getValue())
			button->setOpacity(1.0f);
		else
			button->setOpacity(0.75f);
	}
		, continueButton
		, m_focusedButtonSize);
	m_buttons[0] = continueButton;
	
	menuButton->setText(buttonTexts[1]);
	menuButton->setPosition(tgui::bindWidth(m_panel) / 2 - tgui::bindWidth(menuButton) / 2, tgui::bindHeight(m_panel) / 2 + 0.5f * yPadding);
	menuButton->connect("SizeChanged", [&](tgui::Button::Ptr button, tgui::Layout2d focusedButtonSize)
	{
		if (button->getSize() == focusedButtonSize.getValue())
			button->setOpacity(1.0f);
		else
			button->setOpacity(0.75f);
	}
		, menuButton
		, m_focusedButtonSize);
	m_buttons[1] = menuButton;
#pragma endregion

	m_panel->add(continueButton);
	m_panel->add(menuButton);
}

void PauseState::BindInput() 
{
	m_inputManager.Bind(StaticStrings::Down, GamepadButtons::R2);
	m_inputManager.Bind(StaticStrings::Up, GamepadButtons::L2);
	m_inputManager.Bind(StaticStrings::Select, GamepadButtons::X);
}

void PauseState::UnbindInput() {
	m_inputManager.Unbind(StaticStrings::Down);
	m_inputManager.Unbind(StaticStrings::Up);
	m_inputManager.Unbind(StaticStrings::Select);
}
