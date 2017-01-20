//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "IComponent.h"

class IRenderComponent : public IComponent
{
public:
	typedef std::unique_ptr<IRenderComponent> Ptr;
	typedef std::weak_ptr<IRenderComponent> WeakPtr;

	IRenderComponent(GameObject &gameObject, sf::RenderWindow& renderWindow)
		: IComponent(gameObject)
		, m_renderWindow(renderWindow)
	{}

	virtual void VDraw() = 0;

protected:
	sf::RenderWindow& m_renderWindow;
};