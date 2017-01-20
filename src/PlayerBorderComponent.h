//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IComponent.h"

#include <SFML/Graphics.hpp>

class PlayerBorderComponent : public IComponent
{
public:
	/// \param window the render window used to render this object.
	/// this provides the pixel position using the transform of the 
	/// object.
	/// \param the border size in pixels. Camera is only moved, when
	/// player is about to enter the border
	PlayerBorderComponent(GameObject& camera,
						  GameObject& player, 
						  sf::Vector2f initialPlayerPos,						  
						  sf::RenderWindow& window,
						  int iBorderSize)
		: IComponent(camera)
		, m_window(window)
		, m_iBorderSize(iBorderSize)
		, m_player(player)
		, m_initialPlayerPos(initialPlayerPos)
	{}

	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override;

private:
	sf::Vector2f m_initialPlayerPos;
	GameObject &m_player;
	sf::RenderWindow& m_window;
	int m_iBorderSize;
	sf::Vector2f m_prevPlayerPos;
};