//////////////////////////////////////////////////////
// Game Development			- Assignment 2			//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "GameObject.h"
#include "PlayerMoveComponent.h"
#include "InputManager.h"

using namespace sf;

PlayerMoveComponent::PlayerMoveComponent(
	GameObject &gameObject, int playerIndex)
: IComponent(gameObject)
, m_iPlayerIndex(playerIndex)
{
}

bool 
PlayerMoveComponent::VInit()
{
	return true;
}

void 
PlayerMoveComponent::VUpdate(float fDeltaTime)
{
	const float speed = 300.0f; // pixels/second 
	const float distance = speed * fDeltaTime;
	Vector2f translation{};
	if (InputManager::getInstance().IsKeyDown("right", m_iPlayerIndex))
		translation.x += distance;
	if (InputManager::getInstance().IsKeyDown("left", m_iPlayerIndex))
		translation.x -= distance;
	if (InputManager::getInstance().IsKeyDown("up", m_iPlayerIndex))
		translation.y -= distance;
	if (InputManager::getInstance().IsKeyDown("down", m_iPlayerIndex))
		translation.y += distance;

	m_gameObject.GetTransform().translate(translation);
}


