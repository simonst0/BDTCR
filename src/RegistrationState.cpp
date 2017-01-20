//////////////////////////////////////////////////////
// Game Development			- Assignment 2			//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "RegistrationState.h"

#include "Game.h"
#include "GameStateManager.h"
#include "GameObjectManager.h"

#include "InputManager.h"
#include "RenderManager.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace std;
using namespace sf;

RegistrationState::RegistrationState(GameStateManager* gameStateManager, Game* game, std::string id) : GameState(gameStateManager, game, id)
{
	int padding = 10;
	int count = Game::PLAYER_COUNT;

	string themes[] = { StaticStrings::GuiThemeBlue, StaticStrings::GuiThemeRed, StaticStrings::GuiThemeGreen, StaticStrings::GuiThemeYellow };

	for (int i = 0; i < count; i++) {
		auto theme = make_shared<tgui::Theme>(StaticStrings::ResourcePathGui + themes[i]);
		tgui::Button::Ptr button = theme->load(StaticStrings::GuiButton);
		button->setFont(StaticStrings::ResourcePathFonts + StaticStrings::TextFont);
		button->setSize((tgui::bindWidth(Game::GUI) - (count + 1)*padding) / count,
			tgui::bindHeight(Game::GUI) * 3 / 4);
		button->setPosition(tgui::bindLeft(Game::GUI) + (i + 1)*padding + i*button->getSize().x,
			tgui::bindTop(Game::GUI) + 2 * padding);
		m_buttons[i] = button;
	}
}

void RegistrationState::VInit()
{
	if (m_isInit)
		return;

	for (int i = 0; i < m_buttons.size(); i++) {	
		auto button = m_buttons[i];
		button->setText(m_loginText);
		Game::GUI.add(button);
	}
	
	m_view = m_game->getWindow().getView();

	auto windowSize = m_view.getSize();
	sf::Vector2f position(windowSize.x / 2, windowSize.y - windowSize.y/7);

	m_description = make_unique<GameObject>("RegistrationDescription");
	auto renderComp = make_unique<TextComponent>(*m_description,
		m_game->getWindow(),
		StaticStrings::ResourcePathFonts + StaticStrings::TextFont,
		"press x to start game",
		position,
		55);

	RenderManager::getInstance().Bind(m_description->GetId(), 0, renderComp.get());
	m_description->AddComponent(move(renderComp));

	m_isInit = m_description->Init();

	BindInput();
}

void RegistrationState::VUpdate(float delta)
{
	m_game->getWindow().setView(m_view);
	
	if (m_inputManager.IsKeyPressed(StaticStrings::Select))
	{
		m_gameStateManager->SetState(StaticStrings::StateRegistration);
		return;
	}

	auto deregisteredPlayers = m_gameObjectManager.GetDeregisteredPlayerIDs();
	auto registeredPlayers = m_gameObjectManager.GetRegisteredPlayerIDs();

	for (auto it = registeredPlayers.begin(); it != registeredPlayers.end(); ++it)
	{
		//check if any registered player, pressed the back button
		if (m_inputManager.IsButtonPressed(StaticStrings::Back, *it))
		{
			m_gameStateManager->SetState(StaticStrings::StateMenu);
			return;
		}

		//check if any registered player, pressed the start button
		if (Game::MINIMUM_PLAYER_COUNT <= registeredPlayers.size() && m_inputManager.IsButtonPressed(StaticStrings::Start, *it))
		{
			m_gameStateManager->SetState(StaticStrings::StateMain);
			return;
		}

		//check if any registered player, pressed the deregister button
		if (m_inputManager.IsButtonPressed(StaticStrings::Register, *it))
		{
			m_gameObjectManager.RemovePlayer(*it);
			m_buttons[*it]->setText("press ps\nbutton\nto join");
		}
	}

	for (auto it = deregisteredPlayers.begin(); it != deregisteredPlayers.end(); ++it)
	{
		//check if any player that isn't registered yet, pressed the back button
		if (m_inputManager.IsButtonPressed(StaticStrings::Back, *it))
		{
			m_gameObjectManager.RemoveAllPlayers();
			m_gameStateManager->SetState(StaticStrings::StateMenu);
			return;
		}

		//check if any player that isn't registered yet, pressed the register button
		if (m_inputManager.IsButtonPressed(StaticStrings::Register, *it))
		{
			m_gameObjectManager.AddPlayer(*it);
			m_buttons[*it]->setText(m_logoutText);
		}
	}
}

void RegistrationState::VExit()
{
	for (auto& it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		Game::GUI.remove(it->second);
	}
	
	RenderManager::getInstance().Unbind(m_description->GetId());
	m_description = nullptr;

	UnbindInput();

	m_isInit = false;
}

void RegistrationState::VDestroy() 
{
	m_buttons.clear();
}

void RegistrationState::BindInput() {
	m_inputManager.Bind(StaticStrings::Register, GamepadButtons::PSButton);
	m_inputManager.Bind(StaticStrings::Start, GamepadButtons::X);
	m_inputManager.Bind(StaticStrings::Back, GamepadButtons::Circle);
}

void RegistrationState::UnbindInput() {
	m_inputManager.Unbind(StaticStrings::Register);
	m_inputManager.Unbind(StaticStrings::Start);
	m_inputManager.Unbind(StaticStrings::Back);
}