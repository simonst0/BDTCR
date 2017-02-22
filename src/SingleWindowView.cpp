#include "stdafx.h"
#include "SingleWindowView.h"

void SingleWindowView::Update(float deltaTime)
{
	if (m_bodyCount > 0 && deltaPositions.capacity() != 0)
	{
		Move(-deltaPositions[0]);
		sf::Vector2f middle = GetMiddle();
		Move(middle - m_viewMiddle - deltaPositions[0]);
		Zoom(GetZoom(middle - m_viewMiddle));
		m_window->setView(*m_views[0]);
	}
}

void SingleWindowView::Clear()
{
	m_views[0]->zoom(1 / m_actZoom);
	m_actZoom = 1;
	WindowView::Clear();
}

sf::Vector2f SingleWindowView::GetMiddle()
{
	sf::Vector2f mid;
	float maxX = -FLT_MAX;
	float maxY = -FLT_MAX;
	float minY = FLT_MAX;
	float minX = FLT_MAX;
	for (auto body : m_registeredBodies)
	{
		b2Vec2 bodyPosition = body->GetPosition();
		maxX = std::max(maxX, bodyPosition.x);
		minX = std::min(minX, bodyPosition.x);
		maxY = std::max(maxY, bodyPosition.y);
		minY = std::min(minY, bodyPosition.y);
	}
	mid.x = maxX + minX;
	mid.y = maxY + minY;
	return mid*50.0f;
}

float SingleWindowView::GetZoom(sf::Vector2f middle)
{
	sf::Vector2f sfMid = middle;
	b2Vec2 mid(sfMid.x, sfMid.y);
	float radius = 0;
	for (auto body : m_registeredBodies)
	{
		auto actPos = body->GetPosition();
		actPos.x *= 90;
		actPos.y *= 110;
		auto midToPos = mid - actPos;
		float actRadius = midToPos.Length();
		radius = std::max<float>(actRadius, radius);
	}
	return min((radius / 1250)*(radius / 1250) + 0.05f, 3.0f);
}
void SingleWindowView::Init(sf::RenderWindow* window)
{
	m_window = window;
	deltaPositions.push_back(sf::Vector2f(0, 0));
	auto m_actView = m_window->getView();
	m_views.push_back(&m_actView);
	m_viewMiddle = m_actView.getCenter();
}

void SingleWindowView::Zoom(float zoom)
{
	m_views[0]->zoom(1 / m_actZoom);
	m_views[0]->zoom(zoom);
	m_actZoom = zoom;
}
