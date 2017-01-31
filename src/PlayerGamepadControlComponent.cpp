//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "GameObject.h"
#include "PlayerGamepadControlComponent.h"
#include "InputManager.h"
#include "Box2DPhysicsManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include <math.h>
#include <iostream>

using namespace sf;

PlayerGamepadControlComponent::PlayerGamepadControlComponent(
	GameObject &gameObject, int gamepadIndex, std::string id)
	: IControlComponent(gameObject)
	, m_gamepadIndex(gamepadIndex)
	, m_id(id)
{
}

bool
PlayerGamepadControlComponent::VInit()
{
	return true;
}

void
PlayerGamepadControlComponent::VUpdate(float fDeltaTime)
{
	auto joystickPosition = InputManager::getInstance().GetJoystickPosition(m_gamepadIndex);
	Util::eliminateNoise(joystickPosition, 10);
	if (joystickPosition.x != 0 && joystickPosition.y != 0)
	{
		Util::normalize(joystickPosition);
		m_actAngle = getActAngle(joystickPosition.x, joystickPosition.y);
		Box2DPhysicsManager::GetInstance().SetAngle(m_id, m_actAngle);
	}

	if (InputManager::getInstance().IsButtonDown(StaticStrings::Accelerate, m_gamepadIndex))
	{
		m_timeR2isDown += fDeltaTime;
		float angle = Box2DPhysicsManager::GetInstance().GetAngleById(m_id);
		b2Vec2 direction;
		direction.x = cos(angle-m_90deg);
		direction.y = sin(angle-m_90deg);
		float multiplicator = getActForceMultiplicator();
		Box2DPhysicsManager::GetInstance().ApplyForce(m_id, b2Vec2(direction.x*multiplicator, direction.y*multiplicator));
	}
	else
		m_timeR2isDown = 0;
	if (InputManager::getInstance().IsButtonDown(StaticStrings::Break, m_gamepadIndex))
	{
		b2Vec2 velocity = Box2DPhysicsManager::GetInstance().GetVelocityById(m_id);
		velocity.x /= -1000;
		velocity.y /= -1000;
		Box2DPhysicsManager::GetInstance().ApplyForce(m_id, velocity);
	}
	if (InputManager::getInstance().IsButtonPressed(StaticStrings::Honk, m_gamepadIndex))
		AudioManager::GetInstance().PlayAudioById(StaticStrings::MainHorn);
}

float PlayerGamepadControlComponent::getActAngle(float aK, float gK)
{
	float actAngle = atan2(gK, aK);
	actAngle = actAngle + m_90deg;
	return actAngle;
}
float PlayerGamepadControlComponent::getActForceMultiplicator()
{
	return 6 / (1000 + m_timeR2isDown);
}


