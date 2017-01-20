//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"

#include "PlayerBorderComponent.h"
#include "Box2DPhysicsManager.h"
#include "GameObject.h"
#include "Util.h"
#include <iostream>

using namespace sf;

bool PlayerBorderComponent::VInit()
{
	auto pos = Box2DPhysicsManager::GetInstance().GetPositionById(m_player.GetId());
		m_prevPlayerPos = Vector2f(pos.x, pos.y);
	return true;
}

void PlayerBorderComponent::VUpdate(float fDeltaTime)
{
	Vector2f currentPlayerPos{};
	auto transform = Box2DPhysicsManager::GetInstance().GetTransformById(m_player.GetId(), m_player.GetTransform());
	currentPlayerPos = transform.transformPoint(m_initialPlayerPos);
	const Vector2f diff = (currentPlayerPos - m_prevPlayerPos);
	Vector2f nDiff = diff;
	Util::normalize(nDiff);
	
	const Vector2f size = m_window.getView().getSize();
	const Vector2i currentPosPixel = m_window.mapCoordsToPixel(currentPlayerPos);
	if ((currentPosPixel.x > size.x - m_iBorderSize && Util::dot(Vector2f(1.0f, 0.0f), nDiff) > 0) ||
		(currentPosPixel.y > size.y - m_iBorderSize && Util::dot(Vector2f(0.0f, 1.0f), nDiff) > 0) ||
		(currentPosPixel.x < m_iBorderSize && Util::dot(Vector2f(-1.0f, 0.0f), nDiff) > 0) ||
		(currentPosPixel.y < m_iBorderSize && Util::dot(Vector2f(0.0f, -1.0f), nDiff) > 0))
	{
		auto trans = Box2DPhysicsManager::GetInstance().GetTransformById(m_gameObject.GetId(), m_gameObject.GetTransform());
		trans.translate(diff);
	}
		
	
	m_prevPlayerPos = currentPlayerPos;
}

	
