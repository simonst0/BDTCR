//////////////////////////////////////////////////////
// Game Development			- BrainDamaged Engine	//
// Simon Steiner			- 1510601034, fhs38598	//
// Katrin-Anna Zibuschka	- 1510601044, fhs38708	//
//////////////////////////////////////////////////////

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "IRenderComponent.h"
#include "IObserverPattern.h"

class SpriteRenderComponent : public IRenderComponent, public IObserver
{
public:
	typedef std::unique_ptr<SpriteRenderComponent> Ptr;

	SpriteRenderComponent(GameObject &gameObject,
					sf::RenderWindow &renderWindow,
					const std::string &textureFile);

	virtual bool VInit() override;
	virtual void VUpdate(float fDeltaTime) override {}
	virtual void VDraw() override;

	virtual void notify(IEvent* event);

	sf::Sprite& GetSprite() { return m_sprite;  }
	
	/// Repeat sprite texture n times, e.g., for backgrounds
	/// Attention: overwrites texture size settings of sprite
	void SetRepeat(int n) { m_nRepeat = n; }

private:
	std::string m_textureFile;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	int m_nRepeat = 0;
};