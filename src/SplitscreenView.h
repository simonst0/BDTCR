#pragma once
#include "stdafx.h"
#include "ViewManager.h"

class SplitscreenView : public WindowView
{
public:
	void Update(float deltaTime) override;
	void Clear() override;
	void Init(sf::RenderWindow* window) override;
private:
	std::vector<sf::FloatRect> m_viewports;
};