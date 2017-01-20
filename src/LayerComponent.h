//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include "IRenderComponent.h"
#include <SFML\Graphics.hpp>

using namespace sf;

class LayerComponent : public IRenderComponent {
public:
	typedef std::unique_ptr<sf::Sprite> SpritePtr;
	typedef std::unique_ptr<LayerComponent> Ptr;

	LayerComponent(	GameObject &gameObject,
					sf::RenderWindow &renderWindow) : 
					IRenderComponent(gameObject, renderWindow), 
					m_tiles()
					{}

	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override {}
	virtual void VDraw() override;

	void AddTile(Texture* texture, IntRect source, Vector2f position);

private:
	std::vector<SpritePtr> m_tiles;
};