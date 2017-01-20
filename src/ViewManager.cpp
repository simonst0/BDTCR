//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "ViewManager.h"
#include "Box2DPhysicsManager.h"

ViewManager& ViewManager::GetInstance()
{
	static ViewManager instance;
	return instance;
}
void ViewManager::Init(sf::RenderWindow* window)
{
	m_window = window;
	deltaPosition.x = 0;
	deltaPosition.y = 0;
	m_actView = m_window->getView();
	m_viewMiddle = m_actView.getCenter();
}
void ViewManager::Zoom(float zoom)
{
	m_actView.zoom(1 / m_actZoom);
	m_actView.zoom(zoom);
	m_actZoom = zoom;
}
void ViewManager::Update(float deltaTime)
{
	if (m_bodyCount > 0)
	{
		Move(-deltaPosition);
		sf::Vector2f middle = GetMiddle();
		Move(middle - m_viewMiddle - deltaPosition);
		Zoom(GetZoom(middle - m_viewMiddle));
		m_window->setView(m_actView);
	}
}
void ViewManager::Move(sf::Vector2f offset)
{
	m_actView.move(offset);
	deltaPosition += offset;
	actViewPosition += offset;
}
void ViewManager::RegisterBodyByID(std::string id)
{
	auto body = Box2DPhysicsManager::GetInstance().GetBodyById(id);
	m_registeredBodies.push_back(body);
	m_bodyCount++;
}
sf::Vector2f ViewManager::GetMiddle()
{
	sf::Vector2f mid; mid.x = 0; mid.y = 0;
	for (auto body : m_registeredBodies)
	{
		b2Vec2 bodyPosition = body->GetPosition();
		mid.x += bodyPosition.x;
		mid.y += bodyPosition.y;
	}
	mid.x /= m_bodyCount;
	mid.y /= m_bodyCount;
	return mid*100.0f;
}
void ViewManager::Clear()
{
	m_registeredBodies.clear();
	m_bodyCount = 0;
	m_actView.move(-deltaPosition);
	actViewPosition -= deltaPosition;
	m_actView.zoom(1 / m_actZoom);
	m_actZoom = 1;
	deltaPosition = sf::Vector2f(0, 0);
}
float ViewManager::GetZoom(sf::Vector2f middle)
{
	sf::Vector2f sfMid = middle;
	b2Vec2 mid(sfMid.x, sfMid.y);
	float radius = 0;
	for (auto body : m_registeredBodies)
	{
		auto actPos = body->GetPosition();
		actPos.x *= 100;
		actPos.y *= 100;
		auto midToPos = mid - actPos;
		float actRadius = midToPos.Length();
		radius = std::max<float>(actRadius, radius);
	}
	return 0.1 + radius / 400;
}