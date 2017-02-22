#include "stdafx.h"
#include "SplitscreenView.h"

void SplitscreenView::Update(float deltaTime)
{
	
}

void SplitscreenView::Clear()
{
	WindowView::Clear();
}

void SplitscreenView::Init(sf::RenderWindow* window)
{
	m_window = window;
	auto size = window->getView().getSize();
	std::cout << m_bodyCount << std::endl;
	
	if (m_bodyCount == 2)
	{
		sf::View* view1 = new sf::View(sf::FloatRect(0, 0, size.x / 2, size.y));
		sf::View* view2 = new sf::View(sf::FloatRect(size.x / 2, 0, size.x / 2, size.y));
		view1->setViewport(sf::FloatRect(0, 0, 0.5f, 1));
		view2->setViewport(sf::FloatRect(0.5, 0, 0.5f, 1));
		m_views.push_back(view1);
		m_views.push_back(view2);
	}
	else
	{
		sf::View* view1 = new sf::View(sf::FloatRect(0, 0, size.x / 2, size.y/2));
		sf::View* view2 = new sf::View(sf::FloatRect(size.x / 2, 0, size.x / 2, size.y/2));
		sf::View* view3 = new sf::View(sf::FloatRect(0, size.y/2, size.x / 2, size.y/2));
		sf::View* view4 = new sf::View(sf::FloatRect(size.x / 2, size.y/2, size.x / 2, size.y/2));
		view1->setViewport(sf::FloatRect(0, 0, 0.5f, 0.5f));
		view2->setViewport(sf::FloatRect(0.5f, 0, 0.5f, 0.5f));
		view3->setViewport(sf::FloatRect(0, 0.5f, 0.5f, 0.5f));
		view4->setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f));
		m_views.push_back(view1);
		m_views.push_back(view2);
		m_views.push_back(view3);
		m_views.push_back(view4);
	}
	m_window->setView(*m_views[0]);
}