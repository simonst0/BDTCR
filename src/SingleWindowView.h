#pragma once
#include "stdafx.h"
#include "ViewManager.h"
#include "WindowView.h"

class SingleWindowView : public WindowView
{
public:
	void Update(float deltaTime) override;
	void Clear() override;
	void Init(sf::RenderWindow* window) override;

private:
	sf::Vector2f GetMiddle();
	float GetZoom(sf::Vector2f middle);
	void Zoom(float zoom);
	float m_actZoom = 1.0f;
};