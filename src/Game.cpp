//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "Game.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "MenuState.h"
#include "RegistrationState.h"
#include "MainState.h"
#include "GameOverState.h"
#include "CreditsState.h"
#include "PauseState.h"
#include "Box2DPhysicsManager.h"
#include "ViewManager.h"

using namespace std;
using namespace sf;
	
tgui::Gui Game::GUI;

bool Game::m_shouldBeClosed = false;

void Game::Run()
{
	if (!init())
		return;

	while (m_window.isOpen())
	{
		// process events in the input manager
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == Event::Closed || m_shouldBeClosed)
				m_window.close();
			else
				InputManager::getInstance().Process(event);
		}

		update();
		draw();
	}

	shutdown();
}

bool Game::init()
{
	m_window.create(sf::VideoMode(m_Config.resolution.x, m_Config.resolution.y),
		m_Config.windowName, sf::Style::None);

	GUI.setWindow(m_window);
	ViewManager::GetInstance().Init(&m_window);
	//
	m_gameStateManager.RegisterState(StaticStrings::StateMenu, make_unique<MenuState>(&m_gameStateManager, this, StaticStrings::StateMenu));
	m_gameStateManager.RegisterState(StaticStrings::StateRegistration, make_unique<RegistrationState>(&m_gameStateManager, this, StaticStrings::StateRegistration));
	m_gameStateManager.RegisterState(StaticStrings::StateMain, make_unique<MainState>(&m_gameStateManager, this, StaticStrings::StateMain));
	m_gameStateManager.RegisterState(StaticStrings::StateGameOver, make_unique<GameOverState>(&m_gameStateManager, this, StaticStrings::StateGameOver));
	m_gameStateManager.RegisterState(StaticStrings::StateCredits, make_unique<CreditsState>(&m_gameStateManager, this, StaticStrings::StateCredits));
	m_gameStateManager.RegisterState(StaticStrings::StatePause, make_unique<PauseState>(&m_gameStateManager, this, StaticStrings::StatePause));
	//
	
	m_gameStateManager.SetState(StaticStrings::StateMenu);

	Box2DPhysicsManager::GetInstance().SetGame(this);	return true;
}

void Game::update()
{
	// starts the clock
	static Clock clock;
	// restart takes time
	Time deltaTime = clock.restart();
	float fDeltaTimeSeconds = deltaTime.asSeconds();

	// must be first call
	InputManager::getInstance().Update();
	ViewManager::GetInstance().Update(fDeltaTimeSeconds);
	m_gameStateManager.Update(fDeltaTimeSeconds);
}

void Game::draw()
{
	m_window.clear();

	RenderManager::getInstance().Render();
	//Box2DPhysicsManager::GetInstance().DebugDraw();

	GUI.draw();

	m_window.display();
}

void Game::shutdown()
{
	m_gameStateManager.ShutdownStates();
}

void Game::QuitGame() 
{
	m_shouldBeClosed = true;
}

	