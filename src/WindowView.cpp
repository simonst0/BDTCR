#include "stdafx.h"
#include "WindowView.h"

void WindowView::RegisterBodyByID(std::string id)
{
	auto body = Box2DPhysicsManager::GetInstance().GetBodyById(id);
	m_registeredBodies.push_back(body);
	m_bodyCount++;
}

std::vector<sf::View*> WindowView::GetView()
{
	return m_views;
}

void WindowView::Move(sf::Vector2f offset, int idx)
{
	m_views[idx]->move(offset);
	deltaPositions[idx] += offset;
}

void WindowView::Clear()
{
	m_registeredBodies.clear();
	m_bodyCount = 0;
	int count = 0;
	for (auto it = deltaPositions.begin(); it != deltaPositions.end();)
	{
		m_views[count]->move(-deltaPositions[count]);
		deltaPositions[count] = sf::Vector2f(0, 0);
		count++;
	}
}