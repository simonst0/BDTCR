//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "Box2D\Dynamics\b2Body.h"

class ViewManager
{
public:
	static ViewManager& GetInstance();
	sf::View GetView() { return m_actView; }
	sf::Vector2f GetViewPosition() { return actViewPosition; }
	void Init(sf::RenderWindow* window);
	void Zoom(float zoom);
	void Move(sf::Vector2f offset);
	void Update(float deltaTime);
	void RegisterBodyByID(std::string id);
	void Clear();

private:
	ViewManager() = default;
	sf::Vector2f actViewPosition;
	sf::Vector2f deltaPosition;
	sf::View m_actView;
	sf::RenderWindow* m_window;
	float m_actZoom = 1.0f;
	std::vector<b2Body*> m_registeredBodies;
	int m_bodyCount = 0;
	sf::Vector2f m_viewMiddle;
	sf::Vector2f GetMiddle();
	float GetZoom(sf::Vector2f middle);
};