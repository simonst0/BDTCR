//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <list>

#include "GameState.h"
#include "GameObject.h"
#include "IRenderComponent.h"
#include "Box2DRigidBodyComponent.h"
#include "TextureFactory.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "NLTmxMap.h"
#include "TGUI\TGUI.hpp"

class MainState : public GameState, public IObserver
{
public:
	using GameState::GameState;

	MainState(GameStateManager* gameStateManager, Game* game, std::string id) 
		: GameState(gameStateManager, game, id)
		, m_initialCameraPosition(sf::Vector2f(500, 500)) 
	{}

	virtual void VInit() override;
	virtual void VExit() override;
	virtual void VUpdate(float delta) override;
	void notify(IEvent* e);

private:
	void LoadTMXInput(const std::string& filename);
	void LoadGameObjectFromTMX(NLTmxMapObject* object, std::vector<int> registeredPlayers);

	void StartCountdown();
	void StopCountdown();
	bool m_countdownIsRunning = false;
	float m_countdownDeltaTime;
	int m_countdownDigit;
	tgui::Label::Ptr m_countdownLabel;
	
	void BindInput() override;
	void UnbindInput() override;

	void SetCamera();
	void ResetCamera();

	std::vector<Box2DRigidBodyComponent*> m_rigidBodies;
	int m_environmentCounter;
	int m_deathCounter;

	TextureFactory& m_textureFactory = TextureFactory::GetInstance();
	InputManager& m_inputManager = InputManager::getInstance();
	GameObjectManager& m_gameObjectManager = GameObjectManager::GetInstance();

	const float m_initialCameraZoom = 2.0f;
	const sf::Vector2f m_initialCameraPosition;
	sf::View m_menuCamera;
};