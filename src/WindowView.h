#pragma once
#include "stdafx.h"
#include "Box2D\Dynamics\b2Body.h"
#include "Box2DPhysicsManager.h"

class WindowView
{
public:
	virtual void Init(sf::RenderWindow* window) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Clear();
	void RegisterBodyByID(std::string id);
	std::vector<sf::View*> GetView();

protected:
	void Move(sf::Vector2f offset, int idx = 0);

	std::vector<sf::Vector2f> deltaPositions;
	std::vector<b2Body*> m_registeredBodies;

	int m_bodyCount = 0;
	sf::Vector2f m_viewMiddle;

	sf::RenderWindow* m_window;
	std::vector<sf::View*> m_views;
};